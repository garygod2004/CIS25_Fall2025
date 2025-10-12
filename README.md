#Week 7

##How it works:

The program creates a dynamic array of Item { std::string name; int id; }.

Names are generated in name order: Name001 … Name100.

A second copy of the array is sorted by ID so we can run a binary search by ID.

User enters an ID → program searches the ID-sorted copy → prints match or “not found.”

Memory is freed with delete[].

Valid examples: 1000, 1007, 1014, 1021, 1028, ...
