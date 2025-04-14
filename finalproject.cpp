#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
class ATMSystem {
public:
    string accountNumber;
    string accountHolderName;
    float balance;
    ATMSystem* prev;
    ATMSystem* next;

    ATMSystem(string accNum, string holder, float bal) {
        accountNumber = accNum;
        accountHolderName = holder;
        balance = bal;
        prev = NULL;
        next = NULL;
    }
};

ATMSystem* head = NULL;
bool login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    const string storedUser = "admin";
    const string storedPass = "1234";
    if (username == storedUser && password == storedPass) {
        cout << "Login successful.\n";
        return true;
    }
    cout << "Login failed. Invalid credentials.\n";
    return false;
}

void registerUser() {
    cout << "User registration disabled (file handling removed).\n";
}

ATMSystem* searchAccount(const string& accNum) {
    ATMSystem* temp = head;
    while (temp) {
        if (temp->accountNumber == accNum) return temp;
        temp = temp->next;
    }
    return NULL;
}

void createAccount() {
    string accNum, name;
    float bal;
    cout << "Enter Account Number: "; cin >> accNum;
    if (searchAccount(accNum)) {
        cout << "Account already exists!\n";
        return;
    }
    cout << "Enter Account Holder Name: "; cin.ignore(); getline(cin, name);
    cout << "Enter Initial Balance: "; cin >> bal;
    ATMSystem* newNode = new ATMSystem(accNum, name, bal);
    if (!head) head = newNode;
    else {
        ATMSystem* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
    cout << "Account created successfully!\n";
}

void displayAccounts() {
    ATMSystem* temp = head;
    if (!temp) {
        cout << "No accounts found.\n";
        return;
    }
    while (temp) {
        cout << "\nAccount No: " << temp->accountNumber
             << "\nHolder: " << temp->accountHolderName
             << "\nBalance: $" << temp->balance << "\n";
        temp = temp->next;
    }
}

void deleteAccount(const string& accNum) {
    ATMSystem* temp = searchAccount(accNum);
    if (!temp) {
        cout << "Account not found.\n";
        return;
    }
    if (temp->prev) temp->prev->next = temp->next;
    else head = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    delete temp;
    cout << "Account deleted.\n";
}

void updateAccount(const string& accNum) {
    ATMSystem* acc = searchAccount(accNum);
    if (!acc) {
        cout << "Account not found.\n";
        return;
    }
    cout << "Enter new holder name: "; cin.ignore(); getline(cin, acc->accountHolderName);
    cout << "Updated successfully.\n";
}

void deposit(const string& accNum, float amount) {
    ATMSystem* acc = searchAccount(accNum);
    if (!acc) {
        cout << "Account not found.\n";
        return;
    }
    acc->balance += amount;
    cout << "Amount deposited.\n";
}

void withdraw(const string& accNum, float amount) {
    ATMSystem* acc = searchAccount(accNum);
    if (!acc || acc->balance < amount) {
        cout << "Insufficient funds or account not found.\n";
        return;
    }
    acc->balance -= amount;
    cout << "Amount withdrawn.\n";
}

void printReceipt(const string& accNum) {
    ATMSystem* acc = searchAccount(accNum);
    if (!acc) cout << "Account not found.\n";
    else cout << "\n--- Receipt ---\nAccount: " << acc->accountNumber << "\nHolder: " << acc->accountHolderName << "\nBalance: $" << acc->balance << "\n";
}

void transferMoney(const string& fromAcc, const string& toAcc, float amount) {
    ATMSystem* from = searchAccount(fromAcc);
    ATMSystem* to = searchAccount(toAcc);
    if (!from || !to || from->balance < amount) {
        cout << "Transfer failed.\n";
        return;
    }
    from->balance -= amount;
    to->balance += amount;
    cout << "Transfer successful.\n";
}

void checkBalance(const string& accNum) {
    ATMSystem* acc = searchAccount(accNum);
    if (!acc) cout << "Account not found.\n";
    else cout << "Balance: $" << acc->balance << "\n";
}

void billPayment(const string& accNum, float amount, string ref, string type) {
    ATMSystem* acc = searchAccount(accNum);
    if (!acc || acc->balance < amount) {
        cout << "Payment failed.\n";
        return;
    }
    acc->balance -= amount;
    cout << "Paid $" << amount << " for " << type << " (Ref: " << ref << ").\n";
}

void applyForCard(const string& accNum, string cardType) {
    ATMSystem* acc = searchAccount(accNum);
    if (!acc) cout << "Account not found.\n";
    else cout << "Card application submitted for " << cardType << ".\n";
}

void saveAccountsToFile(ATMSystem* head, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "File write error.\n";
        return;
    }
    ATMSystem* temp = head;
    while (temp) {
        outFile << temp->accountNumber << "," << temp->accountHolderName << "," << temp->balance << "\n";
        temp = temp->next;
    }
    outFile.close();
    cout << "Accounts saved.\n";
}

void loadAccountsFromFile(ATMSystem*& head, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
    	string filepath= "C:\\Users\\SESCO TECH\\Desktop\\finalproject.tx";
        cout << "File read error.\n";
        return;
    }
    head = nullptr;
    string accNum, name, line;
    float bal;
    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');
        if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) continue;
        accNum = line.substr(0, pos1);
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        bal = stof(line.substr(pos2 + 1));
        ATMSystem* newNode = new ATMSystem(accNum, name, bal);
        if (!head) head = newNode;
        else {
            ATMSystem* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
            newNode->prev = temp;
        }
    }
    inFile.close();
    cout << "Accounts loaded.\n";
}
int main() {
  
    int choice;
    string accNum, toAcc, ref, type;
    float amount;
    string filePath ="C:\\Users\\SESCO TECH\\Desktop\\finalproject.txt"; // <-- file path added here

    cout << "---- Welcome to ATM System ----\n";
    cout << "1. Login\n2. Register\nChoice: ";
    cin >> choice;

    if (choice == 2) {
        registerUser();
        return 0;
    }

    if (!login()) return 0;

    loadAccountsFromFile(head, filePath); // <-- updated

    do {
        cout << "\n------ ATM Menu ------\n";
        cout << "1. Create Account\n2. Display All\n3. Delete Account\n4. Update Account\n5. Deposit\n6. Withdraw\n7. Print Receipt\n8. Transfer\n9. Check Balance\n10. Pay Bill\n11. Apply Card\n12. Save to File\n13. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: createAccount(); break;
            case 2: displayAccounts(); break;
            case 3: cout << "Account to delete: "; cin >> accNum; deleteAccount(accNum); break;
            case 4: cout << "Account to update: "; cin >> accNum; updateAccount(accNum); break;
            case 5: cout << "Account to deposit: "; cin >> accNum; cout << "Amount: "; cin >> amount; deposit(accNum, amount); break;
            case 6: cout << "Account to withdraw: "; cin >> accNum; cout << "Amount: "; cin >> amount; withdraw(accNum, amount); break;
            case 7: cout << "Account for receipt: "; cin >> accNum; printReceipt(accNum); break;
            case 8: cout << "From account: "; cin >> accNum; cout << "To account: "; cin >> toAcc; cout << "Amount: "; cin >> amount; transferMoney(accNum, toAcc, amount); break;
            case 9: cout << "Account to check: "; cin >> accNum; checkBalance(accNum); break;
            case 10: cout << "Account: "; cin >> accNum; cout << "Amount: "; cin >> amount; cout << "Ref: "; cin >> ref; cout << "Type: "; cin >> type; billPayment(accNum, amount, ref, type); break;
            case 11: cout << "Account: "; cin >> accNum; cout << "Card Type: "; cin >> type; applyForCard(accNum, type); break;
            case 12: saveAccountsToFile(head, filePath); break; // <-- updated
            case 13: saveAccountsToFile(head, filePath); cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 13);

    return 0;
	}
