# 🏦 ATM & Bank Account Simulator  

A simple **C++ console application** demonstrating **basic OOP principles** such as classes, objects, encapsulation, and file persistence.  
The project simulates a small ATM & Banking system with **signup, login, deposit, withdrawal, and balance inquiry** features.  

---

## ✨ Features  
- 👤 **User Management**  
  - Sign up with name & PIN (unique User ID auto-assigned).  
  - Login with User ID and PIN.  
  - Data stored persistently in `users.txt`.  

- 💳 **Bank Accounts**  
  - Create account at signup (Savings by default).  
  - Each account has account number, type, and balance.  
  - (Optional future upgrade: multiple accounts per user).  

- 🏧 **ATM Operations**  
  - Deposit money.  
  - Withdraw money.  
  - Check balance.  
  - Logout when done.  

- 💾 **Persistence**  
  - All user data is stored in `users.txt` (simple text-based database).  
  - Sample accounts available in `users-sample.txt` for quick testing.  

---

## ⚙️ How to Run 

1. **Clone the repo**  
   ```bash
   git clone https://github.com/vidhimantry/ATM-Bank-Simulator.git
   cd ATM-Bank-Simulator
   ```

2. **Compile and Run**  
   ```bash
   g++ program.cpp -o program
   ./program
   ```
   ---

## 🖥️ Sample Run
```
Welcome to the Banking ATM Simulator!
1. Sign Up
2. Login
3. Exit
Choose: 1
Enter your name: Kriti Gupta
Choose a 4-digit PIN: 4321
Choose account type - 1 for Savings, 2 for Current: 2
Sign up successful! Your User ID is: 1
```
```
Welcome to the Banking ATM Simulator!
1. Sign Up
2. Login
3. Exit
Choose: 2
Enter User ID: 1
Enter PIN: 4321
Welcome, Kriti Gupta!
ATM Options:
1. View Balance
2. Deposit
3. Withdraw
4. Logout
Choose: 1
Current Acc 1001 Balance: 0

ATM Options:
1. View Balance
2. Deposit
3. Withdraw
4. Logout
Choose: 2
Enter amount: 5000
Deposited.
```

## 📖 Concepts Demonstrated
- **Classes & Objects** → `User`, `Account`, `BankSystem`.  
- **Encapsulation** → data + methods bound inside objects.  
- **File Handling** → Persistent storage with text file.  
- **Polymorphism/Extensibility** → Easy to extend with new account types or features.  

---

## 🚀 Future Improvements
- Support for multiple accounts per user (Savings, Current, FD).  
- Transfer money between users.  
- PIN change & account deletion.  
- Admin panel for managing users.  

---

## 📜 License
This project is open-source under the **MIT License**.  




