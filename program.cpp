#include <iostream>
#include <string>
using namespace std;

class Account {
private:
    int accountNumber;
    string holderName;
    double balance;
    int pin;

public:
    Account(int accNo, string name, double bal, int pinCode)
        : accountNumber(accNo), holderName(name), balance(bal), pin(pinCode) {}

    int getAccountNumber() { return accountNumber; }
    string getHolderName() { return holderName; }

    bool validatePIN(int enteredPIN) { return pin == enteredPIN; }

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

class Bank {
private:
    vector<Account> accounts;

public:
    void addAccount(Account acc) { accounts.push_back(acc); }

    Account* getAccount(int accNo) {
        for (auto &acc : accounts) {
            if (acc.getAccountNumber() == accNo)
                return &acc;
        }
        return nullptr;
    }
};

class ATM {
private:
    Bank &bank;
    Account* currentAccount = nullptr;

public:
    ATM(Bank &b) : bank(b) {}

    void login() {
        int accNo, pin;
        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cout << "Enter PIN: ";
        cin >> pin;

        Account* acc = bank.getAccount(accNo);
        if (acc && acc->validatePIN(pin)) {
            currentAccount = acc;
            cout << "Welcome " << acc->getHolderName() << "!" << endl;
            showMenu();
        } else {
            cout << "Invalid account number or PIN.\n";
        }
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n===== ATM MENU =====\n";
            cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. Exit\n";
            cout << "Choose: ";
            cin >> choice;

            switch (choice) {
                case 1: currentAccount->checkBalance(); break;
                case 2: {
                    double amt;
                    cout << "Enter amount to deposit: ";
                    cin >> amt;
                    currentAccount->deposit(amt);
                    break;
                }
                case 3: {
                    double amt;
                    cout << "Enter amount to withdraw: ";
                    cin >> amt;
                    currentAccount->withdraw(amt);
                    break;
                }
                case 4: cout << "Thank you for using ATM!\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } while (choice != 4);
    }
};

int main() {
    Bank bank;
    bank.addAccount(Account(1001, "Alice", 5000, 1234));
    bank.addAccount(Account(1002, "Bob", 3000, 4321));

    ATM atm(bank);

    int option;
    do {
        cout << "\n==== WELCOME TO ATM ====\n";
        cout << "1. Login\n2. Exit\nChoose: ";
        cin >> option;
        if (option == 1) atm.login();
    } while (option != 2);

    return 0;
}
