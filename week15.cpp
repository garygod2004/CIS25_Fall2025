#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;

public:
    Product(int productId, const string& productName, double productPrice)
        : id(productId), name(productName), price(productPrice)
    {
        cout << "Product constructor called!" << endl;
    }

    ~Product() {
        cout << "Product destructor called!" << endl;
    }

    void printDetails() const {
        cout << "ID: " << id
             << ", Name: " << name
             << ", Price: $" << price << endl;
    }
};

int main() {
    Product p(101, "Notebook", 4.99);
    p.printDetails();
    return 0;
}
