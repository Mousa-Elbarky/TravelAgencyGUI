#pragma once
#include "SystemController.h"

namespace TravelAgencyGUI {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class CheckoutForm : public System::Windows::Forms::Form
    {
    public:
        CheckoutForm(void)
        {
            InitializeComponent();
            this->lblTotalAmount->Text = SystemController::totalCost.ToString() + L" EGP";
        }

    protected:
        ~CheckoutForm() { if (components) delete components; }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::Label^ lblInvoice;
    private: System::Windows::Forms::Label^ lblTotalAmount;
    private: System::Windows::Forms::Button^ btnBack;
    private: System::Windows::Forms::Button^ btnConfirm;
    private: System::ComponentModel::Container^ components;

           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->lblInvoice = (gcnew System::Windows::Forms::Label());
               this->lblTotalAmount = (gcnew System::Windows::Forms::Label());
               this->btnBack = (gcnew System::Windows::Forms::Button());
               this->btnConfirm = (gcnew System::Windows::Forms::Button());
               this->SuspendLayout();

               this->lblTitle->Text = L"Step 4: Final Checkout";
               this->lblTitle->Location = System::Drawing::Point(30, 25);
               this->lblTitle->Size = System::Drawing::Size(300, 25);
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Bold));
               this->lblTitle->ForeColor = System::Drawing::Color::DarkBlue;

               this->lblInvoice->Text = L"The total cost for your complete package is:";
               this->lblInvoice->Location = System::Drawing::Point(30, 80);
               this->lblInvoice->Size = System::Drawing::Size(330, 20);
               this->lblInvoice->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Regular));

               this->lblTotalAmount->Text = L"0 EGP";
               this->lblTotalAmount->Location = System::Drawing::Point(30, 115);
               this->lblTotalAmount->Size = System::Drawing::Size(320, 40);
               this->lblTotalAmount->Font = (gcnew System::Drawing::Font(L"Arial", 20, System::Drawing::FontStyle::Bold));
               this->lblTotalAmount->ForeColor = System::Drawing::Color::Crimson;

               this->btnBack->Text = L"Back";
               this->btnBack->Location = System::Drawing::Point(30, 190);
               this->btnBack->Size = System::Drawing::Size(100, 38);
               this->btnBack->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Regular));
               this->btnBack->Click += gcnew System::EventHandler(this, &CheckoutForm::btnBack_Click);

               this->btnConfirm->Text = L"Confirm Booking 💳";
               this->btnConfirm->Location = System::Drawing::Point(170, 190);
               this->btnConfirm->Size = System::Drawing::Size(180, 38);
               this->btnConfirm->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
               this->btnConfirm->BackColor = System::Drawing::Color::LightGreen;
               this->btnConfirm->Click += gcnew System::EventHandler(this, &CheckoutForm::btnConfirm_Click);

               this->ClientSize = System::Drawing::Size(390, 270);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->lblInvoice);
               this->Controls->Add(this->lblTotalAmount);
               this->Controls->Add(this->btnBack);
               this->Controls->Add(this->btnConfirm);
               this->Name = L"CheckoutForm";
               this->Text = L"Travel Agency - Checkout";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->ResumeLayout(false);
               this->PerformLayout();
           }

    private: System::Windows::Forms::Form^ GetFormByName(System::String^ name) {
        for (int i = 0; i < System::Windows::Forms::Application::OpenForms->Count; i++) {
            if (System::Windows::Forms::Application::OpenForms[i]->Name == name) {
                return System::Windows::Forms::Application::OpenForms[i];
            }
        }
        return nullptr;
    }

    private: System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
        System::Windows::Forms::Form^ activityForm = GetFormByName(L"ActivityForm");
        if (activityForm != nullptr) activityForm->Show();
        this->Close();
    }

    private: System::Void btnConfirm_Click(System::Object^ sender, System::EventArgs^ e) {
        this->btnConfirm->Text = L"Done! 👍";
        this->btnConfirm->Enabled = false;
        this->btnConfirm->BackColor = System::Drawing::Color::DarkGreen;
        this->btnConfirm->ForeColor = System::Drawing::Color::White;

        MessageBox::Show(L"Your booking has been successfully confirmed!\nThank you for choosing our Travel Agency.",
            L"Booking Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

        System::Windows::Forms::Application::Exit();
    }
    };
}