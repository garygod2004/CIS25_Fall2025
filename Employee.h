#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"

class Employee : public User {
public:
    // Override User::accessLevel
    void accessLevel() const override {
        std::cout << "Employee Access\n";
    }
};

#endif // EMPLOYEE_H