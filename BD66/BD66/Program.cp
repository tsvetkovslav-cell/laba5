#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Создаем и запускаем главную форму
    BankSystemWinForms::Form1^ form = gcnew BankSystemWinForms::Form1();
    Application::Run(form);

    return 0;
}