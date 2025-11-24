# Week 13 – Inheritance & Method Overriding (C++)

## 📌 Overview
This week’s assignment demonstrates how **inheritance** and **method overriding** work in C++ by building a small role–based access control system. The program creates a class hierarchy where each class represents a different user type in an inventory system.

## 🧱 Class Structure
The project contains the following classes:

### **1. User (Base Class)**
- Contains a `virtual` method named `accessLevel()`.
- Prints **"General Access"**.
- Acts as the foundation for all other user types.

### **2. Employee (Derived From User)**
- Inherits from `User`.
- Overrides `accessLevel()`.
- Prints **"Employee Access"**.

### **3. InventoryManager (Derived From Employee)**
- Inherits from `Employee`.
- Overrides `accessLevel()`.
- Prints **"Full Inventory Management Access"**.
- Represents the highest access level in this simple hierarchy.

## ▶️ Program Behavior
When the program runs:

1. An `InventoryManager` object is created in `main.cpp`.
2. Calling `accessLevel()` runs the **InventoryManager version** of the method.
3. This demonstrates how C++ chooses the correct method using **polymorphism** and **overriding**.

