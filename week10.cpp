#include <iostream>
#include <string>
#include <limits>

class Item {
public:
    std::string name;
    int quantity;

    Item() : name(""), quantity(0) {}
    Item(const std::string& n, int q) : name(n), quantity(q) {}
};

int main() {
    const std::size_t INVENTORY_SIZE = 5;
    Item inventory[INVENTORY_SIZE];

    std::cout << "=== Inventory Management (Arrays) ===\n";
    std::cout << "Please enter " << INVENTORY_SIZE << " items (name and quantity).\n\n";

    for (std::size_t i = 0; i < INVENTORY_SIZE; ++i) {
        std::string name;
        int qty = 0;

        std::cout << "Item " << (i + 1) << " name: ";
        std::getline(std::cin, name);
        while (name.empty()) {
            std::cout << "Name cannot be empty. Try again: ";
            std::getline(std::cin, name);
        }

        std::cout << "Item " << (i + 1) << " quantity (integer): ";
        while (true) {
            if (std::cin >> qty && qty >= 0) {
                break;
            } else {
                std::cout << "Please enter a valid *non-negative* integer: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        inventory[i] = Item(name, qty);
        std::cout << "\n";
    }

    std::cout << "\n--- Current Inventory ---\n";
    int total = 0;
    for (std::size_t i = 0; i < INVENTORY_SIZE; ++i) {
        std::cout << (i + 1) << ". " << inventory[i].name
                  << " - qty: " << inventory[i].quantity << "\n";
        total += inventory[i].quantity;
    }

    std::cout << "\nTotal quantity across all items: " << total << "\n";
    std::cout << "\nSearch for an item by name: ";
    std::string target;
    std::getline(std::cin, target);

    bool found = false;
    for (std::size_t i = 0; i < INVENTORY_SIZE; ++i) {
        if (inventory[i].name == target) {
            std::cout << "Found \"" << inventory[i].name
                      << "\" with quantity: " << inventory[i].quantity << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Item \"" << target << "\" not found in inventory.\n";
    }

    std::cout << "\nGoodbye!\n";
    return 0;
}
