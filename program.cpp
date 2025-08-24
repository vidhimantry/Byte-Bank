#include <iostream>
#include <string>
using namespace std;

class Account {
private:
    int accountNumber;
    double balance;
    string type;

public:
    Account(int accNo, double bal, string t) 
        : accountNumber(accNo), balance(bal), type(t) {}

    int getAccountNumber() { return accountNumber; }
    double getBalance() { return balance; }
    string getType() { return type; }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << " | New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn: " << amount << " | New Balance: " << balance << endl;
        }
    }

    void checkBalance() { cout << "Current Balance: " << balance << endl; }
};

class User {
private:
    string name;
    int userID;
    int pin;
    vector<Account> accounts;

public:
    User(int id, string uname, int p) : userID(id), name(uname), pin(p) {}

    string getName() { return name; }
    int getID() { return userID; }
    bool validatePIN(int entered) { return entered == pin; }

    void addAccount(Account acc) { accounts.push_back(acc); }
    vector<Account>& getAccounts() { return accounts; }
};

class Bank {
private:
    vector<User> users;

public:
    void addUser(User u) { users.push_back(u); }

    User* authenticate(int id, int pin) {
        for (auto &u : users) {
            if (u.getID() == id && u.validatePIN(pin))
                return &u;
        }
        return nullptr;
    }
};

class ATM {
private:
    Bank &bank;
    User* currentUser = nullptr;

public:
    ATM(Bank &b) : bank(b) {}

    void login() {
        int id, pin;
        cout << "Enter User ID: ";
        cin >> id;
        cout << "Enter PIN: ";
        cin >> pin;

        currentUser = bank.authenticate(id, pin);
        if (currentUser) {
            cout << "Welcome " << currentUser->getName() << "!\n";
            showMenu();
        } else {
            cout << "Invalid credentials.\n";
        }
    }

    void showMenu() {
        int choice;
        do {
            cout << "ATM OPTIONS: \n";
            cout << "1. View Accounts\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Logout\n";
            cout << "Choose: ";
            cin >> choice;

        switch (choice) {
                case 1: viewAccounts(); break;
                case 2: deposit(); break;
                case 3: withdraw(); break;
                case 4: transfer(); break;
                case 5: cout << "Logging out...\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    Bank bank;
    bank.addAccount(Account(1001, "Alice", 5000, 1234));
    bank.addAccount(Account(1002, "Bob", 3000, 4321));

    ATM atm(bank);

    int option;
    do {
        cout << "WELCOME TO ATM! ";
        cout << "1. Login\n2. Exit\nChoose: ";
        cin >> option;
        if (option == 1) atm.login();
    } while (option != 2);

    return 0;
}
