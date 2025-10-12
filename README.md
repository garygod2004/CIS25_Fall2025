# Week 7 – Pointers and Memory

## Overview
This lab demonstrates **dynamic memory**, **structs**, and a **binary search**.  
We allocate an array of `Item` (name + id), keep it **sorted by name**, and search for an item **by id** using a copy sorted by id.

**ID pattern:** only numbers of the form `1000 + 7k` are valid (e.g., 1000, 1007, 1014, …).  
Other numbers (like 1001 or 1010) will return **“not found.”**

**What the program does**
- Defines `struct Item { std::string name; int id; }`
- Uses `new[]` to create at least 100 records (`Name001` … `Name100`)
- Copies and sorts that array **by id** for the binary search
- Prompts for an id, prints the result, and frees memory with `delete[]`
