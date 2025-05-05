#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Define a patient structure
struct Patient {
    string name;
    int age;
};

// Priority queues for different types of patients
queue<Patient> seriousQueue;       // Priority 1
queue<Patient> nonSeriousQueue;    // Priority 2
queue<Patient> generalQueue;       // Priority 3

// Add patient to the correct queue
void addPatient() {
    Patient p;
    int priority;

    cout << "Enter Patient Name: ";
    cin.ignore(); // To clear buffer
    getline(cin, p.name);
    cout << "Enter Patient Age: ";
    cin >> p.age;
    cout << "Select Priority (1. Serious, 2. Non-Serious, 3. General Checkup): ";
    cin >> priority;

    switch (priority) {
        case 1: seriousQueue.push(p); break;
        case 2: nonSeriousQueue.push(p); break;
        case 3: generalQueue.push(p); break;
        default: cout << "Invalid priority selected.\n"; return;
    }

    cout << "Patient added successfully.\n";
}

// Serve next patient based on priority
void servePatient() {
    if (!seriousQueue.empty()) {
        Patient p = seriousQueue.front();
        seriousQueue.pop();
        cout << "Serving Serious Patient: " << p.name << ", Age: " << p.age << endl;
    }
    else if (!nonSeriousQueue.empty()) {
        Patient p = nonSeriousQueue.front();
        nonSeriousQueue.pop();
        cout << "Serving Non-Serious Patient: " << p.name << ", Age: " << p.age << endl;
    }
    else if (!generalQueue.empty()) {
        Patient p = generalQueue.front();
        generalQueue.pop();
        cout << "Serving General Checkup Patient: " << p.name << ", Age: " << p.age << endl;
    }
    else {
        cout << "No patients in queue.\n";
    }
}

// Display all waiting patients
void displayQueues() {
    cout << "\n--- Current Waiting List ---\n";

    queue<Patient> temp;

    cout << "Serious Patients:\n";
    temp = seriousQueue;
    while (!temp.empty()) {
        cout << "- " << temp.front().name << ", Age: " << temp.front().age << endl;
        temp.pop();
    }

    cout << "Non-Serious Patients:\n";
    temp = nonSeriousQueue;
    while (!temp.empty()) {
        cout << "- " << temp.front().name << ", Age: " << temp.front().age << endl;
        temp.pop();
    }

    cout << "General Checkup Patients:\n";
    temp = generalQueue;
    while (!temp.empty()) {
        cout << "- " << temp.front().name << ", Age: " << temp.front().age << endl;
        temp.pop();
    }
}

// Main menu
int main() {
    int choice;
    do {
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Next Patient\n";
        cout << "3. Display All Patients\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addPatient(); break;
            case 2: servePatient(); break;
            case 3: displayQueues(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
