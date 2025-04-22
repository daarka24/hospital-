#include "QueueManager.h"
#include <iostream>
#include <fstream>
#include <future>
#include <chrono>
#include <limits>

using namespace std;

void listDoctors(const vector<Doctor>& doctors) {
    cout << "\nСписок лікарів:\n";
    for (size_t i = 0; i < doctors.size(); ++i) {
        cout << i + 1 << ". " << doctors[i].toString() << "\n";
    }
}

void showQueues(const vector<Doctor>& doctors) {
    cout << "\nПоточний стан черг:\n";
    for (const auto& doc : doctors) {
        cout << doc.toString() << ": " << doc.q.size() << " пацієнтів\n";
    }
}

void addPatient(vector<Doctor>& doctors, int& patientCounter) {
    if (doctors.empty()) {
        cout << "Немає лікарів.\n";
        return;
    }
    listDoctors(doctors);
    cout << "Виберіть номер лікаря: ";
    int choice; cin >> choice;
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
    cout << "Пацієнта додано до черги №" << p.id << " до " << doc.toString() << "\n";
}

void processPatient(const Patient& p, const string& doctor,
    vector<Patient>& treated,
    vector<Patient>& untreated)
{
    cout << "\nВиклик: " << p.toString() << " до " << doctor << "\n";
    cout << "Очікування 5 секунд... натисніть Enter, якщо пацієнт присутній.\n" << flush;

    auto inputFuture = async(launch::async, []() {
        string s;
        getline(cin, s);
        return s;
        });

    if (inputFuture.wait_for(chrono::seconds(5)) == future_status::ready) {
        treated.push_back(p);
    }
    else {
        cout << "Час вийшов, наступний пацієнт.\n";
        untreated.push_back(p);
    }
}

void processPatients(vector<Doctor>& doctors,
    vector<Patient>& treated,
    vector<Patient>& untreated)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto& doc : doctors) {
        cout << "\nЧерга до " << doc.toString() << ":\n";
        while (!doc.q.empty()) {
            Patient p = doc.q.front();
            processPatient(p, doc.toString(), treated, untreated);
            doc.q.pop();
        }
    }
}

void saveResults(const vector<Patient>& treated,
    const vector<Patient>& untreated)
{
    ofstream f1("treated.txt");
    ofstream f2("untreated.txt");
    for (auto& p : treated)   f1 << p.toString() << "\n";
    for (auto& p : untreated) f2 << p.toString() << "\n";
    cout << "Результати збережено.\n";
}