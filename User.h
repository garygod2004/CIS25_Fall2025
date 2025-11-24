#ifndef USER_H
#define USER_H

#include <iostream>

class User {
public:
    // Virtual so child classes can override
    virtual void accessLevel() const {
        std::cout << "General Access\n";
    }

    // Always good practice to have a virtual destructor
    virtual ~User() = default;
};

#endif // USER_H