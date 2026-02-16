#pragma once

#include "BankClasses.h"

namespace BankSystemWinForms {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    // Второе (не главное) окно с перегрузкой конструктора для разных сценариев отображения
    public ref class Form2 : public System::Windows::Forms::Form {
    public:
        // Конструктор по умолчанию — режим "Справка"
        Form2(void);

        // Перегрузка: сценарий 1 — информационный режим (светлый фон, заголовок "Справка")
        Form2(int viewMode);

        // Перегрузка: сценарий 2 — режим отчёта (другой заголовок и цвет фона)
        Form2(String^ title, String^ reportText);

    protected:
        ~Form2();

    private:
        void InitializeComponent(void);
        void InitializeComponent(int viewMode);
        void InitializeComponent(String^ title, String^ reportText);

        System::Windows::Forms::Label^ labelContent;
        System::ComponentModel::Container^ components;
    };
}
