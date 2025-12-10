# Week 15 — Working with External Data in C++

## Overview
This assignment focuses on reading and processing real-world data in C++.  
For this project, I selected the **Netflix Movies and TV Shows Dataset** from Kaggle and wrote a C++ program that:

- Loads data from a CSV file  
- Parses and extracts meaningful fields  
- Stores each entry using a custom C++ class  
- Displays the results in a clean, readable format  

This assignment demonstrates skills in **file I/O, string processing, CSV parsing, vectors, and class design**.

---

## Dataset Used
**Kaggle Dataset:** Netflix Movies and TV Shows  
🔗 https://www.kaggle.com/datasets/shivamb/netflix-shows  

The file used in this project:  
`netflix_titles.csv`

---

## Program Features

### 1. File Input
- Opens and reads the CSV file using `ifstream`
- Skips the header row
- Loads at least **10 entries**

### 2. CSV Parsing
- Handles commas inside quotes  
- Trims spaces and quotation marks  
- Splits each row into clean fields  

### 3. Custom Class: `NetflixTitle`
Each row is stored as an object with the following fields:

- `show_id`  
- `type`  
- `title`  
- `director`  
- `country`  
- `release_year`  
- `rating`  
- `duration`  

### 4. Output Display
Prints the formatted details of each Netflix entry.

