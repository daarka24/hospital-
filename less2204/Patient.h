#pragma once
#include <string>
#include <random>

using namespace std;

struct Patient {
    string name;
    int age;
    string disease;
    int id;

    Patient(string name = "", int age = 0, string disease = "")
        : name(name), age(age), disease(disease) {
        id = generateRandomID();
    }

    int generateRandomID() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1000, 9999);
        return dis(gen);
    }
};