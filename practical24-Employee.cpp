#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Employee {
    int id;
    string name;
    string designation;
    double salary;

    // Function to display employee details
    void display() const {
        cout << "ID: " << id << ", Name: " << name 
             << ", Designation: " << designation 
             << ", Salary: " << fixed << setprecision(2) << salary << endl;
    }
};

class EmployeeManager {
private:
    const string filename = "employees.dat";

public:
    void addEmployee(const Employee& emp) {
        ofstream outFile(filename, ios::app | ios::binary);
        if (outFile) {
            outFile.write(reinterpret_cast<const char*>(&emp), sizeof(Employee));
            outFile.close();
            cout << "Employee added successfully." << endl;
        } else {
            cout << "Error opening file." << endl;
        }
    }

    void deleteEmployee(int id) {
        vector<Employee> employees = loadEmployees();
        bool found = false;

        ofstream outFile(filename, ios::binary);
        for (const auto& emp : employees) {
            if (emp.id != id) {
                outFile.write(reinterpret_cast<const char*>(&emp), sizeof(Employee));
            } else {
                found = true;
            }
        }
        outFile.close();

        if (found) {
            cout << "Employee with ID " << id << " deleted successfully." << endl;
        } else {
            cout << "Employee with ID " << id << " not found." << endl;
        }
    }

    void displayEmployee(int id) {
        vector<Employee> employees = loadEmployees();
        bool found = false;

        for (const auto& emp : employees) {
            if (emp.id == id) {
                emp.display();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Employee with ID " << id << " does not exist." << endl;
        }
    }

private:
    vector<Employee> loadEmployees() {
        vector<Employee> employees;
        Employee emp;

        ifstream inFile(filename, ios::binary);
        while (inFile.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
            employees.push_back(emp);
        }
        inFile.close();

        return employees;
    }
};

int main() {
    EmployeeManager manager;
    int choice;

    do {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Employee emp;
                cout << "Enter Employee ID: ";
                cin >> emp.id;
                cout << "Enter Employee Name: ";
                cin.ignore();
                getline(cin, emp.name);
                cout << "Enter Employee Designation: ";
                getline(cin, emp.designation);
                cout << "Enter Employee Salary: ";
                cin >> emp.salary;
                manager.addEmployee(emp);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Employee ID to delete: ";
                cin >> id;
                manager.deleteEmployee(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter Employee ID to display: ";
                cin >> id;
                manager.displayEmployee(id);
                break;
            }
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}