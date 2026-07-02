#pragma once
#include "SystemController.h"
#include "HotelForm.h"
#include <msclr/marshal_cppstd.h>

namespace TravelAgencyGUI {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            SystemController::flightSys.loadFlightsData();
        }

    protected:
        ~MyForm() { if (components) delete components; }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::ComboBox^ cmbCity;
    private: System::Windows::Forms::ListBox^ lstFlights;
    private: System::Windows::Forms::Label^ lblClass;
    private: System::Windows::Forms::ComboBox^ cmbClass;
    private: System::Windows::Forms::Button^ btnNext;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->cmbCity = (gcnew System::Windows::Forms::ComboBox());
               this->lstFlights = (gcnew System::Windows::Forms::ListBox());
               this->lblClass = (gcnew System::Windows::Forms::Label());
               this->cmbClass = (gcnew System::Windows::Forms::ComboBox());
               this->btnNext = (gcnew System::Windows::Forms::Button());
               this->SuspendLayout();

               this->lblTitle->Text = L"Step 1: Select Your Destination Flight";
               this->lblTitle->Location = System::Drawing::Point(30, 25);
               this->lblTitle->Size = System::Drawing::Size(300, 20);
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));

               this->cmbCity->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Turkey", L"Saudi Arabia", L"UAE" });
               this->cmbCity->Location = System::Drawing::Point(30, 60);
               this->cmbCity->Size = System::Drawing::Size(320, 25);
               this->cmbCity->DropDownStyle = ComboBoxStyle::DropDownList;
               this->cmbCity->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::cmbCity_SelectedIndexChanged);

               this->lstFlights->Location = System::Drawing::Point(30, 105);
               this->lstFlights->Size = System::Drawing::Size(320, 90);

               this->lblClass->Text = L"Ticket Class:";
               this->lblClass->Location = System::Drawing::Point(30, 212);
               this->lblClass->Size = System::Drawing::Size(90, 20);

               this->cmbClass->Items->AddRange(gcnew cli::array< System::Object^ >(2) { L"Economy", L"Business (+ $1000)" });
               this->cmbClass->Location = System::Drawing::Point(130, 210);
               this->cmbClass->Size = System::Drawing::Size(220, 25);
               this->cmbClass->DropDownStyle = ComboBoxStyle::DropDownList;
               this->cmbClass->SelectedIndex = 0;

               this->btnNext->Text = L"Next: Choose Hotel";
               this->btnNext->Location = System::Drawing::Point(200, 255);
               this->btnNext->Size = System::Drawing::Size(150, 35);
               this->btnNext->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
               this->btnNext->Click += gcnew System::EventHandler(this, &MyForm::btnNext_Click);

               this->ClientSize = System::Drawing::Size(390, 315);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->cmbCity);
               this->Controls->Add(this->lstFlights);
               this->Controls->Add(this->lblClass);
               this->Controls->Add(this->cmbClass);
               this->Controls->Add(this->btnNext);
               this->Name = L"MyForm";
               this->Text = L"Travel Agency - Flight Selection";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->ResumeLayout(false);
               this->PerformLayout();
           }

    private: System::Void cmbCity_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
        lstFlights->Items->Clear();
        System::String^ sysStr = cmbCity->SelectedItem->ToString();
        std::string nativeCity = msclr::interop::marshal_as<std::string>(sysStr);

        SystemController::currentFlightsResult = SystemController::flightSys.searchFlightsByCity(nativeCity);

        for (size_t i = 0; i < SystemController::currentFlightsResult.size(); i++) {
            System::String^ flightInfo = L"Flight ID: " + SystemController::currentFlightsResult[i].id +
                L" - Price: $" + SystemController::currentFlightsResult[i].price;
            lstFlights->Items->Add(flightInfo);
        }
    }

    private: System::Void btnNext_Click(System::Object^ sender, System::EventArgs^ e) {
        if (cmbCity->SelectedIndex == -1 || lstFlights->SelectedIndex == -1) {
            MessageBox::Show(L"Please select destination and flight first!", L"Selection Required", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        SystemController::resetTotal();

        std::string rawCountry = msclr::interop::marshal_as<std::string>(cmbCity->SelectedItem->ToString());
        if (rawCountry == "Saudi Arabia") {
            SystemController::selectedCountry = "Saudi";
        }
        else {
            SystemController::selectedCountry = rawCountry;
        }

        int selectedIndex = lstFlights->SelectedIndex;
        double flightPrice = SystemController::currentFlightsResult[selectedIndex].price;

        if (cmbClass->SelectedIndex == 1) {
            flightPrice += 1000.0;
        }

        SystemController::addToTotal(flightPrice);

        HotelForm^ hotelScreen = gcnew HotelForm();
        hotelScreen->Show();
        this->Hide();
    }
    };
}