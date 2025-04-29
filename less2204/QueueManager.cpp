#include "QueueManager.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <thread>
#include <chrono>

using namespace std;

void listDoctors(const vector<Doctor>& doctors) {
    cout << "\n������ �����:\n";
    for (size_t i = 0; i < doctors.size(); ++i) {
        cout << i + 1 << ". " << doctors[i].name << " (" << doctors[i].specialization << ")\n";
    }
}

void showQueues(const vector<Doctor>& doctors) {
    cout << "\n�������� ���� ����:\n";
    for (const auto& doc : doctors) {
        cout << doc.name << " (" << doc.specialization << "): " << doc.q.size() << " ��������\n";
    }
}

void addPatient(vector<Doctor>& doctors, int& patientCounter) {
    if (doctors.empty()) {
        cout << "���� �����.\n";
        return;
    }
    listDoctors(doctors);
    cout << "������� ����� �����: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > static_cast<int>(doctors.size())) {
        cout << "������� �����!\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Doctor& doc = doctors[choice - 1];

    Patient p;
    cout << "������ ��'� ��������: ";
    getline(cin, p.name);
    p.id = patientCounter++;

    doc.q.push(p);
    cout << "�������� ������ �� ����� \u2116" << p.id << " �� " << doc.name << "\n";
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

    cout << "\n������: " << p.name << " �� " << doctor << "\n";
    cout << "���������� ��������:\n";
    waitTimer(5);

    cout << "������� �������? (1 - ���, ���� - �): ";
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
        cout << "\n����� �� " << doc.name << " (" << doc.specialization << "):\n";
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
        f1 << "�������: " << p.name << " (ID: " << p.id << ")\n";
    }
    for (const auto& p : untreated) {
        f2 << "�������: " << p.name << " (ID: " << p.id << ")\n";
    }
    cout << "���������� ���������.\n";
}