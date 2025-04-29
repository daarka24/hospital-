#include "QueueManager.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <thread>
#include <chrono>

using namespace std;

void listDoctors(const vector<Doctor>& doctors) {
    cout << "\nСписок лікарів:\n";
    for (size_t i = 0; i < doctors.size(); ++i) {
        cout << i + 1 << ". " << doctors[i].name << " (" << doctors[i].specialization << ")\n";
    }
}

void showQueues(const vector<Doctor>& doctors) {
    cout << "\nПоточний стан черг:\n";
    for (const auto& doc : doctors) {
        cout << doc.name << " (" << doc.specialization << "): " << doc.q.size() << " пацієнтів\n";
    }
}

void addPatient(vector<Doctor>& doctors, int& patientCounter) {
    if (doctors.empty()) {
        cout << "Немає лікарів.\n";
        return;
    }
    listDoctors(doctors);
    cout << "Виберіть номер лікаря: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > static_cast<int>(doctors.size())) {
        cout << "Невірний номер!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Doctor& doc = doctors[choice - 1];

    Patient p;
    cout << "Введіть ім'я пацієнта: ";
    getline(cin, p.name);
    p.id = patientCounter++;

    doc.q.push(p);
    cout << "Пацієнта додано до черги \u2116" << p.id << " до " << doc.name << "\n";
}

void waitTimer(int seconds) {
    for (int i = seconds; i > 0; --i) {
        cout << i << "... " << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << endl;
}

void processPatient(Patient& p, const string& doctor,
    vector<Patient>& treated, vector<Patient>& untreated) {

    cout << "\nВиклик: " << p.name << " до " << doctor << "\n";
    cout << "Очікування пацієнта:\n";
    waitTimer(5);

    cout << "Пацієнт прийшов? (1 - так, інше - ні): ";
    string response;
    getline(cin, response);

    if (response == "1") {
        treated.push_back(p);
    }
    else {
        untreated.push_back(p);
    }
}

void processPatients(vector<Doctor>& doctors, vector<Patient>& treated, vector<Patient>& untreated) {
    for (auto& doc : doctors) {
        cout << "\nЧерга до " << doc.name << " (" << doc.specialization << "):\n";
        while (!doc.q.empty()) {
            Patient p = doc.q.front();
            doc.q.pop();
            processPatient(p, doc.name, treated, untreated);
        }
    }
}

void saveResults(const vector<Patient>& treated, const vector<Patient>& untreated) {
    ofstream f1("treated.txt");
    ofstream f2("untreated.txt");
    for (const auto& p : treated) {
        f1 << "Пацієнт: " << p.name << " (ID: " << p.id << ")\n";
    }
    for (const auto& p : untreated) {
        f2 << "Пацієнт: " << p.name << " (ID: " << p.id << ")\n";
    }
    cout << "Результати збережено.\n";
}