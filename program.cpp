#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Account Class
class Account {
private:
    int accountNumber;
    double balance;
    string type;

public:
    Account(int accNo, double bal, string accType)
        : accountNumber(accNo), balance(bal), type(accType) {}

    int getAccountNumber() { return accountNumber; }
    double getBalance() { return balance; }
    string getType() { return type; }

    void deposit(double amount) { balance += amount; }
    bool withdraw(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }
};

// User Class
class User {
private:
    int id;
    string name;
    int pin;
    vector<Account> accounts;

public:
    User(int uid, string uname, int upin)
        : id(uid), name(uname), pin(upin) {}

    int getId() { return id; }
    string getName() { return name; }
    int getPin() { return pin; }
    vector<Account>& getAccounts() { return accounts; }

    void addAccount(Account acc) { accounts.push_back(acc); }
    bool validatePin(int entered) { return entered == pin; }
};

// Bank Class
class Bank {
private:
    vector<User> users;
    int nextUserId = 1;

public:
    Bank() {
        loadFromFile();
    }

    void signUp(string name, int pin) {
        cout << "Choose account type - 1 for Savings, 2 for Current: ";
        int choice; cin >> choice;
        string type = (choice == 2) ? "Current" : "Savings";
        User newUser(nextUserId++, name, pin);
        newUser.addAccount(Account(1000 + newUser.getId(), 0, type));
        users.push_back(newUser);
        saveToFile();
        cout << "Sign up successful! Your User ID is: " << newUser.getId() << endl;
    }

    User* authenticate(int id, int pin) {
        for (auto &u : users) {
            if (u.getId() == id && u.validatePin(pin)) return &u;
        }
        return nullptr;
    }

    void saveToFile() {
        ofstream file("users.txt");
        for (auto &u : users) {
            Account acc = u.getAccounts()[0];
            file << u.getId() << "|"
                 << u.getName() << "|"
                 << u.getPin() << "|"
                 << acc.getAccountNumber() << "|"
                 << acc.getBalance() << "|"
                 << acc.getType() << "\n";
        }
    }

    void loadFromFile() {
        ifstream file("users.txt");
        if (!file) return;

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string userIdStr, name, pinStr, accNoStr, balStr, typeStr;
            getline(ss, userIdStr, '|');
            getline(ss, name, '|');
            getline(ss, pinStr, '|');
            getline(ss, accNoStr, '|');
            getline(ss, balStr, '|');
            getline(ss, typeStr);

            int id = stoi(userIdStr);
            int pin = stoi(pinStr);
            int accNo = stoi(accNoStr);
            double balance = stod(balStr);
            string type = typeStr;

            User newUser(id, name, pin);
            newUser.addAccount(Account(accNo, balance, type));
            users.push_back(newUser);
            nextUserId = max(nextUserId, id + 1);
        }
        file.close();
    }

    vector<User>& getUsers() { return users; }
};

// ATM Class
class ATM {
private:
    Bank &bank;

public:
    ATM(Bank &b) : bank(b) {}

    void login() {
        int id, pin;
        cout << "Enter User ID: ";
        cin >> id;
        cout << "Enter PIN: ";
        cin >> pin;

        User* user = bank.authenticate(id, pin);
        if (!user) {
            cout << "Invalid login.\n";
            return;
        }

        cout << "Welcome, " << user->getName() << "!\n";
        int choice;
        do {
            cout << "ATM Options:\n1. View Balance\n2. Deposit\n3. Withdraw\n4. Logout\nChoose: ";
            cin >> choice;
            if (choice == 1) {
                for (auto &acc : user->getAccounts()) {
                    cout << acc.getType() << " Account " << acc.getAccountNumber()
                         << " Balance: " << acc.getBalance() << endl;
                }
            } else if (choice == 2) {
                double amt;
                cout << "Enter amount: ";
                cin >> amt;
                user->getAccounts()[0].deposit(amt);
                bank.saveToFile();
                cout << "Deposited " << amt << " to your account!\n";
            } else if (choice == 3) {
                double amt;
                cout << "Enter amount: ";
                cin >> amt;
                if (user->getAccounts()[0].withdraw(amt)) {
                    bank.saveToFile();
                    cout << "Withdrawn " << amt << " from your account!\n";
                } else {
                    cout << "Insufficient funds.\n";
                }
            }
        } while (choice != 4);
    }
};

//  Main
int main() {
    Bank bank;
    ATM atm(bank);

    int choice;
    do {
        cout << "Welcome to ByteBank!\n";
        cout << "1. Sign Up\n2. Login\n3. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            string name; 
            int pin;
            cout << "Enter your name: ";
            cin.ignore();              
            getline(cin, name);      
            cout << "Choose a 4-digit PIN: ";
            cin >> pin;
            bank.signUp(name, pin);
        }
        else if (choice == 2) {
                    atm.login();
            }
    } while (choice != 3);
    return 0;
}
