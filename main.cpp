#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
double balance = 0;
vector<string> transactions;
int loadedTransactionCount = 0;
string accountName;
int accountNumber = 0;
void saveAccountDetails(string name, int accountNumber, double balance);

void createAccount() {

    cout << "\n===== CREATE ACCOUNT =====\n";

    cout << "Enter account holder name: ";
    cin >> ws;
    getline(cin, accountName);

    cout << "Enter account number: ";
    cin >> accountNumber;

    cout << "Enter opening balance: ";
    cin >> balance;

    if (accountNumber <= 0 || balance < 0) {
        cout << "\nInvalid account details!\n";
        return;
    }
    
    saveAccountDetails(accountName, accountNumber, balance);
    cout << "\nAccount created successfully!\n";
    cout << "Account Holder: " << accountName << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Opening Balance: " << balance << endl;
}
void depositMoney(double &balance) {

    double amount;

    cout << "\n===== DEPOSIT MONEY =====\n";
    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid deposit amount!\n";
    }
    else {
        balance += amount;
        saveAccountDetails(accountName, accountNumber, balance);
        transactions.push_back("Deposited: Rs. " + to_string(amount));

        cout << "\nDeposit successful!\n";
        cout << "Updated Balance: " << balance << endl;
    }
}
void withdrawMoney(double &balance) {

    double amount;

    cout << "\n===== WITHDRAW MONEY =====\n";
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid withdrawal amount!\n";
    }
    else if (amount > balance) {
        cout << "Insufficient balance!\n";
    }
    else {
        balance -= amount;
        saveAccountDetails(accountName, accountNumber, balance);
        transactions.push_back("Withdrawn: Rs. " + to_string(amount));

        cout << "\nWithdrawal successful!\n";
        cout << "Remaining Balance: " << balance << endl;
    }
}
void checkBalance(double balance) {

    cout << "\n===== ACCOUNT BALANCE =====\n";
    cout << "Your Current Balance: " << balance << endl;

}
void showTransactionHistory() {

    cout << "\n===== TRANSACTION HISTORY =====\n";

    if (transactions.empty()) {
        cout << "No transactions found.\n";
    }
    else {
        for (string transaction : transactions) {
            cout << transaction << endl;
        }
    }
}
void saveTransactions() {

    ofstream file("transactions.txt", ios::app);

    if (file.is_open()) {

        for (int i = loadedTransactionCount; i < transactions.size(); i++) {
    file << transactions[i] << endl;
}

loadedTransactionCount = transactions.size();
        file.close();

        cout << "\nTransactions saved successfully!\n";
    }
    else {
        cout << "\nUnable to save transactions!\n";
    }
}
void saveAccountDetails(string name, int accountNumber, double balance) {

    ofstream file("account.txt");

    if (file.is_open()) {
        file << name << endl;
        file << accountNumber << endl;
        file << balance << endl;

        file.close();

        cout << "Account details saved successfully!\n";
    }
}
void loadAccountDetails() {

    cout << "\nLoading account details...\n";

    ifstream file("account.txt");

    if (file.is_open()) {
        getline(file, accountName);
        file >> accountNumber;
        file >> balance;

        file.close();

        cout << "\nAccount details loaded successfully!\n";
    }
    else {
    cout << "Account file not found!\n";
}
}
void loadTransactions() {

    ifstream file("transactions.txt");
    string transaction;

    while (getline(file, transaction)) {
        transactions.push_back(transaction);
    }
    loadedTransactionCount = transactions.size();

    file.close();
}
int main() {
    loadAccountDetails();
    loadTransactions();

    int choice;

    do {
        cout << "\n===== BANKING SYSTEM =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Transaction History\n";
        cout << "6. Exit\n";

        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) { 
              cin.clear();
              cin.ignore(1000, '\n');

              cout << "Invalid input! Please enter a number.\n";
              continue;
}
        switch (choice) {

    case 1:
        createAccount();
        break;

    case 2:
        depositMoney(balance);
        break;

    case 3:
        withdrawMoney(balance);
        break;

    case 4:
        checkBalance(balance);
        break;

    case 5:
        showTransactionHistory();
        break;

    case 6:
        saveTransactions();
        cout << "Exiting Banking System...\n";
        break;

    default:
        cout << "Invalid choice! Please try again.\n";
}

    } while (choice != 6);

    cout << "\nThank you for using our Banking System!\n";

    return 0;
}