#pragma once
#include "SystemController.h"
#include "CheckoutForm.h"
#include <msclr/marshal_cppstd.h>

namespace TravelAgencyGUI {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class ActivityForm : public System::Windows::Forms::Form
    {
    public:
        ActivityForm(void)
        {
            InitializeComponent();
            LoadActivities();
        }

    protected:
        ~ActivityForm() { if (components) delete components; }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::ListBox^ lstActivities;
    private: System::Windows::Forms::Label^ lblTime;
    private: System::Windows::Forms::ComboBox^ cmbTimes;
    private: System::Windows::Forms::Button^ btnBack;
    private: System::Windows::Forms::Button^ btnNext;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->lstActivities = (gcnew System::Windows::Forms::ListBox());
               this->lblTime = (gcnew System::Windows::Forms::Label());
               this->cmbTimes = (gcnew System::Windows::Forms::ComboBox());
               this->btnBack = (gcnew System::Windows::Forms::Button());
               this->btnNext = (gcnew System::Windows::Forms::Button());
               this->SuspendLayout();

               this->lblTitle->Text = L"Step 3: Choose Local Activity";
               this->lblTitle->Location = System::Drawing::Point(30, 15);
               this->lblTitle->Size = System::Drawing::Size(300, 20);
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));

               this->lstActivities->Location = System::Drawing::Point(30, 45);
               this->lstActivities->Size = System::Drawing::Size(320, 100);
               this->lstActivities->SelectedIndexChanged += gcnew System::EventHandler(this, &ActivityForm::lstActivities_SelectedIndexChanged);

               this->lblTime->Text = L"Available Slots:";
               this->lblTime->Location = System::Drawing::Point(30, 160);
               this->lblTime->Size = System::Drawing::Size(100, 20);

               this->cmbTimes->Location = System::Drawing::Point(140, 158);
               this->cmbTimes->Size = System::Drawing::Size(210, 25);
               this->cmbTimes->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

               this->btnBack->Text = L"Back";
               this->btnBack->Location = System::Drawing::Point(30, 210);
               this->btnBack->Size = System::Drawing::Size(100, 35);
               this->btnBack->Click += gcnew System::EventHandler(this, &ActivityForm::btnBack_Click);

               this->btnNext->Text = L"Next: Checkout";
               this->btnNext->Location = System::Drawing::Point(200, 210);
               this->btnNext->Size = System::Drawing::Size(150, 35);
               this->btnNext->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
               this->btnNext->Click += gcnew System::EventHandler(this, &ActivityForm::btnNext_Click);

               this->ClientSize = System::Drawing::Size(390, 280);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->lstActivities);
               this->Controls->Add(this->lblTime);
               this->Controls->Add(this->cmbTimes);
               this->Controls->Add(this->btnBack);
               this->Controls->Add(this->btnNext);
               this->Name = L"ActivityForm";
               this->Text = L"Travel Agency - Activities";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->ResumeLayout(false);
               this->PerformLayout();
           }

           void LoadActivities() {
               lstActivities->Items->Clear();
               if (SystemController::selectedCountry == "Turkey") {
                   lstActivities->Items->Add(L"Bosphorus Cruise Tour - 500 EGP");
                   lstActivities->Items->Add(L"Cappadocia Hot Air Balloon - 2500 EGP");
               }
               else if (SystemController::selectedCountry == "Saudi") {
                   lstActivities->Items->Add(L"Desert Safari & ATV - 800 EGP");
                   lstActivities->Items->Add(L"Historical Museum Visit - 300 EGP");
               }
               else if (SystemController::selectedCountry == "UAE") {
                   lstActivities->Items->Add(L"Scuba Diving Dubai - 1500 EGP");
                   lstActivities->Items->Add(L"Burj Khalifa Top View - 1000 EGP");
               }
           }

    private: System::Void lstActivities_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
        cmbTimes->Items->Clear();
        if (lstActivities->SelectedIndex != -1) {
            cmbTimes->Items->AddRange(gcnew cli::array< System::Object^ >(3) { L"10:00 AM - 01:00 PM", L"03:00 PM - 06:00 PM", L"08:00 PM - 11:00 PM" });
            cmbTimes->SelectedIndex = 0;
        }
    }

    private: System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
        System::Windows::Forms::Form^ hotelForm = System::Windows::Forms::Application::OpenForms[L"HotelForm"];
        if (hotelForm != nullptr) hotelForm->Show();
        this->Close();
    }

    private: System::Void btnNext_Click(System::Object^ sender, System::EventArgs^ e) {
        if (lstActivities->SelectedIndex == -1 || cmbTimes->SelectedIndex == -1) {
            MessageBox::Show(L"Please select an activity and time slot!", L"Selection Required", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        double activityPrice = 0.0;
        int actIndex = lstActivities->SelectedIndex;

        if (SystemController::selectedCountry == "Turkey") {
            activityPrice = (actIndex == 0) ? 500.0 : 2500.0;
        }
        else if (SystemController::selectedCountry == "Saudi") {
            activityPrice = (actIndex == 0) ? 800.0 : 3000.0;
        }
        else if (SystemController::selectedCountry == "UAE") {
            activityPrice = (actIndex == 0) ? 1500.0 : 1000.0;
        }

        SystemController::selectedActivity = msclr::interop::marshal_as<std::string>(lstActivities->SelectedItem->ToString());
        SystemController::activityTime = msclr::interop::marshal_as<std::string>(cmbTimes->SelectedItem->ToString());

        SystemController::addToTotal(activityPrice);

        CheckoutForm^ checkScreen = gcnew CheckoutForm();
        checkScreen->Show();
        this->Hide();
    }
    };
}