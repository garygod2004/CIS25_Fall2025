#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Item {
public:
    string name;
    int quantity;

    void saveToFile() {
        ofstream out("items.txt", ios::app); 
        if (out.is_open()) {
            out << name << "," << quantity << endl;
            out.close();
            cout << "Item saved: " << name << ", " << quantity << endl;
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }


    static void loadFromFile() {
        ifstream in("items.txt");
        if (in.is_open()) {
            string line;
            cout << "\nItems in file:" << endl;
            while (getline(in, line)) {
                cout << " - " << line << endl;
            }
            in.close();
        } else {
            cout << "Unable to open file for reading." << endl;
        }
    }
};

int main() {
  
    vector<Item> inventory;

    Item screwdriver;
    screwdriver.name = "Screwdriver";
    screwdriver.quantity = 10;

    Item hammer;
    hammer.name = "Hammer";
    hammer.quantity = 5;

    Item wrench;
    wrench.name = "Wrench";
    wrench.quantity = 7;


    inventory.push_back(screwdriver);
    inventory.push_back(hammer);
    inventory.push_back(wrench);

  
    for (auto &tool : inventory) {
        tool.saveToFile();
    }


    Item::loadFromFile();

    return 0;
}
