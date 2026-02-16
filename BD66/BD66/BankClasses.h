#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;

// ????????? ???????
enum class DepositCategory {
    SHORT_TERM,
    LONG_TERM,
    SPECIAL,
    SAVINGS
};

ref class DepositType {
public:
    System::String^ name;
    double interestRate;
    DepositCategory category;

    DepositType(System::String^ n, double rate, DepositCategory cat);
    System::String^ getCategoryString();
};

ref class Client {
public:
    System::String^ firstName;
    double depositAmount;
    DepositType^ depositType;

    Client(System::String^ first);
};

ref class Bank {
private:
    static Bank^ instance = nullptr;
    List<DepositType^>^ depositTypes;
    List<Client^>^ clients;

    Bank();

public:
    static Bank^ getInstance();

    bool saveToDatabase();
    bool loadFromDatabase();
    bool saveToDatabase(System::String^ filePath);
    bool loadFromDatabase(System::String^ filePath);
    bool clearDatabase();

    void addDepositType(System::String^ name, double rate, DepositCategory category);
    void addClient(System::String^ firstName);
    bool editClient(System::String^ oldName, System::String^ newName);
    bool editDepositType(System::String^ oldName, System::String^ newName, double newRate);
    bool makeDeposit(System::String^ clientName, System::String^ depositName, double amount);

    double calculateClientInterest(System::String^ clientName);
    double calculateTotalInterest();
    Client^ findTopPayer();
    void sortClientsByName();
    double getTotalDeposits();

    Client^ findClient(System::String^ name);
    DepositType^ findDepositType(System::String^ name);
    bool removeClient(System::String^ name);
    bool removeDepositType(System::String^ name);

    List<DepositType^>^ getDepositTypes();
    List<Client^>^ getClients();

    bool saveToFile(System::String^ filePath);
    bool loadFromFile(System::String^ filePath);
};
