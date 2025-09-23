#include <iostream>
#include <vector>
using namespace std;


void showMenu();
void addNumber(vector<int>& numbers);
void viewNumbers(const vector<int>& numbers);


void showMenu() {
    cout << "\n=== MENU ===\n";
    cout << "1. Add Number\n";
    cout << "2. View Numbers\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void addNumber(vector<int>& numbers) {
    int num;
    cout << "Enter a number to add: ";
    cin >> num;
    numbers.push_back(num);
    cout << num << " added!\n";
}


void viewNumbers(const vector<int>& numbers) {
    cout << "Numbers stored: ";
    if (numbers.empty()) {
        cout << "(none)\n";
    } else {
        for (int n : numbers) {
            cout << n << " ";
        }
        cout << "\n";
    }
}

int main() {
    vector<int> numbers; 
    int option;

    do {
        showMenu();
        cin >> option;

        switch(option) {
            case 1:
                addNumber(numbers);
                break;
            case 2:
                viewNumbers(numbers);
                break;
            case 3:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (option != 3);

    return 0;
}
