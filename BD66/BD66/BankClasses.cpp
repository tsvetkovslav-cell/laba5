#include "BankClasses.h"

using namespace System::Data::SQLite;

// ==================== DepositType ====================
DepositType::DepositType(System::String^ n, double rate, DepositCategory cat) {
    name = n;
    interestRate = rate;
    category = cat;
}

System::String^ DepositType::getCategoryString() {
    switch (category) {
    case DepositCategory::SHORT_TERM: return L"\u041a\u0440\u0430\u0442\u043a\u043e\u0441\u0440\u043e\u0447\u043d\u044b\u0439";
    case DepositCategory::LONG_TERM: return L"\u0414\u043e\u043b\u0433\u043e\u0441\u0440\u043e\u0447\u043d\u044b\u0439";
    case DepositCategory::SPECIAL: return L"\u0421\u043f\u0435\u0446\u0438\u0430\u043b\u044c\u043d\u044b\u0439";
    case DepositCategory::SAVINGS: return L"\u041d\u0430\u043a\u043e\u043f\u0438\u0442\u0435\u043b\u044c\u043d\u044b\u0439";
    default: return L"\u041d\u0435\u0438\u0437\u0432\u0435\u0441\u0442\u043d\u043e";
    }
}

// ==================== Client ====================
Client::Client(System::String^ first) {
    firstName = first;
    depositAmount = 0.0;
    depositType = nullptr;
}

// ==================== Bank ====================
Bank::Bank() {
    depositTypes = gcnew List<DepositType^>();
    clients = gcnew List<Client^>();
}

Bank^ Bank::getInstance() {
    if (instance == nullptr) {
        instance = gcnew Bank();
    }
    return instance;
}

void Bank::addDepositType(System::String^ name, double rate, DepositCategory category) {
    if (rate <= 0 || rate > 1000000) return;  // Ограничение ставки до 1 000 000%
    depositTypes->Add(gcnew DepositType(name, rate, category));
}

void Bank::addClient(System::String^ firstName) {
    clients->Add(gcnew Client(firstName));
}

bool Bank::editClient(System::String^ oldName, System::String^ newName) {
    Client^ client = findClient(oldName);
    if (client != nullptr && findClient(newName) == nullptr) {
        client->firstName = newName;
        return true;
    }
    return false;
}

bool Bank::editDepositType(System::String^ oldName, System::String^ newName, double newRate) {
    if (newRate <= 0 || newRate > 1000000) return false;  // Ограничение ставки до 1 000 000%
    DepositType^ type = findDepositType(oldName);
    if (type != nullptr && (newName->Equals(oldName) || findDepositType(newName) == nullptr)) {
        type->name = newName;
        type->interestRate = newRate;
        return true;
    }
    return false;
}

bool Bank::makeDeposit(System::String^ clientName, System::String^ depositName, double amount) {
    Client^ client = findClient(clientName);
    DepositType^ type = findDepositType(depositName);
    if (client != nullptr && type != nullptr && amount > 0 && amount <= 100000000000) {
        client->depositAmount = amount;
        client->depositType = type;
        return true;
    }
    return false;
}

double Bank::calculateClientInterest(System::String^ clientName) {
    Client^ client = findClient(clientName);
    if (client != nullptr && client->depositType != nullptr && client->depositAmount > 0) {
        return client->depositAmount * client->depositType->interestRate / 100.0;
    }
    return 0.0;
}

double Bank::calculateTotalInterest() {
    double total = 0.0;
    for each(Client ^ client in clients) {
        if (client->depositType != nullptr && client->depositAmount > 0) {
            total += client->depositAmount * client->depositType->interestRate / 100.0;
        }
    }
    return total;
}

Client^ Bank::findTopPayer() {
    Client^ topClient = nullptr;
    double maxInterest = 0.0;
    for each(Client ^ client in clients) {
        if (client->depositType != nullptr && client->depositAmount > 0) {
            double interest = client->depositAmount * client->depositType->interestRate / 100.0;
            if (interest > maxInterest) {
                maxInterest = interest;
                topClient = client;
            }
        }
    }
    return topClient;
}

void Bank::sortClientsByName() {
    for (int i = 0; i < clients->Count - 1; i++) {
        for (int j = i + 1; j < clients->Count; j++) {
            if (String::Compare(clients[i]->firstName, clients[j]->firstName) > 0) {
                Client^ temp = clients[i];
                clients[i] = clients[j];
                clients[j] = temp;
            }
        }
    }
}

double Bank::getTotalDeposits() {
    double total = 0.0;
    for each(Client ^ client in clients) {
        if (client->depositAmount > 0) {
            total += client->depositAmount;
        }
    }
    return total;
}

Client^ Bank::findClient(System::String^ name) {
    for each(Client ^ client in clients) {
        if (client->firstName->Equals(name)) {
            return client;
        }
    }
    return nullptr;
}

DepositType^ Bank::findDepositType(System::String^ name) {
    for each(DepositType ^ type in depositTypes) {
        if (type->name->Equals(name)) {
            return type;
        }
    }
    return nullptr;
}

bool Bank::removeClient(System::String^ name) {
    for (int i = 0; i < clients->Count; i++) {
        if (clients[i]->firstName->Equals(name)) {
            clients->RemoveAt(i);
            return true;
        }
    }
    return false;
}

bool Bank::removeDepositType(System::String^ name) {
    for each(Client ^ client in clients) {
        if (client->depositType != nullptr && client->depositType->name->Equals(name)) {
            return false;
        }
    }
    for (int i = 0; i < depositTypes->Count; i++) {
        if (depositTypes[i]->name->Equals(name)) {
            depositTypes->RemoveAt(i);
            return true;
        }
    }
    return false;
}

List<DepositType^>^ Bank::getDepositTypes() {
    return depositTypes;
}

List<Client^>^ Bank::getClients() {
    return clients;
}

// ---------- SQLite DB ----------
bool Bank::saveToDatabase() {
    return saveToDatabase("bank.db");
}

bool Bank::loadFromDatabase() {
    return loadFromDatabase("bank.db");
}

bool Bank::saveToDatabase(System::String^ filePath) {
    try {
        SQLiteConnection^ conn = gcnew SQLiteConnection();
        conn->ConnectionString = "Data Source=" + filePath + ";Version=3;";
        conn->Open();

        SQLiteCommand^ cmd = conn->CreateCommand();

        cmd->CommandText = "CREATE TABLE IF NOT EXISTS deposit_types (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL UNIQUE, interest_rate REAL NOT NULL, category INTEGER NOT NULL);";
        cmd->ExecuteNonQuery();

        cmd->CommandText = "CREATE TABLE IF NOT EXISTS clients (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, deposit_amount REAL NOT NULL, deposit_type_name TEXT);";
        cmd->ExecuteNonQuery();

        cmd->CommandText = "DELETE FROM clients;";
        cmd->ExecuteNonQuery();
        cmd->CommandText = "DELETE FROM deposit_types;";
        cmd->ExecuteNonQuery();

        for each(DepositType ^ type in depositTypes) {
            cmd->CommandText = String::Format("INSERT INTO deposit_types (name, interest_rate, category) VALUES ('{0}', {1}, {2});",
                type->name->Replace("'", "''"), type->interestRate.ToString(System::Globalization::CultureInfo::InvariantCulture), (int)type->category);
            cmd->ExecuteNonQuery();
        }

        for each(Client ^ client in clients) {
            String^ typeName = (client->depositType != nullptr) ? client->depositType->name->Replace("'", "''") : "";
            cmd->CommandText = String::Format("INSERT INTO clients (name, deposit_amount, deposit_type_name) VALUES ('{0}', {1}, '{2}');",
                client->firstName->Replace("'", "''"), client->depositAmount.ToString(System::Globalization::CultureInfo::InvariantCulture), typeName);
            cmd->ExecuteNonQuery();
        }

        conn->Close();
        delete (IDisposable^)conn;
        return true;
    }
    catch (Exception^) {
        return false;
    }
}

bool Bank::loadFromDatabase(System::String^ filePath) {
    try {
        if (!System::IO::File::Exists(filePath))
            return false;
        SQLiteConnection^ conn = gcnew SQLiteConnection();
        conn->ConnectionString = "Data Source=" + filePath + ";Version=3;";
        conn->Open();

        SQLiteCommand^ cmd = conn->CreateCommand();
        cmd->CommandText = "SELECT name FROM sqlite_master WHERE type='table' AND name='deposit_types';";
        Object^ o = cmd->ExecuteScalar();
        if (o == nullptr || o->ToString() != "deposit_types") {
            conn->Close();
            delete (IDisposable^)conn;
            return false;
        }

        depositTypes->Clear();
        clients->Clear();

        cmd->CommandText = "SELECT name, interest_rate, category FROM deposit_types;";
        SQLiteDataReader^ reader = (SQLiteDataReader^)cmd->ExecuteReader();
        while (reader->Read()) {
            String^ name = reader->GetString(0);
            double rate = reader->GetDouble(1);
            DepositCategory cat = (DepositCategory)reader->GetInt32(2);
            addDepositType(name, rate, cat);
        }
        reader->Close();

        cmd->CommandText = "SELECT name, deposit_amount, deposit_type_name FROM clients;";
        reader = (SQLiteDataReader^)cmd->ExecuteReader();
        while (reader->Read()) {
            String^ name = reader->GetString(0);
            double amount = reader->GetDouble(1);
            String^ typeName = reader->IsDBNull(2) ? "" : reader->GetString(2);
            addClient(name);
            if (!String::IsNullOrEmpty(typeName)) {
                makeDeposit(name, typeName, amount);
            }
        }
        reader->Close();

        conn->Close();
        delete (IDisposable^)conn;
        return true;
    }
    catch (Exception^) {
        return false;
    }
}

bool Bank::clearDatabase() {
    try {
        if (File::Exists("bank.db")) {
            File::Delete("bank.db");
        }
        return true;
    }
    catch (Exception^) {
        return false;
    }
}

// ---------- Ôàéëû ----------
bool Bank::saveToFile(System::String^ filePath) {
    try {
        StreamWriter^ writer = gcnew StreamWriter(filePath);
        writer->WriteLine("[DepositTypes]");
        for each(DepositType ^ type in depositTypes) {
            writer->WriteLine(type->name + "," +
                type->interestRate.ToString(System::Globalization::CultureInfo::InvariantCulture) + "," +
                ((int)type->category).ToString());
        }
        writer->WriteLine("[Clients]");
        for each(Client ^ client in clients) {
            String^ line = client->firstName + "," +
                client->depositAmount.ToString(System::Globalization::CultureInfo::InvariantCulture);
            if (client->depositType != nullptr) {
                line += "," + client->depositType->name;
            }
            writer->WriteLine(line);
        }
        writer->Close();
        return true;
    }
    catch (Exception^) {
        return false;
    }
}

bool Bank::loadFromFile(System::String^ filePath) {
    try {
        if (!File::Exists(filePath)) {
            return false;
        }
        StreamReader^ reader = gcnew StreamReader(filePath);
        depositTypes->Clear();
        clients->Clear();
        String^ line;
        String^ section = "";
        while ((line = reader->ReadLine()) != nullptr) {
            if (String::IsNullOrWhiteSpace(line)) continue;
            if (line == "[DepositTypes]") {
                section = "DepositTypes";
            }
            else if (line == "[Clients]") {
                section = "Clients";
            }
            else if (section == "DepositTypes") {
                array<String^>^ tokens = line->Split(',');
                if (tokens->Length >= 3) {
                    String^ name = tokens[0]->Trim();
                    double rate = Double::Parse(tokens[1]->Trim(), System::Globalization::CultureInfo::InvariantCulture);
                    int catNum = Int32::Parse(tokens[2]->Trim());
                    if (catNum >= 0 && catNum <= 3) {
                        addDepositType(name, rate, (DepositCategory)catNum);
                    }
                }
            }
            else if (section == "Clients") {
                array<String^>^ tokens = line->Split(',');
                if (tokens->Length >= 2) {
                    String^ name = tokens[0]->Trim();
                    double amount = Double::Parse(tokens[1]->Trim(), System::Globalization::CultureInfo::InvariantCulture);
                    addClient(name);
                    if (tokens->Length >= 3 && !String::IsNullOrEmpty(tokens[2])) {
                        makeDeposit(name, tokens[2]->Trim(), amount);
                    }
                }
            }
        }
        reader->Close();
        return true;
    }
    catch (Exception^) {
        return false;
    }
}
