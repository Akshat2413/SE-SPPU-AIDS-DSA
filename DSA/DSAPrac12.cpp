#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX_NAME_LENGTH = 50;
const int MAX_DESIGNATION_LENGTH = 50;
const char* FILE_NAME = "Employee.txt";  // Global constant for file name

struct Employee {
    int employeeID;
    char name[MAX_NAME_LENGTH];
    char designation[MAX_DESIGNATION_LENGTH];
    double salary;
};

void addEmployee(fstream& file) {
    Employee employee;
    cout << "Enter employee ID: ";
    cin >> employee.employeeID;
    cout << "Enter employee name: ";
    cin.ignore();
    cin.getline(employee.name, MAX_NAME_LENGTH);
    cout << "Enter employee designation: ";
    cin.getline(employee.designation, MAX_DESIGNATION_LENGTH);
    cout << "Enter employee salary: ";
    cin >> employee.salary;

    file.write((char*)&employee, sizeof(Employee));
    cout << "Employee added successfully!" << endl;
}

void deleteEmployee(fstream& file) {
    int employeeID;
    bool found = false;
    Employee employee;

    cout << "Enter employee ID to delete: ";
    cin >> employeeID;

    fstream tempfile("temp.txt", ios::out | ios::binary);
    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg);
    
    while (file.read((char*)&employee, sizeof(Employee))) {
        if (employee.employeeID != employeeID) {
            tempfile.write((char*)&employee, sizeof(Employee));
        } else {
            found = true;
        }
    }

    file.close();
    tempfile.close();

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        cout << "Employee deleted successfully!" << endl;
    } else {
        cout << "Employee not found!" << endl;
    }

    file.open(FILE_NAME, ios::in | ios::out | ios::binary);
}

void displayEmployee(fstream& file) {
    int employeeID;
    bool found = false;
    Employee employee;

    cout << "Enter employee ID to display: ";
    cin >> employeeID;

    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg);

    while (file.read((char*)&employee, sizeof(Employee))) {
        if (employee.employeeID == employeeID) {
            found = true;
            cout << "Employee ID: " << employee.employeeID << endl;
            cout << "Name: " << employee.name << endl;
            cout << "Designation: " << employee.designation << endl;
            cout << "Salary: " << employee.salary << endl;
            break;
        }
    }

    if (!found) {
        cout << "Employee not found!" << endl;
    }
}

int main() {
    fstream file(FILE_NAME, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        cout << "Creating a new file..." << endl;
        file.open(FILE_NAME, ios::out | ios::binary);
        file.close(); // Close the file immediately
        return 1; // Exit the program as file creation failed
    }
    int choice;
    cout << "Employee Information System" << endl;
    cout << "1. Add Employee" << endl;
    cout << "2. Delete Employee" << endl;
    cout << "3. Display Employee" << endl;
    cout << "4. Quit" << endl;
    do {
        cout << "-------------------\n";
        cout << "Enter your choice: ";
        
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "-------------------\n";
                addEmployee(file);
                break;
            case 2:
                cout << "-------------------\n";
                deleteEmployee(file);
                break;
            case 3:
                cout << "-------------------\n";
                displayEmployee(file);
                break;
            case 4:
                cout << "-------------------\n";
                file.close();
                cout << "Exiting... ";
                return 0;
            default:
                cout << "-------------------\n";
                cout << "Invalid choice! Please try again." << endl;
        }

    }
    while(choice!=4);
    cout << "-------------------\n";
    return 0;
}

