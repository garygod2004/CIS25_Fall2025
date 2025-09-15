#include <iostream>
#include <algorithm> // for std::max
using namespace std;

int main() {
    float n1, n2, n3;

    cout << "Enter three numbers: ";
    if (!(cin >> n1 >> n2 >> n3)) {
        cerr << "Input error. Please enter three numbers.\n";
        return 1;
    }

    cout << "You entered: n1=" << n1 << ", n2=" << n2 << ", n3=" << n3 << endl;

    float largest = max(n1, max(n2, n3));
    cout << "Largest number: " << largest << endl;

    return 0;
}
