#include <iostream>

int main() {
    // a) Greeting
    std::cout << "Hello Inventory System!\n";

    // Demonstrate escape characters
    std::cout << "Escape demo:\n";
    std::cout << "\t- New line -> \\n\n";
    std::cout << "\t- Tab -> \\t\n";
    std::cout << "\t- Quote -> \\\" (example: \"SKU\")\n\n";

    // Output sizes of basic types (bytes)
    std::cout << "Type sizes (bytes):\n";
    std::cout << "\tint:   "  << sizeof(int)   << '\n';
    std::cout << "\tfloat: "  << sizeof(float) << '\n';
    std::cout << "\tchar:  "  << sizeof(char)  << '\n';

    return 0;
}