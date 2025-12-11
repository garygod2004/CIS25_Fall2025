#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <ctime>
#include <algorithm>   // only used for median sort on a copy of grades
#include <map>

using namespace std;

// ---------------------------------------------------------------------
// Student
// ---------------------------------------------------------------------
// Represents one student in the cohort.
// Stores ID, name, attendance info for today, and a list of grades.
// Also provides helper functions to compute average and median grades.
struct Student {
    int id{};                // unique ID for each student
    string name;             // student name
    bool presentToday{false}; // whether the student is currently checked in
    string checkInTime;      // last check-in time (HH:MM:SS)
    string checkOutTime;     // last check-out time (HH:MM:SS)
    vector<int> grades;      // all grades for this student

    // Compute the average grade.
    double average() const {
        if (grades.empty()) return 0.0;
        int sum = 0;
        for (int g : grades) sum += g;
        return static_cast<double>(sum) / grades.size();
    }

    // Compute the median grade.
    // We copy the grades into a temporary vector and sort *that*,
    // so we do not change the original order of grades.
    double median() const {
        if (grades.empty()) return 0.0;
        vector<int> tmp = grades;
        // Sorting ONLY this small temp vector is fine; the project’s
        // manual sorting requirement is on the student list, not here.
        sort(tmp.begin(), tmp.end());
        size_t n = tmp.size();
        if (n % 2 == 1) {
            return tmp[n / 2];                 // odd number of grades
        } else {
            return (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0; // even number
        }
    }
};

// ---------------------------------------------------------------------
// Time helper functions
// ---------------------------------------------------------------------
// Return the current date as a string in the format YYYY-MM-DD.
string currentDate() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char buf[11]; // YYYY-MM-DD + null terminator
    strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
    return string(buf);
}

// Return the current time as a string in the format HH:MM:SS.
string currentTime() {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char buf[9]; // HH:MM:SS + null terminator
    strftime(buf, sizeof(buf), "%H:%M:%S", ltm);
    return string(buf);
}

// ---------------------------------------------------------------------
// Utility: split a string by a delimiter
// ---------------------------------------------------------------------
// Splits a string like "101,Jane Doe,95" into {"101","Jane Doe","95"}.
vector<string> split(const string &s, char delim) {
    vector<string> tokens;
    string item;
    stringstream ss(s);
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

// ---------------------------------------------------------------------
// File I/O: roster & grades
// ---------------------------------------------------------------------
// Load students from a roster file into the vector.
// Expected format per line: id,name
void loadRoster(const string &filename, vector<Student> &students) {
    ifstream in(filename);
    if (!in) {
        cerr << "Could not open roster file: " << filename << endl;
        return;
    }
    students.clear();
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        auto parts = split(line, ',');
        if (parts.size() < 2) continue; // need id and name
        Student s;
        s.id = stoi(parts[0]);
        s.name = parts[1];
        students.push_back(s);
    }
    cout << "Loaded " << students.size() << " students from " << filename << ".\n";
}

// Load grades from a file and attach them to the matching students.
// Expected format per line: id,grade1,grade2,...
void loadGrades(const string &filename, vector<Student> &students) {
    ifstream in(filename);
    if (!in) {
        // No grades file yet is fine; students will just have empty grade lists.
        return;
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        auto parts = split(line, ',');
        if (parts.size() < 2) continue;
        int id = stoi(parts[0]);

        // Find student by id in the vector.
        auto it = find_if(students.begin(), students.end(),
                          [id](const Student &s){ return s.id == id; });
        if (it == students.end()) continue;

        it->grades.clear();
        for (size_t i = 1; i < parts.size(); ++i) {
            if (!parts[i].empty()) {
                it->grades.push_back(stoi(parts[i]));
            }
        }
    }
}

// Save current grades back to a CSV file so they persist between runs.
// Format written: id,grade1,grade2,...
void saveGrades(const string &filename, const vector<Student> &students) {
    ofstream out(filename);
    if (!out) {
        cerr << "Could not open grades file for writing: " << filename << endl;
        return;
    }
    for (const auto &s : students) {
        out << s.id;
        for (size_t i = 0; i < s.grades.size(); ++i) {
            out << "," << s.grades[i];
        }
        out << "\n";
    }
}

// ---------------------------------------------------------------------
// Listing students (paged output)
// ---------------------------------------------------------------------
// Displays students with their average and median. Shows a few at a time
// and pauses so the user can read the output.
void listStudentsPaged(const vector<Student> &students, int pageSize = 5) {
    int total = static_cast<int>(students.size());
    if (total == 0) {
        cout << "No students loaded.\n";
        return;
    }

    cout << fixed << setprecision(2);

    // The ENTER key handling is set up in main using cin.ignore().
    for (int i = 0; i < total; ++i) {
        const Student &s = students[i];
        cout << s.id << " - " << s.name
             << " | Avg: " << s.average()
             << " | Median: " << s.median() << "\n";

        // After each page, wait for the user to press ENTER.
        if ((i + 1) % pageSize == 0 && (i + 1) < total) {
            cout << "-- More -- Press ENTER to continue --";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// ---------------------------------------------------------------------
// Manual sorting functions (Selection Sort)
// ---------------------------------------------------------------------
// The project requires implementing our own sorting, so we use
// selection sort on the student list instead of std::sort.

// Sort students by ID in ascending order using selection sort.
void selectionSortById(vector<Student> &students) {
    int n = static_cast<int>(students.size());
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (students[j].id < students[minIdx].id) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(students[i], students[minIdx]);
        }
    }
}

// Sort students by name (alphabetical) using selection sort.
void selectionSortByName(vector<Student> &students) {
    int n = static_cast<int>(students.size());
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (students[j].name < students[minIdx].name) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(students[i], students[minIdx]);
        }
    }
}

// Sort students by average grade in *descending* order using selection sort.
void selectionSortByAverage(vector<Student> &students) {
    int n = static_cast<int>(students.size());
    // sort by average descending (highest first)
    for (int i = 0; i < n - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (students[j].average() > students[maxIdx].average()) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            swap(students[i], students[maxIdx]);
        }
    }
}

// ---------------------------------------------------------------------
// Binary search by student ID
// ---------------------------------------------------------------------
// Assumes the students vector is already sorted by ID.
// Returns the index of the student if found, or -1 if not found.
int binarySearchById(const vector<Student> &students, int targetId) {
    int left = 0;
    int right = static_cast<int>(students.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (students[mid].id == targetId) return mid;
        if (students[mid].id < targetId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// ---------------------------------------------------------------------
// Attendance logging
// ---------------------------------------------------------------------
// Append a single attendance record to the log file.
// Format: date,time,id,name,action
void appendAttendanceLog(const string &filename, const Student &s, const string &action) {
    ofstream out(filename, ios::app);
    if (!out) {
        cerr << "Could not open attendance log for appending.\n";
        return;
    }
    out << currentDate() << "," << currentTime() << ","
        << s.id << "," << s.name << "," << action << "\n";
}

// Check a student in: set the flag, store the time, and log to file.
void markCheckIn(vector<Student> &students) {
    if (students.empty()) {
        cout << "No students.\n";
        return;
    }
    // Ensure the list is sorted by ID so binary search works.
    selectionSortById(students);

    cout << "Enter student ID to check in: ";
    int id;
    cin >> id;

    int idx = binarySearchById(students, id);
    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }

    Student &s = students[idx];
    s.presentToday = true;
    s.checkInTime = currentTime();
    appendAttendanceLog("attendance_log.csv", s, "check-in");

    cout << s.name << " checked in at " << s.checkInTime << ".\n";
}

// Check a student out: clear the flag, store the time, and log to file.
void markCheckOut(vector<Student> &students) {
    if (students.empty()) {
        cout << "No students.\n";
        return;
    }
    selectionSortById(students);

    cout << "Enter student ID to check out: ";
    int id;
    cin >> id;

    int idx = binarySearchById(students, id);
    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }

    Student &s = students[idx];
    s.presentToday = false;
    s.checkOutTime = currentTime();
    appendAttendanceLog("attendance_log.csv", s, "check-out");

    cout << s.name << " checked out at " << s.checkOutTime << ".\n";
}

// ---------------------------------------------------------------------
// Grades
// ---------------------------------------------------------------------
// Prompt for a student ID and add a new grade (0–100) to that student.
void addGrade(vector<Student> &students) {
    if (students.empty()) {
        cout << "No students.\n";
        return;
    }
    selectionSortById(students);

    cout << "Enter student ID to add grade for: ";
    int id;
    cin >> id;

    int idx = binarySearchById(students, id);
    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Enter grade (0-100): ";
    int g;
    cin >> g;

    if (g < 0 || g > 100) {
        cout << "Invalid grade.\n";
        return;
    }

    students[idx].grades.push_back(g);
    cout << "Grade added for " << students[idx].name << ".\n";
}

// ---------------------------------------------------------------------
// Reports
// ---------------------------------------------------------------------
// Generate a daily attendance report for today and write it to a file.
void dailyReport(const string &attendanceFile, const string &outFile) {
    ifstream in(attendanceFile);
    if (!in) {
        cerr << "No attendance log found.\n";
        return;
    }
    ofstream out(outFile);
    if (!out) {
        cerr << "Could not open daily report file.\n";
        return;
    }

    string today = currentDate();
    out << "Daily Attendance Report for " << today << "\n";
    out << "Date,Time,ID,Name,Action\n";

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        auto parts = split(line, ',');
        if (parts.size() < 5) continue;
        if (parts[0] == today) {
            out << line << "\n";
        }
    }

    cout << "Daily report written to " << outFile << ".\n";
}

// Generate an overall report summarizing attendance and grades
// for every student in the roster.
void overallReport(const vector<Student> &students,
                   const string &attendanceFile,
                   const string &outFile) {
    ofstream out(outFile);
    if (!out) {
        cerr << "Could not open overall report file.\n";
        return;
    }

    // Count total check-ins per student (how many times they were present).
    map<int, int> presentCount;

    ifstream in(attendanceFile);
    if (in) {
        string line;
        while (getline(in, line)) {
            if (line.empty()) continue;
            auto parts = split(line, ',');
            if (parts.size() < 5) continue;
            int id = stoi(parts[2]);
            string action = parts[4];
            if (action == "check-in") {
                presentCount[id]++;
            }
        }
    }

    out << "Overall Report\n";
    out << "ID,Name,TimesPresent,NumGrades,Average,Median\n";

    out << fixed << setprecision(2);
    for (const auto &s : students) {
        int times = presentCount[s.id];
        out << s.id << ","
            << s.name << ","
            << times << ","
            << s.grades.size() << ","
            << s.average() << ","
            << s.median() << "\n";
    }

    cout << "Overall report written to " << outFile << ".\n";
}

// ---------------------------------------------------------------------
// Search menu (binary search wrapper)
// ---------------------------------------------------------------------
// Ask the user for an ID, search using binary search, and display details.
void searchStudentById(vector<Student> &students) {
    if (students.empty()) {
        cout << "No students.\n";
        return;
    }
    selectionSortById(students);

    cout << "Enter ID to search: ";
    int id;
    cin >> id;

    int idx = binarySearchById(students, id);
    if (idx == -1) {
        cout << "Student not found.\n";
        return;
    }

    const Student &s = students[idx];
    cout << "Found: " << s.id << " - " << s.name << "\n";
    cout << "Grades: ";
    for (int g : s.grades) cout << g << " ";
    cout << "\nAverage: " << fixed << setprecision(2) << s.average()
         << " Median: " << s.median() << "\n";
}

// ---------------------------------------------------------------------
// Sort menu
// ---------------------------------------------------------------------
// Simple menu that lets the user pick which field to sort by.
void menuSort(vector<Student> &students) {
    if (students.empty()) {
        cout << "No students.\n";
        return;
    }
    cout << "Sort by:\n";
    cout << "1. ID\n";
    cout << "2. Name\n";
    cout << "3. Average grade (descending)\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            selectionSortById(students);
            break;
        case 2:
            selectionSortByName(students);
            break;
        case 3:
            selectionSortByAverage(students);
            break;
        default:
            cout << "Invalid choice.\n";
            return;
    }
    cout << "Sorted.\n";
}

// ---------------------------------------------------------------------
// main
// ---------------------------------------------------------------------
// Drives the entire Cohort Manager Pro program.
// Loads data, shows a menu, and calls helper functions based on user choice.
int main() {
    vector<Student> students;

    // Initial load from CSV files (long-term storage).
    loadRoster("roster.csv", students);
    loadGrades("grades.csv", students);

    int choice;

    do {
        cout << "\n=== Cohort Manager Pro ===\n";
        cout << "1. List students\n";
        cout << "2. Search student by ID (binary search)\n";
        cout << "3. Sort students\n";
        cout << "4. Mark check-in\n";
        cout << "5. Mark check-out\n";
        cout << "6. Add grade\n";
        cout << "7. Generate daily report\n";
        cout << "8. Generate overall report\n";
        cout << "9. Save grades\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            // If input fails (e.g., user types a letter), exit the loop.
            break;
        }

        switch (choice) {
            case 1: {
                // Clear leftover newline before using getline/ignore in paging.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                listStudentsPaged(students);
                break;
            }
            case 2:
                searchStudentById(students);
                break;
            case 3:
                menuSort(students);
                break;
            case 4:
                markCheckIn(students);
                break;
            case 5:
                markCheckOut(students);
                break;
            case 6:
                addGrade(students);
                break;
            case 7:
                dailyReport("attendance_log.csv", "report_daily.txt");
                break;
            case 8:
                overallReport(students, "attendance_log.csv", "report_overall.txt");
                break;
            case 9:
                saveGrades("grades.csv", students);
                cout << "Grades saved.\n";
                break;
            case 0:
                // Auto-save grades on exit so nothing is lost.
                saveGrades("grades.csv", students);
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }

    } while (choice != 0);

    return 0;
}
