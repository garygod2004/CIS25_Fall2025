# Week 15 – Constructors & Destructors in C++

## Overview
This week’s assignment focuses on understanding how constructors and destructors work within a C++ class.  
The code for this assignment defines a class named **Product**, which contains private attributes and demonstrates how object lifecycle methods behave.

---

## What This Code Does

### 1. Defines a `Product` Class
The class includes the following **private attributes**:

- **id** – an integer representing the product ID  
- **name** – a string representing the product's name  
- **price** – a double storing the product’s price  

These attributes are private to follow proper object-oriented design.

---

### 2. Implements a Constructor
When a `Product` object is created, the constructor:

- Initializes the `id`, `name`, and `price` attributes  
- Prints a message so you can see when object construction occurs  

---

### 3. Implements a Destructor
When the object goes out of scope, the destructor:

- Automatically runs  
- Prints a message indicating cleanup is happening  

This shows the full lifecycle of the object.

---

### 4. Includes a `printDetails()` Method
This method prints the product’s:

- ID  
- Name  
- Price  

It verifies that the constructor has properly initialized the object.

---

## Program Flow in `main()`
1. A `Product` object is created with example values  
2. `printDetails()` is called  
3. When `main()` ends, the destructor runs automatically  
