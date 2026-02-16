#pragma once

#include "BankClasses.h"

namespace BankSystemWinForms {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace System::Globalization;

    public ref class Form1 : public System::Windows::Forms::Form {
    public:
        Form1(void);
    protected:
        ~Form1();
    private:
        Bank^ bank;
        System::Windows::Forms::TabControl^ tabControl1;
        System::Windows::Forms::TabPage^ tabPageClients;
        System::Windows::Forms::TabPage^ tabPageDeposits;
        System::Windows::Forms::TabPage^ tabPageDBInfo;
        System::Windows::Forms::DataGridView^ dataGridViewClients;
        System::Windows::Forms::DataGridView^ dataGridViewDeposits;
        System::Windows::Forms::DataGridView^ dataGridViewDBInfo;
        System::Windows::Forms::Button^ btnAddClient;
        System::Windows::Forms::Button^ btnDeleteClient;
        System::Windows::Forms::Button^ btnEditClient;
        System::Windows::Forms::Button^ btnAddDeposit;
        System::Windows::Forms::Button^ btnDeleteDeposit;
        System::Windows::Forms::Button^ btnEditDeposit;
        System::Windows::Forms::Button^ btnOpenDeposit;
        System::Windows::Forms::Button^ btnCalculateInterest;
        System::Windows::Forms::Button^ btnTotalInterest;
        System::Windows::Forms::Button^ btnTopPayer;
        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::Button^ btnLoad;
        System::Windows::Forms::Button^ btnSort;
        System::Windows::Forms::Button^ btnExportToDB;
        System::Windows::Forms::Button^ btnImportFromDB;
        System::Windows::Forms::Button^ btnClearDB;
        System::Windows::Forms::Label^ labelStatus;
        System::Windows::Forms::Label^ labelDBInfo;
        System::ComponentModel::Container^ components;

        static String^ ShowInputBox(String^ prompt, String^ title, String^ defaultValue);
        static String^ ShowInputBoxWithMaxLength(String^ prompt, String^ title, String^ defaultValue, int maxLength);
        void InitializeComponent(void);
        void LoadDatabase();
        void LoadSampleData();
        void UpdateClientsGridView();
        void UpdateDepositsGridView();
        void UpdateDBInfoView();
        void UpdateDataGridViews();

        System::Void btnAddClient_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnEditClient_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnDeleteClient_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnAddDeposit_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnEditDeposit_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnDeleteDeposit_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnOpenDeposit_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnCalculateInterest_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnTotalInterest_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnTopPayer_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnLoad_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnSort_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnExportToDB_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnImportFromDB_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void btnClearDB_Click(System::Object^ sender, System::EventArgs^ e);
    };
}
