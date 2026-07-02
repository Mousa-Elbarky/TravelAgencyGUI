#pragma once
#include "SystemController.h"
#include "ActivityForm.h"

namespace TravelAgencyGUI {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class HotelForm : public System::Windows::Forms::Form
    {
    public:
        HotelForm(void)
        {
            InitializeComponent();
            LoadFilteredHotels();
        }

    protected:
        ~HotelForm() { if (components) delete components; }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::ListBox^ lstHotels;
    private: System::Windows::Forms::Label^ lblNights;
    private: System::Windows::Forms::NumericUpDown^ numNights;
    private: System::Windows::Forms::Button^ btnBack;
    private: System::Windows::Forms::Button^ btnNext;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->lstHotels = (gcnew System::Windows::Forms::ListBox());
               this->lblNights = (gcnew System::Windows::Forms::Label());
               this->numNights = (gcnew System::Windows::Forms::NumericUpDown());
               this->btnBack = (gcnew System::Windows::Forms::Button());
               this->btnNext = (gcnew System::Windows::Forms::Button());
               this->SuspendLayout();

               this->lblTitle->Text = L"Step 2: Choose Accomodation";
               this->lblTitle->Location = System::Drawing::Point(30, 15);
               this->lblTitle->Size = System::Drawing::Size(330, 20);
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));

               this->lstHotels->Location = System::Drawing::Point(30, 45);
               this->lstHotels->Size = System::Drawing::Size(320, 100);

               this->lblNights->Text = L"Number of Nights:";
               this->lblNights->Location = System::Drawing::Point(30, 160);
               this->lblNights->Size = System::Drawing::Size(120, 20);

               this->numNights->Location = System::Drawing::Point(160, 158);
               this->numNights->Size = System::Drawing::Size(60, 20);
               this->numNights->Minimum = 1;
               this->numNights->Value = 1;

               this->btnBack->Text = L"Back";
               this->btnBack->Location = System::Drawing::Point(30, 210);
               this->btnBack->Size = System::Drawing::Size(100, 35);
               this->btnBack->Click += gcnew System::EventHandler(this, &HotelForm::btnBack_Click);

               this->btnNext->Text = L"Next: Activities";
               this->btnNext->Location = System::Drawing::Point(200, 210);
               this->btnNext->Size = System::Drawing::Size(150, 35);
               this->btnNext->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
               this->btnNext->Click += gcnew System::EventHandler(this, &HotelForm::btnNext_Click);

               this->ClientSize = System::Drawing::Size(390, 280);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->lstHotels);
               this->Controls->Add(this->lblNights);
               this->Controls->Add(this->numNights);
               this->Controls->Add(this->btnBack);
               this->Controls->Add(this->btnNext);
               this->Name = L"HotelForm";
               this->Text = L"Travel Agency - Hotel Selection";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->ResumeLayout(false);
               this->PerformLayout();
           }

           void LoadFilteredHotels() {
               lstHotels->Items->Clear();
               if (SystemController::selectedCountry == "Turkey") {
                   lstHotels->Items->Add(L"Istanbul Hotel - 2000 EGP/Night");
                   lstHotels->Items->Add(L"Bosphorus Hotel - 2500 EGP/Night");
               }
               else if (SystemController::selectedCountry == "Saudi") {
                   lstHotels->Items->Add(L"Makkah Hotel - 3000 EGP/Night");
                   lstHotels->Items->Add(L"Madinah Hotel - 2800 EGP/Night");
               }
               else if (SystemController::selectedCountry == "UAE") {
                   lstHotels->Items->Add(L"Dubai Palace - 3500 EGP/Night");
                   lstHotels->Items->Add(L"Marina Hotel - 3200 EGP/Night");
               }
           }

    private: System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
        System::Windows::Forms::Form^ mainForm = System::Windows::Forms::Application::OpenForms[L"MyForm"];
        if (mainForm != nullptr) mainForm->Show();
        this->Close();
    }

    private: System::Void btnNext_Click(System::Object^ sender, System::EventArgs^ e) {
        if (lstHotels->SelectedIndex == -1) {
            MessageBox::Show(L"Please select a hotel first!", L"Selection Required", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        double pricePerNight = 0.0;
        int hotelIndex = lstHotels->SelectedIndex;

        if (SystemController::selectedCountry == "Turkey") {
            pricePerNight = (hotelIndex == 0) ? 2000.0 : 2500.0;
        }
        else if (SystemController::selectedCountry == "Saudi") {
            pricePerNight = (hotelIndex == 0) ? 3000.0 : 2800.0;
        }
        else if (SystemController::selectedCountry == "UAE") {
            pricePerNight = (hotelIndex == 0) ? 3500.0 : 3200.0;
        }

        int nights = Convert::ToInt32(numNights->Value);
        double totalHotelCost = pricePerNight * nights;

        SystemController::addToTotal(totalHotelCost);

        ActivityForm^ actScreen = gcnew ActivityForm();
        actScreen->Show();
        this->Hide();
    }
    };
}