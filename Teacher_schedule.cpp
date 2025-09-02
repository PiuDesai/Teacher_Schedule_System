#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <sstream>
#include <algorithm>  // for trimming
using namespace std;

// Helper function to trim spaces
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

class Teacher {
protected:
    string id;
    string name;
    string dept;
    string date;
    vector<string> class_no;
    vector<string> subjects;
    vector<string> times;

public:
    void addTeacherDetails() {
        cout << "(to assign schedule)" << endl;
        cout << "\nDATE: ";
        cin >> date;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "ENTER FACULTY DETAILS: " << endl;
        cout << "ID: ";
        getline(cin, id);

        cout << "NAME: ";
        getline(cin, name);

        cout << "DEPARTMENT: ";
        getline(cin, dept);
    }
};

class Schedule : public Teacher {
public:
    void addClass() {
        string subject, time, c_no;
        ofstream outfile("schedule.txt", ios::app);  // Append mode

        // Save teacher's basic info to the file
        outfile << "DATE : " << date << endl;
        outfile << "ID : " << id << endl;
        outfile << "NAME : " << name << endl;
        outfile << "DEPARTMENT: " << dept << endl;
        outfile << "COURSE            TIME               CLASSROOM" << endl;

        int numClasses;
        cout << "Enter the number of classes: ";
        cin >> numClasses;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < numClasses; i++) {
            cout << "\nCOURSE: ";
            getline(cin, subject);
            subjects.push_back(subject);

            cout << "TIME SLOT: ";
            getline(cin, time);
            times.push_back(time);

            cout << "CLASSROOM_NO: ";
            getline(cin, c_no);
            class_no.push_back(c_no);

            outfile << subject << "        " << time << "        " << c_no << endl;
        }

        outfile << endl;  // blank line after each teacher block
        outfile.close();
        cout << "Schedule saved successfully!" << endl;
    }
};

class DisplaySchedule : public Schedule {
public:
    void display_schedule() {
        string entered_id;
        cout << "ENTER YOUR ID TO VIEW YOUR SCHEDULE: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        getline(cin, entered_id);

        ifstream infile("schedule.txt");
        if (!infile.is_open()) {
            cout << "No schedule found!" << endl;
            return;
        }

        string line, file_id;
        bool id_found = false;

        while (getline(infile, line)) {
            if (line.rfind("ID :", 0) == 0) { // line starts with "ID :"
                file_id = trim(line.substr(5));

                if (file_id == entered_id) {
                    id_found = true;

                    cout << "ID: " << entered_id << endl;

                    getline(infile, line);
                    cout << line << endl;  // Name

                    getline(infile, line);
                    cout << line << endl;  // Department

                    getline(infile, line);
                    cout << line << endl;  // Header

                    while (getline(infile, line) && !line.empty()) {
                        cout << line << endl;
                    }
                    break;
                }
            }
        }

        if (!id_found) {
            cout << "ID does not match. Access Denied!" << endl;
        }

        infile.close();
    }
};

int main() {
    DisplaySchedule D1;

    int c;
    string pass;
    cout << "***WELCOME TO TEACHER SCHEDULE SYSTEM*****" << endl << endl;
    cout << "ENTER: " << endl;
    cout << "1. DISTRIBUTE SCHEDULE TO FACULTY " << endl;
    cout << "(only HOD can distribute the schedule.)" << endl;
    cout << "2. SEE TODAY'S SCHEDULE (for faculty)" << endl;

    cout << "ENTER: ";
    cin >> c;

    switch (c) {
        case 1: {
            cout << "\nENTER PASSWORD: ";
            cin >> pass;
            if (pass == "comp123") {
                cout << "LOGIN SUCCESSFULLY...." << endl;
                D1.addTeacherDetails();
                D1.addClass();
            } else {
                cout << "INVALID PASSWORD" << endl;
            }
            break;
        }
        case 2: {
            D1.display_schedule();
            break;
        }
        default:
            cout << "INVALID" << endl;
    }

    return 0;
}
