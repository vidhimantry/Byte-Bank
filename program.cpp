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

int main() {
    cout << "Account class created successfully." << endl;
    return 0;
}
