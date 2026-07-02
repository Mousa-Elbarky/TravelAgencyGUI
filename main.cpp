#include "MyForm.h"
[System::STAThreadAttribute]
int main(cli::array<System::String^>^ args) {
    System::Windows::Forms::Application::Run(gcnew TravelAgencyGUI::MyForm());
    return 0;
}