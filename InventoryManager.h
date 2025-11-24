#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "Employee.h"

class InventoryManager : public Employee {
public:
    // Override Employee::accessLevel
    void accessLevel() const override {
        std::cout << "Full Inventory Management Access\n";
    }
};

#endif // INVENTORY_MANAGER_H