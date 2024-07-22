#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

const string FILE_NAME = "StuRecord.txt";

struct Student {
    int rollNo;
    string name;
    char division;
    string address;

    void acceptInput() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cin.ignore();  // Ignore newline character
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Division: ";
        cin >> division;
        cin.ignore();  // Ignore newline character
        cout << "Enter Address: ";
        getline(cin, address);
    }

    void display() const {
        cout << "Roll Number: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }

    string serialize() const {
        stringstream ss;
        ss << rollNo << " " << name << " " << division << " " << address;
        return ss.str();
    }

    static Student deserialize(const string& data) {
        Student student;
        stringstream ss(data);
        ss >> student.rollNo;
        ss.ignore(); // Ignore space
        getline(ss, student.name, ' ');
        ss >> student.division;
        ss.ignore(); // Ignore space
        getline(ss, student.address);
        return student;
    }
};

void addRecord() {
    ofstream file(FILE_NAME, ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    Student student;
    student.acceptInput();
    file << student.serialize() << endl;
    file.close();
}

void deleteRecord(int rollNo) {
    ifstream fileIn(FILE_NAME);
    if (!fileIn.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    ofstream fileOut("temp.txt");
    if (!fileOut.is_open()) {
        cerr << "Error opening temp file for writing!" << endl;
        fileIn.close();
        return;
    }

    string line;
    bool found = false;
    while (getline(fileIn, line)) {
        Student student = Student::deserialize(line);
        if (student.rollNo != rollNo) {
            fileOut << line << endl;
        } else {
            found = true;
        }
    }

    fileIn.close();
    fileOut.close();

    if (found) {
        remove(FILE_NAME.c_str());
        rename("temp.txt", FILE_NAME.c_str());
        cout << "Record with Roll Number " << rollNo << " deleted." << endl;
    } else {
        cout << "Record with Roll Number " << rollNo << " not found." << endl;
    }
}

void searchRecord(int rollNo) {
    ifstream file(FILE_NAME);
    if (!file.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        Student student = Student::deserialize(line);
        if (student.rollNo == rollNo) {
            found = true;
            cout << "Record Found:" << endl;
            student.display();
            cout << endl;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Record with Roll Number " << rollNo << " not found." << endl;
    }
}

void displayRecords() {
    ifstream file(FILE_NAME);
    if (!file.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Student student = Student::deserialize(line);
        student.display();
        cout << endl;
    }

    file.close();
}

int main() {
    int choice;
    cout << "MENU:\n1. Add Record\n2. Display Records\n3. Delete Record\n4. Search Record\n5. Exit\n";
    cout << "-------------------\n";
    do {
        cout << "Enter the choice:";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "-------------------\n";
                addRecord();
                break;
            case 2:
                cout << "-------------------\n";
                displayRecords();
                break;
            case 3:
                cout << "-------------------\n";
                {
                    int rollNo;
                    cout << "Enter Roll Number to delete: ";
                    cin >> rollNo;
                    deleteRecord(rollNo);
                }
                break;
            case 4:
                cout << "-------------------\n";
                {
                    int rollNo;
                    cout << "Enter Roll Number to search: ";
                    cin >> rollNo;
                    searchRecord(rollNo);
                }
                break;
            case 5:
                cout << "-------------------\n";
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "-------------------\n";
                cout << "Invalid choice! Please enter again." << endl;
        }
        cout << "-------------------\n";
    } while (choice != 5);

    return 0;
}

