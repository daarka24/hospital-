// main.cpp
#include <iostream>
#include <vector>
#include "QueueManager.h"
#include "Doctor.h"
#include "Patient.h"

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    vector<Doctor> doctors = {
        {"Іваненко", "Марія", "Терапевт"},
        {"Шевченко", "Олег", "Стоматолог"},
        {"Ковальчук", "Наталія", "Дерматолог"}
    };

    vector<Patient> treated;
    vector<Patient> untreated;
    int patientCounter = 1;

    while (true) {
        cout << "\n=== МЕНЮ ===\n"
            << "1. Додати пацієнта\n"
            << "2. Опрацювати черги\n"
            << "3. Показати черги\n"
            << "4. Вийти\n"
            << "Ваш вибір: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "Помилка: введіть число від 1 до 4.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(10000, '\n');  // Очистка буфера після вибору

        if (choice == 1) {
            addPatient(doctors, patientCounter);
        }
        else if (choice == 2) {
            processPatients(doctors, treated, untreated);
            saveResults(treated, untreated);
        }
        else if (choice == 3) {
            showQueues(doctors);
        }
        else if (choice == 4) {
            cout << "До побачення!\n";
            break;
        }
        else {
            cout << "Невірний вибір. Введіть число від 1 до 4.\n";
        }
    }

    return 0;
}
