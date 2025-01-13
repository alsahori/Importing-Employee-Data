#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream> // For file operations
using namespace std;

class employeeInfo {
private:
    string name;
    string streetAddress;
    string city;
    string state;
    string zipcode;
    string department;
    double salary;
    int ID;
public:
    void setID(int);
    void employeeIntake(); // Manual input
    void employeeIntake(ifstream& file); // Read from file
    void giveRaise();
    void printEmployee();
    void printEmployeeList(vector<employeeInfo>);
};

void employeeInfo::setID(int id) {
    ID = id;
}

// Overloaded employeeIntake for manual input
void employeeInfo::employeeIntake() {
    cout << "Please enter employee's name: ";
    getline(cin, name);
    cout << "Street Address: ";
    getline(cin, streetAddress);
    cout << "City: ";
    getline(cin, city);
    cout << "State: ";
    getline(cin, state);
    cout << "Zipcode: ";
    getline(cin, zipcode);
    cout << "Department: ";
    getline(cin, department);
    cout << "Current Salary: ";
    cin >> salary;
    cin.ignore();
}

// Overloaded employeeIntake to read from file
void employeeInfo::employeeIntake(ifstream& file) {
    getline(file, name);
    getline(file, streetAddress);
    getline(file, city);
    getline(file, state);
    getline(file, zipcode);
    getline(file, department);
    file >> salary;
    file.ignore(); // Ignore the newline after the salary
}

void employeeInfo::giveRaise() {
    int bump = 0;
    cout << fixed << setprecision(2);
    cout << name << "'s current salary is $" << salary << " per year. What % increase would you like to apply? " << endl;
    cin >> bump;
    cin.ignore();
    salary += (salary * bump) / 100;
    cout << name << "'s new salary is now $" << salary << " per year." << endl;
}

void employeeInfo::printEmployee() {
    cout << left;
    cout << setw(20) << "Employee ID: " << ID << endl;
    cout << setw(20) << "Name: " << name << endl;
    cout << setw(20) << "Street Address: " << streetAddress << endl;
    cout << setw(20) << "City: " << city << endl;
    cout << setw(20) << "State: " << state << endl;
    cout << setw(20) << "Zipcode: " << zipcode << endl;
    cout << setw(20) << "Department: " << department << endl;
    cout << fixed << setprecision(2);
    cout << setw(20) << "Salary: " << "$" << salary << endl;
    cout << "_________________________________________" << endl;
}

void employeeInfo::printEmployeeList(vector<employeeInfo> empList) {
    for (int i = 0; i < empList.size(); i++) {
        cout << i + 1 << ". " << empList.at(i).name << endl;
    }
}

int main() {
    int menu;
    int x = 0;
    int empCount = 1000;
    vector<employeeInfo> allEmployees;
    employeeInfo tempEmployee;
    ifstream employeeFile("Text.txt"); // Open the file containing employee info

    if (!employeeFile.is_open()) {
        cout << "Error: Could not open the file!" << endl;
        return 1;
    }

    cout << "Welcome to our Employee Information System" << endl;
    cout << "Please select from the following menu options" << endl;

    // Read employees from the file
    while (!employeeFile.eof()) {
        tempEmployee.setID(empCount);
        tempEmployee.employeeIntake(employeeFile); // Call the file version of employeeIntake
        allEmployees.push_back(tempEmployee);
        empCount++;
    }

    employeeFile.close(); // Close the file after reading

    do {
        cout << "Menu:" << endl;
        cout << "1. Add employee (manual input)" << endl;
        cout << "2. Give an employee a raise" << endl;
        cout << "3. Print an employee's info" << endl;
        cout << "4. Print all employee info" << endl;
        cout << "5. Exit" << endl;
        cin >> menu;
        cin.ignore();

        if (menu == 1) {
            tempEmployee.setID(empCount);
            tempEmployee.employeeIntake(); // Call the manual input version
            allEmployees.push_back(tempEmployee);
            empCount++;
        }

        if (menu == 2) {
            if (allEmployees.empty()) {
                cout << "There are no employees listed in the system yet, please add one first" << endl;
            }
            else {
                cout << "Pick an Employee: " << endl;
                tempEmployee.printEmployeeList(allEmployees);
                cout << "Enter Choice: ";
                cin >> x;
                cin.ignore();
                allEmployees.at(x - 1).giveRaise();
            }
        }

        if (menu == 3) {
            if (allEmployees.empty()) {
                cout << "There are no employees listed in the system yet, please add one first" << endl;
            }
            else {
                cout << "Pick an Employee: " << endl;
                tempEmployee.printEmployeeList(allEmployees);
                cout << "Enter Choice: ";
                cin >> x;
                cin.ignore();
                allEmployees.at(x - 1).printEmployee();
            }
        }

        if (menu == 4) {
            if (allEmployees.empty()) {
                cout << "There are no employees listed in the system yet, please add one first" << endl;
            }
            else {
                for (int i = 0; i < allEmployees.size(); i++) {
                    allEmployees.at(i).printEmployee();
                }
            }
        }

        if (menu == 5) {
            cout << "Thank you for using the Employee Information System" << endl;
        }

        if (menu != 1 && menu != 2 && menu != 3 && menu != 4 && menu != 5) {
            cout << "Invalid Entry, please try again\n";
        }
    } while (menu != 5);

    cout << "The Program will be shutting down now" << endl;
    return 0;
}
