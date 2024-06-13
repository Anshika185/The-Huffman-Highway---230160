#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student {
public:
    string name;
    int rollNumber;
    string course;
    int totalMarks;

    Student(string n, int r, string c, int m) : name(n), rollNumber(r), course(c), totalMarks(m) {}
};

class StudentRecordSystem {
private:
    vector<Student> records;

    int findRecord(int rollNumber) {
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].rollNumber == rollNumber) {
                return i;
            }
        }
        return -1; // Record not found
    }

public:
    void createRecord(string name, int rollNumber, string course, int totalMarks) {
        if (findRecord(rollNumber) != -1) {
            cout << "Record with roll number " << rollNumber << " already exists." << endl;
            return;
        }
        records.push_back(Student(name, rollNumber, course, totalMarks));
        cout << "Record created successfully." << endl;
    }

    void deleteRecord(int rollNumber) {
        int index = findRecord(rollNumber);
        if (index == -1) {
            cout << "Record with roll number " << rollNumber << " not found." << endl;
            return;
        }
        records.erase(records.begin() + index);
        cout << "Record deleted successfully." << endl;
    }

    void showRecord(int rollNumber) {
        int index = findRecord(rollNumber);
        if (index == -1) {
            cout << "Record with roll number " << rollNumber << " not found." << endl;
            return;
        }
        Student &s = records[index];
        cout << "Name: " << s.name << endl;
        cout << "Roll Number: " << s.rollNumber << endl;
        cout << "Course: " << s.course << endl;
        cout << "Total Marks: " << s.totalMarks << endl;
    }

    void searchRecord(int rollNumber) {
        int index = findRecord(rollNumber);
        if (index == -1) {
            cout << "Record with roll number " << rollNumber << " not found." << endl;
            return;
        }
        cout << "Record with roll number " << rollNumber << " exists." << endl;
    }

    void showAllRecords() {
        if (records.empty()) {
            cout << "No records found." << endl;
            return;
        }
        for (const auto &s : records) {
            cout << "Name: " << s.name << ", Roll Number: " << s.rollNumber << ", Course: " << s.course << ", Total Marks: " << s.totalMarks << endl;
        }
    }
};

int main() {
    StudentRecordSystem srs;
    int choice, rollNumber, totalMarks;
    string name, course;

    while (true) {
        cout << "\nStudent Record Management System" << endl;
        cout << "1. Create Record" << endl;
        cout << "2. Delete Record" << endl;
        cout << "3. Show Record" << endl;
        cout << "4. Search Record" << endl;
        cout << "5. Show All Records" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter name: ";
            cin.ignore(); // To ignore newline character left in the buffer
            getline(cin, name);
            cout << "Enter roll number: ";
            cin >> rollNumber;
            cout << "Enter course: ";
            cin.ignore(); // To ignore newline character left in the buffer
            getline(cin, course);
            cout << "Enter total marks: ";
            cin >> totalMarks;
            srs.createRecord(name, rollNumber, course, totalMarks);
            break;
        case 2:
            cout << "Enter roll number to delete: ";
            cin >> rollNumber;
            srs.deleteRecord(rollNumber);
            break;
        case 3:
            cout << "Enter roll number to show: ";
            cin >> rollNumber;
            srs.showRecord(rollNumber);
            break;
        case 4:
            cout << "Enter roll number to search: ";
            cin >> rollNumber;
            srs.searchRecord(rollNumber);
            break;
        case 5:
            srs.showAllRecords();
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
