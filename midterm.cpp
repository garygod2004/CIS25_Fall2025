#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class BankAccount {
private:
    double balance;

    
    void saveTransaction(const string& type, const string& item, double amount) {
        ofstream file("transactions.txt", ios::app);
        if (!file) {
            cerr << "[ERROR] Could not open transactions.txt\n";
            return;
        }
        file << fixed << setprecision(2);
        file << type;
        if (!item.empty()) file << " - " << item;
        file << ": $" << amount << " | Balance: $" << balance << '\n';
        file.close();
    }

public:
    
    BankAccount() : balance(0.0) {}
    explicit BankAccount(double starting) : balance(starting) {
        
        saveTransaction("Start", "", balance);
    }

    
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit must be positive.\n";
            return;
        }
        balance += amount;
        cout << "Deposited $" << fixed << setprecision(2) << amount
             << ". New balance: $" << balance << '\n';
        saveTransaction("Deposit", "", amount);
    }

    
    void makePurchase(const string& item, double cost) {
        if (cost <= 0) {
            cout << "Purchase amount must be positive.\n";
            return;
        }
        if (cost > balance) {
            cout << "Insufficient funds for \"" << item << "\" (cost $"
                 << fixed << setprecision(2) << cost << ").\n";
            return;
        }
        balance -= cost;
        cout << "Purchased \"" << item << "\" for $" << fixed << setprecision(2)
             << cost << ". New balance: $" << balance << '\n';
        saveTransaction("Purchase", item, cost);
    }

   
    void displayBalance() const {
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << '\n';
    }
};

int main() {
    ofstream reset("transactions.txt");
    reset << "=== Transaction Log ===\n";
    reset.close();

    BankAccount myAccount;           
    myAccount.deposit(100.00);      
    myAccount.makePurchase("Coffee", 4.50);
    myAccount.makePurchase("Book", 25.00);
    myAccount.displayBalance();

    myAccount.makePurchase("Laptop", 2000.00);

    return 0;
}
