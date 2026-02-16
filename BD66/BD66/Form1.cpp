#include "Form1.h"

namespace BankSystemWinForms {
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::ComponentModel;

    Form1::Form1(void) {
        InitializeComponent();
        bank = Bank::getInstance();
        LoadDatabase();
        UpdateDataGridViews();
    }

    Form1::~Form1() {
        if (components) delete components;
    }

    String^ Form1::ShowInputBox(String^ prompt, String^ title, String^ defaultValue) {
        return ShowInputBoxWithMaxLength(prompt, title, defaultValue, 32767);
    }

    String^ Form1::ShowInputBoxWithMaxLength(String^ prompt, String^ title, String^ defaultValue, int maxLength) {
        Form^ form = gcnew Form();
        Label^ label = gcnew Label();
        TextBox^ textBox = gcnew TextBox();
        Button^ buttonOK = gcnew Button();
        Button^ buttonCancel = gcnew Button();
        form->Text = title;
        label->Text = prompt;
        textBox->Text = defaultValue;
        textBox->MaxLength = maxLength;
        buttonOK->Text = L"OK";
        buttonOK->DialogResult = System::Windows::Forms::DialogResult::OK;
        buttonCancel->Text = L"\u041e\u0442\u043c\u0435\u043d\u0430";
        buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        label->SetBounds(9, 20, 372, 13);
        textBox->SetBounds(12, 36, 372, 20);
        buttonOK->SetBounds(228, 72, 75, 23);
        buttonCancel->SetBounds(309, 72, 75, 23);
        form->ClientSize = System::Drawing::Size(396, 107);
        form->Controls->AddRange(gcnew array<Control^> { label, textBox, buttonOK, buttonCancel });
        form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        form->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
        form->MinimizeBox = false;
        form->MaximizeBox = false;
        form->AcceptButton = buttonOK;
        form->CancelButton = buttonCancel;
        if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            return textBox->Text;
        return String::Empty;
    }

    void Form1::InitializeComponent(void) {
        this->components = gcnew System::ComponentModel::Container();
        this->Text = L"\u0411\u0430\u043d\u043a\u043e\u0432\u0441\u043a\u0430\u044f \u0441\u0438\u0441\u0442\u0435\u043c\u0430";
        this->Size = System::Drawing::Size(850, 650);
        this->tabControl1 = gcnew TabControl();
        this->tabControl1->Location = System::Drawing::Point(12, 12);
        this->tabControl1->Size = System::Drawing::Size(810, 400);
        this->tabPageClients = gcnew TabPage();
        this->tabPageClients->Text = L"\u041a\u043b\u0438\u0435\u043d\u0442\u044b";
        this->dataGridViewClients = gcnew DataGridView();
        this->dataGridViewClients->Location = System::Drawing::Point(10, 10);
        this->dataGridViewClients->Size = System::Drawing::Size(770, 300);
        this->dataGridViewClients->ReadOnly = true;
        this->dataGridViewClients->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
        this->dataGridViewClients->AllowUserToAddRows = false;
        this->dataGridViewClients->AllowUserToDeleteRows = false;
        this->dataGridViewClients->RowHeadersVisible = false;
        this->dataGridViewClients->MultiSelect = false;
        this->dataGridViewClients->Columns->Add("ClientName", L"\u0418\u043c\u044f \u043a\u043b\u0438\u0435\u043d\u0442\u0430");
        this->dataGridViewClients->Columns->Add("DepositName", L"\u0422\u0438\u043f \u0432\u043a\u043b\u0430\u0434\u0430");
        this->dataGridViewClients->Columns->Add("Amount", L"\u0421\u0443\u043c\u043c\u0430");
        this->dataGridViewClients->Columns->Add("Interest", L"\u041f\u0440\u043e\u0446\u0435\u043d\u0442\u044b");
        this->tabPageDeposits = gcnew TabPage();
        this->tabPageDeposits->Text = L"\u0422\u0438\u043f\u044b \u0432\u043a\u043b\u0430\u0434\u043e\u0432";
        this->dataGridViewDeposits = gcnew DataGridView();
        this->dataGridViewDeposits->Location = System::Drawing::Point(10, 10);
        this->dataGridViewDeposits->Size = System::Drawing::Size(770, 300);
        this->dataGridViewDeposits->ReadOnly = true;
        this->dataGridViewDeposits->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
        this->dataGridViewDeposits->AllowUserToAddRows = false;
        this->dataGridViewDeposits->AllowUserToDeleteRows = false;
        this->dataGridViewDeposits->RowHeadersVisible = false;
        this->dataGridViewDeposits->MultiSelect = false;
        this->dataGridViewDeposits->Columns->Add("Number", L"\u2116");
        this->dataGridViewDeposits->Columns->Add("DepositTypeName", L"\u041d\u0430\u0437\u0432\u0430\u043d\u0438\u0435");
        this->dataGridViewDeposits->Columns->Add("InterestRate", L"\u0421\u0442\u0430\u0432\u043a\u0430 %");
        this->dataGridViewDeposits->Columns->Add("Category", L"\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f");
        this->dataGridViewDeposits->Columns[0]->Width = 40;
        this->tabPageDBInfo = gcnew TabPage();
        this->tabPageDBInfo->Text = L"\u0418\u043d\u0444\u043e\u0440\u043c\u0430\u0446\u0438\u044f \u0411\u0414";
        this->dataGridViewDBInfo = gcnew DataGridView();
        this->dataGridViewDBInfo->Location = System::Drawing::Point(10, 40);
        this->dataGridViewDBInfo->Size = System::Drawing::Size(770, 270);
        this->dataGridViewDBInfo->ReadOnly = true;
        this->dataGridViewDBInfo->AllowUserToAddRows = false;
        this->dataGridViewDBInfo->AllowUserToDeleteRows = false;
        this->dataGridViewDBInfo->RowHeadersVisible = false;
        this->labelDBInfo = gcnew Label();
        this->labelDBInfo->Text = L"\u0418\u043d\u0444\u043e\u0440\u043c\u0430\u0446\u0438\u044f \u043e \u0431\u0430\u0437\u0435 \u0434\u0430\u043d\u043d\u044b\u0445:";
        this->labelDBInfo->Location = System::Drawing::Point(10, 10);
        this->labelDBInfo->Size = System::Drawing::Size(300, 25);
        this->tabPageClients->Controls->Add(this->dataGridViewClients);
        this->tabPageDeposits->Controls->Add(this->dataGridViewDeposits);
        this->tabPageDBInfo->Controls->Add(this->labelDBInfo);
        this->tabPageDBInfo->Controls->Add(this->dataGridViewDBInfo);
        this->tabControl1->Controls->Add(this->tabPageClients);
        this->tabControl1->Controls->Add(this->tabPageDeposits);
        this->tabControl1->Controls->Add(this->tabPageDBInfo);
        this->btnAddClient = gcnew Button();
        this->btnAddClient->Text = L"\u0414\u043e\u0431\u0430\u0432\u0438\u0442\u044c \u043a\u043b\u0438\u0435\u043d\u0442\u0430";
        this->btnAddClient->Location = System::Drawing::Point(10, 320);
        this->btnAddClient->Size = System::Drawing::Size(110, 30);
        this->btnAddClient->Click += gcnew EventHandler(this, &Form1::btnAddClient_Click);
        this->btnEditClient = gcnew Button();
        this->btnEditClient->Text = L"\u0418\u0437\u043c\u0435\u043d\u0438\u0442\u044c \u043a\u043b\u0438\u0435\u043d\u0442\u0430";
        this->btnEditClient->Location = System::Drawing::Point(130, 320);
        this->btnEditClient->Size = System::Drawing::Size(110, 30);
        this->btnEditClient->Click += gcnew EventHandler(this, &Form1::btnEditClient_Click);
        this->btnDeleteClient = gcnew Button();
        this->btnDeleteClient->Text = L"\u0423\u0434\u0430\u043b\u0438\u0442\u044c \u043a\u043b\u0438\u0435\u043d\u0442\u0430";
        this->btnDeleteClient->Location = System::Drawing::Point(250, 320);
        this->btnDeleteClient->Size = System::Drawing::Size(110, 30);
        this->btnDeleteClient->Click += gcnew EventHandler(this, &Form1::btnDeleteClient_Click);
        this->btnOpenDeposit = gcnew Button();
        this->btnOpenDeposit->Text = L"\u041e\u0442\u043a\u0440\u044b\u0442\u044c \u0432\u043a\u043b\u0430\u0434";
        this->btnOpenDeposit->Location = System::Drawing::Point(370, 320);
        this->btnOpenDeposit->Size = System::Drawing::Size(110, 30);
        this->btnOpenDeposit->Click += gcnew EventHandler(this, &Form1::btnOpenDeposit_Click);
        this->btnCalculateInterest = gcnew Button();
        this->btnCalculateInterest->Text = L"\u0420\u0430\u0441\u0441\u0447\u0438\u0442\u0430\u0442\u044c %";
        this->btnCalculateInterest->Location = System::Drawing::Point(490, 320);
        this->btnCalculateInterest->Size = System::Drawing::Size(110, 30);
        this->btnCalculateInterest->Click += gcnew EventHandler(this, &Form1::btnCalculateInterest_Click);
        this->btnAddDeposit = gcnew Button();
        this->btnAddDeposit->Text = L"\u0414\u043e\u0431\u0430\u0432\u0438\u0442\u044c \u0442\u0438\u043f";
        this->btnAddDeposit->Location = System::Drawing::Point(10, 320);
        this->btnAddDeposit->Size = System::Drawing::Size(110, 30);
        this->btnAddDeposit->Click += gcnew EventHandler(this, &Form1::btnAddDeposit_Click);
        this->btnEditDeposit = gcnew Button();
        this->btnEditDeposit->Text = L"\u0418\u0437\u043c\u0435\u043d\u0438\u0442\u044c \u0442\u0438\u043f";
        this->btnEditDeposit->Location = System::Drawing::Point(130, 320);
        this->btnEditDeposit->Size = System::Drawing::Size(110, 30);
        this->btnEditDeposit->Click += gcnew EventHandler(this, &Form1::btnEditDeposit_Click);
        this->btnDeleteDeposit = gcnew Button();
        this->btnDeleteDeposit->Text = L"\u0423\u0434\u0430\u043b\u0438\u0442\u044c \u0442\u0438\u043f";
        this->btnDeleteDeposit->Location = System::Drawing::Point(250, 320);
        this->btnDeleteDeposit->Size = System::Drawing::Size(110, 30);
        this->btnDeleteDeposit->Click += gcnew EventHandler(this, &Form1::btnDeleteDeposit_Click);
        this->btnExportToDB = gcnew Button();
        this->btnExportToDB->Text = L"\u042d\u043a\u0441\u043f\u043e\u0440\u0442 \u0432 \u0411\u0414";
        this->btnExportToDB->Location = System::Drawing::Point(10, 320);
        this->btnExportToDB->Size = System::Drawing::Size(110, 30);
        this->btnExportToDB->Click += gcnew EventHandler(this, &Form1::btnExportToDB_Click);
        this->btnImportFromDB = gcnew Button();
        this->btnImportFromDB->Text = L"\u0418\u043c\u043f\u043e\u0440\u0442 \u0438\u0437 \u0411\u0414";
        this->btnImportFromDB->Location = System::Drawing::Point(130, 320);
        this->btnImportFromDB->Size = System::Drawing::Size(110, 30);
        this->btnImportFromDB->Click += gcnew EventHandler(this, &Form1::btnImportFromDB_Click);
        this->btnClearDB = gcnew Button();
        this->btnClearDB->Text = L"\u041e\u0447\u0438\u0441\u0442\u0438\u0442\u044c \u0411\u0414";
        this->btnClearDB->Location = System::Drawing::Point(250, 320);
        this->btnClearDB->Size = System::Drawing::Size(110, 30);
        this->btnClearDB->Click += gcnew EventHandler(this, &Form1::btnClearDB_Click);
        this->tabPageClients->Controls->Add(this->btnAddClient);
        this->tabPageClients->Controls->Add(this->btnEditClient);
        this->tabPageClients->Controls->Add(this->btnDeleteClient);
        this->tabPageClients->Controls->Add(this->btnOpenDeposit);
        this->tabPageClients->Controls->Add(this->btnCalculateInterest);
        this->tabPageDeposits->Controls->Add(this->btnAddDeposit);
        this->tabPageDeposits->Controls->Add(this->btnEditDeposit);
        this->tabPageDeposits->Controls->Add(this->btnDeleteDeposit);
        this->tabPageDBInfo->Controls->Add(this->btnExportToDB);
        this->tabPageDBInfo->Controls->Add(this->btnImportFromDB);
        this->tabPageDBInfo->Controls->Add(this->btnClearDB);
        this->btnTotalInterest = gcnew Button();
        this->btnTotalInterest->Text = L"\u041e\u0431\u0449\u0438\u0435 \u043f\u0440\u043e\u0446\u0435\u043d\u0442\u044b";
        this->btnTotalInterest->Location = System::Drawing::Point(12, 420);
        this->btnTotalInterest->Size = System::Drawing::Size(120, 30);
        this->btnTotalInterest->Click += gcnew EventHandler(this, &Form1::btnTotalInterest_Click);
        this->btnTopPayer = gcnew Button();
        this->btnTopPayer->Text = L"\u0422\u043e\u043f \u043a\u043b\u0438\u0435\u043d\u0442";
        this->btnTopPayer->Location = System::Drawing::Point(140, 420);
        this->btnTopPayer->Size = System::Drawing::Size(120, 30);
        this->btnTopPayer->Click += gcnew EventHandler(this, &Form1::btnTopPayer_Click);
        this->btnSave = gcnew Button();
        this->btnSave->Text = L"\u0421\u043e\u0445\u0440\u0430\u043d\u0438\u0442\u044c \u0432 \u0444\u0430\u0439\u043b";
        this->btnSave->Location = System::Drawing::Point(268, 420);
        this->btnSave->Size = System::Drawing::Size(120, 30);
        this->btnSave->Click += gcnew EventHandler(this, &Form1::btnSave_Click);
        this->btnLoad = gcnew Button();
        this->btnLoad->Text = L"\u0417\u0430\u0433\u0440\u0443\u0437\u0438\u0442\u044c \u0438\u0437 \u0444\u0430\u0439\u043b\u0430";
        this->btnLoad->Location = System::Drawing::Point(396, 420);
        this->btnLoad->Size = System::Drawing::Size(120, 30);
        this->btnLoad->Click += gcnew EventHandler(this, &Form1::btnLoad_Click);
        this->btnSort = gcnew Button();
        this->btnSort->Text = L"\u0421\u043e\u0440\u0442\u0438\u0440\u043e\u0432\u0430\u0442\u044c";
        this->btnSort->Location = System::Drawing::Point(524, 420);
        this->btnSort->Size = System::Drawing::Size(120, 30);
        this->btnSort->Click += gcnew EventHandler(this, &Form1::btnSort_Click);
        this->labelStatus = gcnew Label();
        this->labelStatus->Text = L"\u0413\u043e\u0442\u043e\u0432";
        this->labelStatus->Location = System::Drawing::Point(12, 470);
        this->labelStatus->Size = System::Drawing::Size(800, 20);
        this->labelStatus->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
        this->Controls->Add(this->tabControl1);
        this->Controls->Add(this->btnTotalInterest);
        this->Controls->Add(this->btnTopPayer);
        this->Controls->Add(this->btnSave);
        this->Controls->Add(this->btnLoad);
        this->Controls->Add(this->btnSort);
        this->Controls->Add(this->labelStatus);
    }

    void Form1::LoadDatabase() {
        if (bank->loadFromDatabase()) {
            labelStatus->Text = L"\u0411\u0430\u0437\u0430 \u0434\u0430\u043d\u043d\u044b\u0445 \u0437\u0430\u0433\u0440\u0443\u0436\u0435\u043d\u0430: " + DateTime::Now.ToString("HH:mm:ss");
            UpdateDBInfoView();
        } else {
            LoadSampleData();
        }
    }

    void Form1::LoadSampleData() {
        if (bank->getDepositTypes()->Count == 0) {
            bank->addDepositType(L"\u0421\u0431\u0435\u0440\u0435\u0433\u0430\u0442\u0435\u043b\u044c\u043d\u044b\u0439", 5.0, DepositCategory::SAVINGS);
            bank->addDepositType(L"\u041d\u0430\u043a\u043e\u043f\u0438\u0442\u0435\u043b\u044c\u043d\u044b\u0439", 7.5, DepositCategory::SAVINGS);
            bank->addDepositType(L"\u041a\u0440\u0430\u0442\u043a\u043e\u0441\u0440\u043e\u0447\u043d\u044b\u0439", 3.0, DepositCategory::SHORT_TERM);
        }
        if (bank->getClients()->Count == 0) {
            bank->addClient(L"\u0418\u0432\u0430\u043d\u043e\u0432 \u0418\u0432\u0430\u043d");
            bank->addClient(L"\u041f\u0435\u0442\u0440\u043e\u0432 \u041f\u0435\u0442\u0440");
            bank->addClient(L"\u0421\u0438\u0434\u043e\u0440\u043e\u0432\u0430 \u041c\u0430\u0440\u0438\u044f");
            bank->makeDeposit(L"\u0418\u0432\u0430\u043d\u043e\u0432 \u0418\u0432\u0430\u043d", L"\u0421\u0431\u0435\u0440\u0435\u0433\u0430\u0442\u0435\u043b\u044c\u043d\u044b\u0439", 100000);
            bank->makeDeposit(L"\u041f\u0435\u0442\u0440\u043e\u0432 \u041f\u0435\u0442\u0440", L"\u041d\u0430\u043a\u043e\u043f\u0438\u0442\u0435\u043b\u044c\u043d\u044b\u0439", 150000);
        }
    }

    void Form1::UpdateClientsGridView() {
        dataGridViewClients->Rows->Clear();
        for each(Client^ client in bank->getClients()) {
            int index = dataGridViewClients->Rows->Add();
            dataGridViewClients->Rows[index]->Cells[0]->Value = client->firstName;
            if (client->depositType != nullptr) {
                dataGridViewClients->Rows[index]->Cells[1]->Value = client->depositType->name;
                dataGridViewClients->Rows[index]->Cells[2]->Value = client->depositAmount.ToString("F2");
                double interest = client->depositAmount * client->depositType->interestRate / 100.0;
                dataGridViewClients->Rows[index]->Cells[3]->Value = interest.ToString("F2");
            } else {
                dataGridViewClients->Rows[index]->Cells[1]->Value = L"\u041d\u0435\u0442 \u0432\u043a\u043b\u0430\u0434\u0430";
                dataGridViewClients->Rows[index]->Cells[2]->Value = L"0.00";
                dataGridViewClients->Rows[index]->Cells[3]->Value = L"0.00";
            }
        }
    }

    void Form1::UpdateDepositsGridView() {
        dataGridViewDeposits->Rows->Clear();
        int number = 1;
        for each(DepositType^ type in bank->getDepositTypes()) {
            int index = dataGridViewDeposits->Rows->Add();
            dataGridViewDeposits->Rows[index]->Cells[0]->Value = number++.ToString();
            dataGridViewDeposits->Rows[index]->Cells[1]->Value = type->name;
            dataGridViewDeposits->Rows[index]->Cells[2]->Value = type->interestRate.ToString("F2");
            dataGridViewDeposits->Rows[index]->Cells[3]->Value = type->getCategoryString();
        }
    }

    void Form1::UpdateDBInfoView() {
        dataGridViewDBInfo->Rows->Clear();
        dataGridViewDBInfo->Columns->Clear();
        dataGridViewDBInfo->Columns->Add("Parameter", L"\u041f\u0430\u0440\u0430\u043c\u0435\u0442\u0440");
        dataGridViewDBInfo->Columns->Add("Value", L"\u0417\u043d\u0430\u0447\u0435\u043d\u0438\u0435");
        int row1 = dataGridViewDBInfo->Rows->Add();
        dataGridViewDBInfo->Rows[row1]->Cells[0]->Value = L"\u041a\u043e\u043b\u0438\u0447\u0435\u0441\u0442\u0432\u043e \u043a\u043b\u0438\u0435\u043d\u0442\u043e\u0432";
        dataGridViewDBInfo->Rows[row1]->Cells[1]->Value = bank->getClients()->Count.ToString();
        int row2 = dataGridViewDBInfo->Rows->Add();
        dataGridViewDBInfo->Rows[row2]->Cells[0]->Value = L"\u041a\u043e\u043b\u0438\u0447\u0435\u0441\u0442\u0432\u043e \u0442\u0438\u043f\u043e\u0432 \u0432\u043a\u043b\u0430\u0434\u043e\u0432";
        dataGridViewDBInfo->Rows[row2]->Cells[1]->Value = bank->getDepositTypes()->Count.ToString();
        int row3 = dataGridViewDBInfo->Rows->Add();
        dataGridViewDBInfo->Rows[row3]->Cells[0]->Value = L"\u041e\u0431\u0449\u0430\u044f \u0441\u0443\u043c\u043c\u0430 \u0432\u043a\u043b\u0430\u0434\u043e\u0432";
        dataGridViewDBInfo->Rows[row3]->Cells[1]->Value = bank->getTotalDeposits().ToString("F2");
        int row4 = dataGridViewDBInfo->Rows->Add();
        dataGridViewDBInfo->Rows[row4]->Cells[0]->Value = L"\u041e\u0431\u0449\u0438\u0435 \u043f\u0440\u043e\u0446\u0435\u043d\u0442\u044b";
        dataGridViewDBInfo->Rows[row4]->Cells[1]->Value = bank->calculateTotalInterest().ToString("F2");
        int row5 = dataGridViewDBInfo->Rows->Add();
        dataGridViewDBInfo->Rows[row5]->Cells[0]->Value = L"\u0411\u0430\u0437\u0430 \u0434\u0430\u043d\u043d\u044b\u0445";
        dataGridViewDBInfo->Rows[row5]->Cells[1]->Value = L"SQLite (bank.db)";
        dataGridViewDBInfo->AutoResizeColumns(DataGridViewAutoSizeColumnsMode::AllCells);
    }

    void Form1::UpdateDataGridViews() {
        UpdateClientsGridView();
        UpdateDepositsGridView();
        UpdateDBInfoView();
        labelStatus->Text = L"\u0414\u0430\u043d\u043d\u044b\u0435 \u043e\u0431\u043d\u043e\u0432\u043b\u0435\u043d\u044b: " + DateTime::Now.ToString("HH:mm:ss");
    }

    void Form1::btnExportToDB_Click(System::Object^ sender, System::EventArgs^ e) {
        SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
        saveDialog->Filter = L"\u0411\u0430\u0437\u0430 \u0434\u0430\u043d\u043d\u044b\u0445 (*.db)|*.db|\u0412\u0441\u0435 \u0444\u0430\u0439\u043b\u044b (*.*)|*.*";
        saveDialog->Title = L"\u042d\u043a\u0441\u043f\u043e\u0440\u0442 \u0432 \u0411\u0414";
        saveDialog->DefaultExt = L"db";
        saveDialog->FileName = L"bank.db";
        if (saveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            if (bank->saveToDatabase(saveDialog->FileName)) {
                UpdateDBInfoView();
                labelStatus->Text = L"\u0414\u0430\u043d\u043d\u044b\u0445 \u044d\u043a\u0441\u043f\u043e\u0440\u0442\u0438\u0440\u043e\u0432\u0430\u043d\u044b \u0432: " + saveDialog->FileName;
                MessageBox::Show(L"\u0414\u0430\u043d\u043d\u044b\u0445 \u0443\u0441\u043f\u0435\u0448\u043d\u043e \u0441\u043e\u0445\u0440\u0430\u043d\u0435\u043d\u044b \u0432 \u0431\u0430\u0437\u0443 \u0434\u0430\u043d\u043d\u044b\u0445!", L"\u042d\u043a\u0441\u043f\u043e\u0440\u0442", MessageBoxButtons::OK, MessageBoxIcon::Information);
            } else {
                MessageBox::Show(L"\u041e\u0448\u0438\u0431\u043a\u0430 \u043f\u0440\u0438 \u0441\u043e\u0445\u0440\u0430\u043d\u0435\u043d\u0438\u0438 \u0432 \u0431\u0430\u0437\u0443 \u0434\u0430\u043d\u043d\u044b\u0445!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    void Form1::btnImportFromDB_Click(System::Object^ sender, System::EventArgs^ e) {
        OpenFileDialog^ openDialog = gcnew OpenFileDialog();
        openDialog->Filter = L"\u0411\u0430\u0437\u0430 \u0434\u0430\u043d\u043d\u044b\u0445 (*.db)|*.db|\u0412\u0441\u0435 \u0444\u0430\u0439\u043b\u044b (*.*)|*.*";
        openDialog->Title = L"\u0418\u043c\u043f\u043e\u0440\u0442 \u0438\u0437 \u0411\u0414";
        if (openDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            if (bank->loadFromDatabase(openDialog->FileName)) {
                UpdateDataGridViews();
                labelStatus->Text = L"\u0414\u0430\u043d\u043d\u044b\u0445 \u0437\u0430\u0433\u0440\u0443\u0436\u0435\u043d\u044b \u0438\u0437: " + openDialog->FileName;
                MessageBox::Show(L"\u0414\u0430\u043d\u043d\u044b\u0445 \u0443\u0441\u043f\u0435\u0448\u043d\u043e \u0437\u0430\u0433\u0440\u0443\u0436\u0435\u043d\u044b \u0438\u0437 \u0431\u0430\u0437\u044b \u0434\u0430\u043d\u043d\u044b\u0445!", L"\u0418\u043c\u043f\u043e\u0440\u0442", MessageBoxButtons::OK, MessageBoxIcon::Information);
            } else {
                MessageBox::Show(L"\u041e\u0448\u0438\u0431\u043a\u0430 \u043f\u0440\u0438 \u0437\u0430\u0433\u0440\u0443\u0437\u043a\u0435 \u0438\u0437 \u0431\u0430\u0437\u044b \u0434\u0430\u043d\u043d\u044b\u0445!\n\u0424\u0430\u0439\u043b \u043d\u0435 \u043d\u0430\u0439\u0434\u0435\u043d \u0438\u043b\u0438 \u043d\u0435\u0432\u0435\u0440\u043d\u044b\u0439 \u0444\u043e\u0440\u043c\u0430\u0442.", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

    void Form1::btnClearDB_Click(System::Object^ sender, System::EventArgs^ e) {
        System::Windows::Forms::DialogResult result = MessageBox::Show(
            L"\u0412\u044b \u0434\u0435\u0439\u0441\u0442\u0432\u0438\u0442\u0435\u043b\u044c\u043d\u043e \u0445\u043e\u0442\u0438\u0442\u0435 \u043e\u0447\u0438\u0441\u0442\u0438\u0442\u044c \u0431\u0430\u0437\u0443 \u0434\u0430\u043d\u043d\u044b\u0445?\n\u0412\u0441\u0435 \u0434\u0430\u043d\u043d\u044b\u0445 \u0431\u0443\u0434\u0443\u0442 \u0443\u0434\u0430\u043b\u0435\u043d\u044b!",
            L"\u041f\u043e\u0434\u0442\u0432\u0435\u0440\u0436\u0434\u0435\u043d\u0438\u0435 \u043e\u0447\u0438\u0441\u0442\u043a\u0438 \u0411\u0414", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
        if (result == System::Windows::Forms::DialogResult::Yes) {
            if (bank->clearDatabase()) {
                bank->getClients()->Clear();
                bank->getDepositTypes()->Clear();
                UpdateDataGridViews();
                labelStatus->Text = L"\u0411\u0430\u0437\u0430 \u0434\u0430\u043d\u043d\u044b\u0445 \u043e\u0447\u0438\u0449\u0435\u043d\u0430";
            }
        }
    }

    void Form1::btnAddClient_Click(System::Object^ sender, System::EventArgs^ e) {
        String^ name = ShowInputBoxWithMaxLength(L"\u0412\u0432\u0435\u0434\u0438\u0442\u0435 \u0438\u043c\u044f \u043a\u043b\u0438\u0435\u043d\u0442\u0430:", L"\u0414\u043e\u0431\u0430\u0432\u043b\u0435\u043d\u0438\u044f \u043a\u043b\u0438\u0435\u043d\u0442\u0430", L"", 20);
        if (String::IsNullOrEmpty(name)) return;
        if (name->Length > 20) {
            MessageBox::Show(L"\u0418\u043c\u044f \u043d\u0435 \u0434\u043e\u043b\u0436\u043d\u043e \u043f\u0440\u0435\u0432\u044b\u0448\u0430\u0442\u044c 20 \u0441\u0438\u043c\u0432\u043e\u043b\u043e\u0432!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        if (bank->findClient(name) != nullptr) {
            MessageBox::Show(L"\u041a\u043b\u0438\u0435\u043d\u0442 \u0441 \u0442\u0430\u043a\u0438\u043c \u0438\u043c\u0435\u043d\u0435\u043c \u0443\u0436\u0435 \u0441\u0443\u0449\u0435\u0441\u0442\u0432\u0443\u0435\u0442!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        bank->addClient(name);
        bank->saveToDatabase();
        UpdateDataGridViews();
        labelStatus->Text = L"\u041a\u043b\u0438\u0435\u043d\u0442 '" + name + L"' \u0434\u043e\u0431\u0430\u0432\u043b\u0435\u043d";
    }

    void Form1::btnEditClient_Click(System::Object^ sender, System::EventArgs^ e) {
        if (dataGridViewClients->SelectedRows->Count == 0) {
            MessageBox::Show(L"\u0412\u044b\u0431\u0435\u0440\u0438\u0442\u0435 \u043a\u043b\u0438\u0435\u043d\u0442\u0430", L"\u0418\u043d\u0444\u043e\u0440\u043c\u0430\u0446\u0438\u044f", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }
        DataGridViewRow^ row = dataGridViewClients->SelectedRows[0];
        String^ oldName = row->Cells[0]->Value->ToString();
        String^ newName = ShowInputBoxWithMaxLength(L"\u041d\u043e\u0432\u043e\u0435 \u0438\u043c\u044f:", L"\u0418\u0437\u043c\u0435\u043d\u0435\u043d\u0438\u044f", oldName, 20);
        if (String::IsNullOrEmpty(newName) || newName == oldName) return;
        if (newName->Length > 20) {
            MessageBox::Show(L"\u0418\u043c\u044f \u043d\u0435 \u0434\u043e\u043b\u0436\u043d\u043e \u043f\u0440\u0435\u0432\u044b\u0448\u0430\u0442\u044c 20 \u0441\u0438\u043c\u0432\u043e\u043b\u043e\u0432!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        if (bank->editClient(oldName, newName)) {
            bank->saveToDatabase();
            UpdateDataGridViews();
            labelStatus->Text = L"\u041a\u043b\u0438\u0435\u043d\u0442 \u0438\u0437\u043c\u0435\u043d\u0451\u043d";
        }
    }

    void Form1::btnDeleteClient_Click(System::Object^ sender, System::EventArgs^ e) {
        if (dataGridViewClients->SelectedRows->Count == 0) {
            MessageBox::Show(L"\u0412\u044b\u0431\u0435\u0440\u0438\u0442\u0435 \u043a\u043b\u0438\u0435\u043d\u0442\u0430", L"\u0418\u043d\u0444\u043e\u0440\u043c\u0430\u0446\u0438\u044f", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }
        String^ name = dataGridViewClients->SelectedRows[0]->Cells[0]->Value->ToString();
        if (MessageBox::Show(L"\u0423\u0434\u0430\u043b\u0438\u0442\u044c '" + name + L"'?", L"\u041f\u043e\u0434\u0442\u0432\u0435\u0440\u0436\u0434\u0435\u043d\u0438\u0435", MessageBoxButtons::YesNo, MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::Yes) return;
        if (bank->removeClient(name)) {
            bank->saveToDatabase();
            UpdateDataGridViews();
            labelStatus->Text = L"\u041a\u043b\u0438\u0435\u043d\u0442 \u0443\u0434\u0430\u043b\u0451\u043d";
        }
    }

    void Form1::btnAddDeposit_Click(System::Object^ sender, System::EventArgs^ e) {
        String^ name = ShowInputBoxWithMaxLength(L"\u041d\u0430\u0437\u0432\u0430\u043d\u0438\u0435 \u0432\u043a\u043b\u0430\u0434\u0430:", L"\u0414\u043e\u0431\u0430\u0432\u0438\u0442\u044c \u0442\u0438\u043f", L"", 20);
        if (String::IsNullOrEmpty(name) || name->Length > 20) return;
        if (bank->findDepositType(name) != nullptr) {
            MessageBox::Show(L"\u0422\u0438\u043f \u0441 \u0442\u0430\u043a\u0438\u043c \u043d\u0430\u0437\u0432\u0430\u043d\u0438\u0435\u043c \u0443\u0436\u0435 \u0435\u0441\u0442\u044c!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        String^ rateStr = ShowInputBox(L"\u041f\u0440\u043e\u0446\u0435\u043d\u0442\u043d\u0430\u044f \u0441\u0442\u0430\u0432\u043a\u0430 (5.0 \u0438\u043b\u0438 7.5):", L"\u0421\u0442\u0430\u0432\u043a\u0430", L"5.0");
        if (String::IsNullOrEmpty(rateStr)) return;
        rateStr = rateStr->Trim()->Replace(L",", L".");
        double rate;
        if (!Double::TryParse(rateStr, System::Globalization::NumberStyles::Any, System::Globalization::CultureInfo::InvariantCulture, rate) || rate <= 0 || rate > 1000000) {
            MessageBox::Show(L"\u0412\u0432\u0435\u0434\u0438\u0442\u0435 \u043a\u043e\u0440\u0440\u0435\u043a\u0442\u043d\u0443\u044e \u0441\u0442\u0430\u0432\u043a\u0443 (0 \u2014 1 000 000)!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        String^ catStr = ShowInputBox(L"\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f: 1-\u041a\u0440\u0430\u0442\u043a\u043e\u0441\u0440. 2-\u0414\u043e\u043b\u0433\u043e\u0441\u0440. 3-\u0421\u043f\u0435\u0446. 4-\u041d\u0430\u043a\u043e\u043f.", L"\u041a\u0430\u0442\u0435\u0433\u043e\u0440\u0438\u044f", L"1");
        int c;
        if (!Int32::TryParse(catStr, c) || c < 1 || c > 4) { MessageBox::Show(L"\u0412\u0432\u0435\u0434\u0438\u0442\u0435 1-4", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error); return; }
        DepositCategory cat = (DepositCategory)(c - 1);
        bank->addDepositType(name, rate, cat);
        bank->saveToDatabase();
        UpdateDataGridViews();
        labelStatus->Text = L"\u0422\u0438\u043f '" + name + L"' \u0434\u043e\u0431\u0430\u0432\u043b\u0435\u043d";
    }

    void Form1::btnEditDeposit_Click(System::Object^ sender, System::EventArgs^ e) {
        if (dataGridViewDeposits->SelectedRows->Count == 0) {
            MessageBox::Show(L"\u0412\u044b\u0431\u0435\u0440\u0438\u0442\u0435 \u0442\u0438\u043f \u0432\u043a\u043b\u0430\u0434\u0430", L"\u0418\u043d\u0444\u043e\u0440\u043c\u0430\u0446\u0438\u044f", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }
        DataGridViewRow^ row = dataGridViewDeposits->SelectedRows[0];
        String^ oldName = row->Cells[1]->Value->ToString();
        String^ newName = ShowInputBoxWithMaxLength(L"\u041d\u043e\u0432\u043e\u0435 \u043d\u0430\u0437\u0432\u0430\u043d\u0438\u0435:", L"\u0418\u0437\u043c\u0435\u043d\u0438\u0442\u044c", oldName, 20);
        if (String::IsNullOrEmpty(newName) || newName == oldName) return;
        String^ rateStr = ShowInputBox(L"\u041d\u043e\u0432\u0430\u044f \u0441\u0442\u0430\u0432\u043a\u0430:", L"\u0421\u0442\u0430\u0432\u043a\u0430", row->Cells[2]->Value->ToString());
        if (String::IsNullOrEmpty(rateStr)) return;
        rateStr = rateStr->Trim()->Replace(L",", L".");
        double newRate;
        if (!Double::TryParse(rateStr, System::Globalization::NumberStyles::Any, System::Globalization::CultureInfo::InvariantCulture, newRate) || newRate <= 0 || newRate > 1000000) {
            MessageBox::Show(L"\u0412\u0432\u0435\u0434\u0438\u0442\u0435 \u043a\u043e\u0440\u0440\u0435\u043a\u0442\u043d\u0443\u044e \u0441\u0442\u0430\u0432\u043a\u0443 (0 \u2014 1 000 000)!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        if (bank->editDepositType(oldName, newName, newRate)) {
            bank->saveToDatabase();
            UpdateDataGridViews();
            labelStatus->Text = L"\u0422\u0438\u043f \u0432\u043a\u043b\u0430\u0434\u0430 \u0438\u0437\u043c\u0435\u043d\u0451\u043d";
        }
    }

    void Form1::btnDeleteDeposit_Click(System::Object^ sender, System::EventArgs^ e) {
        if (dataGridViewDeposits->SelectedRows->Count == 0) {
            MessageBox::Show(L"\u0412\u044b\u0431\u0435\u0440\u0438\u0442\u0435 \u0442\u0438\u043f \u0432\u043a\u043b\u0430\u0434\u0430", L"\u0418\u043d\u0444\u043e\u0440\u043c\u0430\u0446\u0438\u044f", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }
        String^ name = dataGridViewDeposits->SelectedRows[0]->Cells[1]->Value->ToString();
        if (MessageBox::Show(L"\u0423\u0434\u0430\u043b\u0438\u0442\u044c \u0442\u0438\u043f '" + name + L"'?", L"\u041f\u043e\u0434\u0442\u0432\u0435\u0440\u0436\u0434\u0435\u043d\u0438\u0435", MessageBoxButtons::YesNo, MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::Yes) return;
        if (bank->removeDepositType(name)) {
            bank->saveToDatabase();
            UpdateDataGridViews();
            labelStatus->Text = L"\u0422\u0438\u043f \u0443\u0434\u0430\u043b\u0451\u043d";
        } else {
            MessageBox::Show(L"\u041d\u0435\u043b\u044c\u0437\u044f \u0443\u0434\u0430\u043b\u0438\u0442\u044c \u2014 \u0442\u0438\u043f \u0438\u0441\u043f\u043e\u043b\u044c\u0437\u0443\u0435\u0442\u0441\u044f \u043a\u043b\u0438\u0435\u043d\u0442\u0430\u043c\u0438!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void Form1::btnOpenDeposit_Click(System::Object^ sender, System::EventArgs^ e) {
        if (dataGridViewClients->SelectedRows->Count == 0) {
            MessageBox::Show(L"\u0412\u044b\u0431\u0435\u0440\u0438\u0442\u0435 \u043a\u043b\u0438\u0435\u043d\u0442\u0430", L"\u0418\u043d\u0444\u043e\u0440\u043c\u0430\u0446\u0438\u044f", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }
        if (bank->getDepositTypes()->Count == 0) {
            MessageBox::Show(L"\u0414\u043e\u0431\u0430\u0432\u044c\u0442\u0435 \u0441\u043d\u0430\u0447\u0430\u043b\u0430 \u0442\u0438\u043f\u044b \u0432\u043a\u043b\u0430\u0434\u043e\u0432!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        String^ clientName = dataGridViewClients->SelectedRows[0]->Cells[0]->Value->ToString();
        String^ depositList = L"";
        for (int i = 0; i < bank->getDepositTypes()->Count; i++)
            depositList += (i + 1).ToString() + L". " + bank->getDepositTypes()[i]->name + L" (" + bank->getDepositTypes()[i]->interestRate.ToString("F1") + L"%)\n";
        String^ choice = ShowInputBox(L"\u0412\u044b\u0431\u0435\u0440\u0438\u0442\u0435 \u0442\u0438\u043f \u0432\u043a\u043b\u0430\u0434\u0430 \u0434\u043b\u044f " + clientName + L":\n" + depositList, L"\u041e\u0442\u043a\u0440\u044b\u0442\u044c \u0432\u043a\u043b\u0430\u0434", L"1");
        int idx;
        if (!Int32::TryParse(choice, idx) || idx < 1 || idx > bank->getDepositTypes()->Count) return;
        String^ amountStr = ShowInputBox(L"\u0421\u0443\u043c\u043c\u0430 \u0432\u043a\u043b\u0430\u0434\u0430:", L"\u0421\u0443\u043c\u043c\u0430", L"1000");
        if (String::IsNullOrEmpty(amountStr)) return;
        amountStr = amountStr->Replace(L",", L".");
        double amount;
        if (!Double::TryParse(amountStr, System::Globalization::NumberStyles::Any, System::Globalization::CultureInfo::InvariantCulture, amount) || amount <= 0 || amount > 100000000000) {
            MessageBox::Show(L"\u0412\u0432\u0435\u0434\u0438\u0442\u0435 \u043a\u043e\u0440\u0440\u0435\u043a\u0442\u043d\u0443\u044e \u0441\u0443\u043c\u043c\u0443!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }
        String^ depositName = bank->getDepositTypes()[idx - 1]->name;
        if (bank->makeDeposit(clientName, depositName, amount)) {
            bank->saveToDatabase();
            UpdateDataGridViews();
            labelStatus->Text = L"\u0412\u043a\u043b\u0430\u0434 \u043e\u0442\u043a\u0440\u044b\u0442 \u0434\u043b\u044f " + clientName;
        }
    }

    void Form1::btnCalculateInterest_Click(System::Object^ sender, System::EventArgs^ e) {
        if (dataGridViewClients->SelectedRows->Count == 0) {
            MessageBox::Show(L"\u0412\u044b\u0431\u0435\u0440\u0438\u0442\u0435 \u043a\u043b\u0438\u0435\u043d\u0442\u0430", L"\u0418\u043d\u0444\u043e\u0440\u043c\u0430\u0446\u0438\u044f", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }
        String^ name = dataGridViewClients->SelectedRows[0]->Cells[0]->Value->ToString();
        double interest = bank->calculateClientInterest(name);
        MessageBox::Show(L"\u041f\u0440\u043e\u0446\u0435\u043d\u0442\u044b: " + interest.ToString("F2"), L"\u0420\u0430\u0441\u0447\u0451\u0442");
    }

    void Form1::btnTotalInterest_Click(System::Object^ sender, System::EventArgs^ e) {
        double total = bank->calculateTotalInterest();
        MessageBox::Show(L"\u041e\u0431\u0449\u0438\u0435 \u043f\u0440\u043e\u0446\u0435\u043d\u0442\u044b: " + total.ToString("F2"), L"\u0420\u0430\u0441\u0447\u0451\u0442");
    }

    void Form1::btnTopPayer_Click(System::Object^ sender, System::EventArgs^ e) {
        Client^ top = bank->findTopPayer();
        if (top == nullptr) {
            MessageBox::Show(L"\u041d\u0435\u0442 \u043a\u043b\u0438\u0435\u043d\u0442\u043e\u0432 \u0441 \u0432\u043a\u043b\u0430\u0434\u0430\u043c\u0438", L"\u0418\u043d\u0444\u043e\u0440\u043c\u0430\u0446\u0438\u044f");
            return;
        }
        double interest = bank->calculateClientInterest(top->firstName);
        MessageBox::Show(L"\u0422\u043e\u043f \u043a\u043b\u0438\u0435\u043d\u0442: " + top->firstName + L"\n\u041f\u0440\u043e\u0446\u0435\u043d\u0442\u044b: " + interest.ToString("F2"), L"\u0422\u043e\u043f-\u043a\u043b\u0438\u0435\u043d\u0442");
    }

    void Form1::btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
        SaveFileDialog^ dlg = gcnew SaveFileDialog();
        dlg->Filter = L"\u0422\u0435\u043a\u0441\u0442 (*.txt)|*.txt|*.*|*.*";
        dlg->Title = L"\u0421\u043e\u0445\u0440\u0430\u043d\u0438\u0442\u044c \u0432 \u0444\u0430\u0439\u043b";
        dlg->DefaultExt = L"txt";
        if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
        if (bank->saveToFile(dlg->FileName))
            labelStatus->Text = L"\u0421\u043e\u0445\u0440\u0430\u043d\u0435\u043d\u043e: " + dlg->FileName;
        else
            MessageBox::Show(L"\u041e\u0448\u0438\u0431\u043a\u0430 \u0441\u043e\u0445\u0440\u0430\u043d\u0435\u043d\u0438\u044f!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }

    void Form1::btnLoad_Click(System::Object^ sender, System::EventArgs^ e) {
        OpenFileDialog^ dlg = gcnew OpenFileDialog();
        dlg->Filter = L"\u0422\u0435\u043a\u0441\u0442 (*.txt)|*.txt|*.*|*.*";
        dlg->Title = L"\u0417\u0430\u0433\u0440\u0443\u0437\u0438\u0442\u044c \u0438\u0437 \u0444\u0430\u0439\u043b\u0430";
        if (dlg->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
        if (bank->loadFromFile(dlg->FileName)) {
            bank->saveToDatabase();
            UpdateDataGridViews();
            labelStatus->Text = L"\u0417\u0430\u0433\u0440\u0443\u0436\u0435\u043d\u043e: " + dlg->FileName;
        } else {
            MessageBox::Show(L"\u041e\u0448\u0438\u0431\u043a\u0430 \u0437\u0430\u0433\u0440\u0443\u0437\u043a\u0438!", L"\u041e\u0448\u0438\u0431\u043a\u0430", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void Form1::btnSort_Click(System::Object^ sender, System::EventArgs^ e) {
        bank->sortClientsByName();
        UpdateDataGridViews();
        labelStatus->Text = L"\u041a\u043b\u0438\u0435\u043d\u0442\u044b \u043e\u0442\u0441\u043e\u0440\u0442\u0438\u0440\u043e\u0432\u0430\u043d\u044b";
    }
}
