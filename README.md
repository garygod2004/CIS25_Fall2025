# Midterm

## Bank Account Simulation – Module 8

### 🧠 Overview
This program simulates a simple **Bank Account system** using C++.  
It demonstrates class design, file handling, and formatted output.

The program allows a user to:
- **Deposit funds** into an account  
- **Make purchases** that deduct from the balance  
- **Check their balance** at any time  
- **Store every transaction** (deposits and purchases) in a text file (`transactions.txt`) for permanent record keeping  

---

### ⚙️ How It Works
1. The `BankAccount` class manages a private balance variable.  
2. The class includes methods for:
   - `deposit(double amount)` → adds money to the balance  
   - `makePurchase(string item, double cost)` → deducts money if balance is sufficient  
   - `displayBalance()` → prints the current balance to the console  
   - `saveTransaction()` → logs all transactions in `transactions.txt`  
3. The `main()` function:
   - Creates a new `Ba
