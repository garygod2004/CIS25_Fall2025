// -----------------------------------------------------------
// Working With External Data in C++
// This program loads real Netflix data from a CSV file,
// extracts at least 5 fields, stores them in a class, and
// displays at least 10 entries in a readable format.
// -----------------------------------------------------------

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Name of the CSV file we want to load.
// The file must be in the SAME folder as this .cpp file.
const string FILENAME = "netflix_titles.csv";


// -----------------------------------------------------------
// Helper function: trim()
// Removes extra spaces and quotation marks from the beginning
// and end of a string. This makes the CSV data cleaner.
// -----------------------------------------------------------
string trim(const string &s) {
    size_t start = 0;
    size_t end = s.size();

    // Move 'start' forward if the character is a space, tab, or quote
    while (start < end && (s[start] == ' ' || s[start] == '\t' || s[start] == '\"')) {
        start++;
    }

    // Move 'end' backward if the character is a space, tab, or quote
    while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t' || s[end - 1] == '\"')) {
        end--;
    }

    return s.substr(start, end - start);
}


// -----------------------------------------------------------
// Helper function: splitCSVLine()
// Splits one line of a CSV file into individual fields.
// This version handles commas INSIDE quotes properly.
// Example: "United States, Canada" stays together.
// -----------------------------------------------------------
vector<string> splitCSVLine(const string &line) {
    vector<string> fields;
    string current;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        // Toggle the inQuotes flag when encountering a quote mark
        if (c == '\"') {
            inQuotes = !inQuotes;
            current += c;
        }
        // If we see a comma AND we are NOT inside quotes, this marks a new field
        else if (c == ',' && !inQuotes) {
            fields.push_back(trim(current));
            current.clear();
        }
        else {
            current += c;
        }
    }

    // Add the final field
    if (!current.empty()) {
        fields.push_back(trim(current));
    }

    return fields;
}


// -----------------------------------------------------------
// Class: NetflixTitle
// This class stores the information for one row of the dataset.
// We use at least 5 fields: show_id, type, title, director,
// country, release_year, rating, and duration.
// -----------------------------------------------------------
class NetflixTitle {
private:
    string show_id;
    string type;
    string title;
    string director;
    string country;
    string release_year;
    string rating;
    string duration;

public:
    // Default constructor (not used but good practice to include)
    NetflixTitle() {}

    // Custom constructor that assigns all fields
    NetflixTitle(const string &show_id,
                 const string &type,
                 const string &title,
                 const string &director,
                 const string &country,
                 const string &release_year,
                 const string &rating,
                 const string &duration)
        : show_id(show_id),
          type(type),
          title(title),
          director(director),
          country(country),
          release_year(release_year),
          rating(rating),
          duration(duration) {}

    // Display one Netflix title in a readable format
    void printInfo() const {
        cout << "-------------------------------------------\n";
        cout << "Title:        " << title << "\n";
        cout << "Type:         " << type << "\n";
        cout << "Director:     " << (director.empty() ? "N/A" : director) << "\n";
        cout << "Country:      " << (country.empty() ? "N/A" : country) << "\n";
        cout << "Release Year: " << release_year << "\n";
        cout << "Rating:       " << (rating.empty() ? "N/A" : rating) << "\n";
        cout << "Duration:     " << duration << "\n";
        cout << "Show ID:      " << show_id << "\n";
    }
};


int main() {

    // -------------------------------------------------------
    // Step 1: Open the CSV file
    // -------------------------------------------------------
    ifstream file(FILENAME);
    if (!file.is_open()) {
        cerr << "Error: Could not open file \"" << FILENAME << "\".\n";
        cerr << "Make sure the CSV file is in the same folder as this program.\n";
        return 1;
    }

    string line;

    // -------------------------------------------------------
    // Step 2: Skip the header line (the first row contains labels)
    // -------------------------------------------------------
    if (!getline(file, line)) {
        cerr << "Error: File is empty or could not read header.\n";
        return 1;
    }

    // Vector to store the NetflixTitle objects we create
    vector<NetflixTitle> titles;
    const int MAX_TITLES = 10; // Requirement: load at least 10 rows

    // -------------------------------------------------------
    // Step 3: Read the file line-by-line
    // -------------------------------------------------------
    while (getline(file, line) && (int)titles.size() < MAX_TITLES) {

        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Split the CSV row into columns
        vector<string> fields = splitCSVLine(line);

        // The dataset MUST have at least 10 columns for our fields
        if (fields.size() < 10) {
            continue; // skip bad/malformed rows
        }

        // Extract the fields we care about using column indexes
        string show_id      = fields[0];
        string type         = fields[1];
        string title        = fields[2];
        string director     = fields[3];
        string country      = fields[5];
        string release_year = fields[7];
        string rating       = fields[8];
        string duration     = fields[9];

        // Create a NetflixTitle object and store it
        NetflixTitle t(show_id, type, title, director,
                       country, release_year, rating, duration);
        titles.push_back(t);
    }

    file.close(); // Done reading the file

    // -------------------------------------------------------
    // Step 4: Display the titles we loaded
    // -------------------------------------------------------
    if (titles.empty()) {
        cout << "No titles were loaded from the file.\n";
    } else {
        cout << "Loaded " << titles.size() << " Netflix titles from the dataset.\n";
        cout << "Displaying them below:\n\n";

        for (size_t i = 0; i < titles.size(); ++i) {
            cout << "Entry #" << (i + 1) << "\n";
            titles[i].printInfo();
            cout << "\n";
        }
    }

    return 0; // end of program
}
