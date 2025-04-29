#include <iostream>
#include <vector>
#include <limits>
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
        {"Ковальчук", "Наталія", "Дерматолог"},
        {"Мельник", "Петро", "Хірург"},
        {"Кравчук", "Лариса", "Кардіолог"},
        {"Бондаренко", "Сергій", "Педіатр"},
        {"Дьяків", "Олександр", "Невролог"},
        {"Гриценко", "Тимофій", "Терапевт"},
        {"Тимошенко", "Ірина", "Стоматолог"},
        {"Петрова", "Вікторія", "Дерматолог"},
        {"Чорномаз", "Ігор", "Хірург"},
        {"Леонова", "Алла", "Кардіолог"},
        {"Скороход", "Володимир", "Педіатр"},
        {"Власенко", "Світлана", "Невролог"}
    };

    vector<Patient> treated;
    vector<Patient> untreated;
    int patientCounter = 1;

    while (true) {
        cout << "\n=== МЕНЮ ===\n"
            << "1. Додати пацієнта\n"
            << "2. Опрацювати черги\n"
            << "3. Показати черги\n"
            << "4. Показати лікарів за спеціалізацією\n"
            << "5. Вийти\n"
            << "Ваш вибір: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "Помилка!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
            listDoctors(doctors);  // функція спеціалізацій була оголошена, але не реалізована
        }
        else if (choice == 5) {
            cout << "До побачення!\n";
            break;
        }
        else {
            cout << "Невірний вибір. Введіть число від 1 до 5.\n";
        }
    }

    return 0;
}
