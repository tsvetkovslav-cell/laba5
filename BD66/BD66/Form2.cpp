#include "Form2.h"

namespace BankSystemWinForms {

    Form2::Form2(void) {
        InitializeComponent();
    }

    Form2::Form2(int viewMode) {
        InitializeComponent(viewMode);
    }

    Form2::Form2(String^ title, String^ reportText) {
        InitializeComponent(title, reportText);
    }

    Form2::~Form2() {
        if (components) {
            delete components;
        }
    }

    void Form2::InitializeComponent(void) {
        this->components = gcnew System::ComponentModel::Container();
        this->Text = L"\u0421\u043f\u0440\u0430\u0432\u043a\u0430";
        this->Size = System::Drawing::Size(450, 350);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
        this->BackColor = System::Drawing::Color::WhiteSmoke;

        this->labelContent = gcnew System::Windows::Forms::Label();
        this->labelContent->Text = L"\u0411\u0430\u043d\u043a\u043e\u0432\u0441\u043a\u0430\u044f \u0441\u0438\u0441\u0442\u0435\u043c\u0430.\r\n\r\n\u0417\u0434\u0435\u0441\u044c \u043c\u043e\u0436\u043d\u043e \u0443\u043f\u0440\u0430\u0432\u043b\u044f\u0442\u044c \u043a\u043b\u0438\u0435\u043d\u0442\u0430\u043c\u0438 \u0438 \u0442\u0438\u043f\u0430\u043c\u0438 \u0432\u043a\u043b\u0430\u0434\u043e\u0432,\r\n\u0441\u043e\u0445\u0440\u0430\u043d\u044f\u0442\u044c \u0438 \u0437\u0430\u0433\u0440\u0443\u0436\u0430\u0442\u044c \u0434\u0430\u043d\u043d\u044b\u0435 \u0438\u0437 \u0444\u0430\u0439\u043b\u0430 \u0438 \u0431\u0430\u0437\u044b \u0434\u0430\u043d\u043d\u044b\u0445.";
        this->labelContent->Location = System::Drawing::Point(20, 20);
        this->labelContent->Size = System::Drawing::Size(400, 120);
        this->labelContent->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f);
        this->labelContent->ForeColor = System::Drawing::Color::Black;
        this->Controls->Add(this->labelContent);
    }

    void Form2::InitializeComponent(int viewMode) {
        this->components = gcnew System::ComponentModel::Container();
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;

        this->labelContent = gcnew System::Windows::Forms::Label();
        this->labelContent->Location = System::Drawing::Point(20, 20);
        this->labelContent->Size = System::Drawing::Size(400, 200);
        this->labelContent->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f);

        if (viewMode == 0) {
            this->Text = L"\u0418\u043d\u0444\u043e\u0440\u043c\u0430\u0446\u0438\u044f";
            this->Size = System::Drawing::Size(450, 300);
            this->BackColor = System::Drawing::Color::LightYellow;
            this->labelContent->ForeColor = System::Drawing::Color::DarkSlateGray;
            this->labelContent->Text = L"\u0420\u0435\u0436\u0438\u043c: \u0418\u043d\u0444\u043e\u0440\u043c\u0430\u0446\u0438\u044f.\r\n\r\n\u0418\u0441\u043f\u043e\u043b\u044c\u0437\u0443\u0439\u0442\u0435 \u0432\u043a\u043b\u0430\u0434\u043a\u0438 \u0434\u043b\u044f \u043f\u0435\u0440\u0435\u043a\u043b\u044e\u0447\u0435\u043d\u0438\u044f \u043c\u0435\u0436\u0434\u0443 \u043a\u043b\u0438\u0435\u043d\u0442\u0430\u043c\u0438, \u0442\u0438\u043f\u0430\u043c\u0438 \u0432\u043a\u043b\u0430\u0434\u043e\u0432 \u0438 \u0441\u0432\u0435\u0434\u0435\u043d\u0438\u044f\u043c\u0438 \u043e \u0411\u0414.";
        }
        else {
            this->Text = L"\u0420\u0435\u0436\u0438\u043c \u043e\u0442\u043e\u0431\u0440\u0430\u0436\u0435\u043d\u0438\u044f";
            this->Size = System::Drawing::Size(450, 320);
            this->BackColor = System::Drawing::Color::Lavender;
            this->labelContent->ForeColor = System::Drawing::Color::Indigo;
            this->labelContent->Text = L"\u0420\u0435\u0436\u0438\u043c \u043e\u0442\u043e\u0431\u0440\u0430\u0436\u0435\u043d\u0438\u044f: " + viewMode.ToString() + L".\r\n\r\n\u0412\u043d\u0435\u0448\u043d\u0438\u0439 \u0432\u0438\u0434 \u0444\u043e\u0440\u043c\u044b \u0438\u0437\u043c\u0435\u043d\u0451\u043d \u0432 \u0437\u0430\u0432\u0438\u0441\u0438\u043c\u043e\u0441\u0442\u0438 \u043e\u0442 \u043f\u0435\u0440\u0435\u0434\u0430\u043d\u043d\u043e\u0433\u043e \u043f\u0430\u0440\u0430\u043c\u0435\u0442\u0440\u0430 (\u043f\u0435\u0440\u0435\u0433\u0440\u0443\u0437\u043a\u0430 \u043a\u043e\u043d\u0441\u0442\u0440\u0443\u043a\u0442\u043e\u0440\u0430).";
        }
        this->Controls->Add(this->labelContent);
    }

    void Form2::InitializeComponent(String^ title, String^ reportText) {
        this->components = gcnew System::ComponentModel::Container();
        this->Text = title;
        this->Size = System::Drawing::Size(500, 400);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
        this->BackColor = System::Drawing::Color::AliceBlue;

        this->labelContent = gcnew System::Windows::Forms::Label();
        this->labelContent->Text = reportText;
        this->labelContent->Location = System::Drawing::Point(20, 20);
        this->labelContent->Size = System::Drawing::Size(440, 340);
        this->labelContent->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.75f);
        this->labelContent->ForeColor = System::Drawing::Color::DarkBlue;
        this->labelContent->AutoSize = false;
        this->labelContent->MaximumSize = System::Drawing::Size(460, 0);
        this->Controls->Add(this->labelContent);
    }
}
