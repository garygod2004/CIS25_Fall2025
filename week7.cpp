
#include <iostream>
#include <string>

struct Item {
    std::string name; 
    int id;
};

void populateSortedByName(Item* a, int N) {
    for (int i = 0; i < N; ++i) {
        int n = i + 1;

        
        a[i].name = std::string("Name")
                  + (n < 10 ? "00" : (n < 100 ? "0" : ""))
                  + std::to_string(n);

        a[i].id = 1000 + (i * 7);  
    }
}


void sortById(Item* a, int N) {
    for (int i = 0; i < N - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < N; ++j)
            if (a[j].id < a[minIdx].id) minIdx = j;
        if (minIdx != i) std::swap(a[i], a[minIdx]);
    }
}


int binarySearchById(Item* a, int N, int targetId) {
    int lo = 0, hi = N - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid].id == targetId) return mid;
        if (a[mid].id < targetId) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int main() {
    const int N = 100;                 
    Item* items = new Item[N];         
    populateSortedByName(items, N);    

    
    Item* itemsById = new Item[N];
    for (int i = 0; i < N; ++i) itemsById[i] = items[i];
    sortById(itemsById, N);

    std::cout << "Enter an ID to search for: ";
    int q;
    if (!(std::cin >> q)) { delete[] itemsById; delete[] items; return 0; }

    int pos = binarySearchById(itemsById, N, q);
    if (pos != -1)
        std::cout << "Found: name=" << itemsById[pos].name << ", id=" << itemsById[pos].id << "\n";
    else
        std::cout << "ID not found.\n";
        

    delete[] itemsById; 
    delete[] items;     
    return 0;
}