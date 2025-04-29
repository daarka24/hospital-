#pragma once
#include <string>
#include <queue>
#include <iostream>
#include "Patient.h"

using namespace std;

class Doctor {
public:
    string name;
    string surname;
    string specialization;
    queue<Patient> q;

    Doctor(string s, string n, string sp)
        : surname(s), name(n), specialization(sp) {
    }

    void addPatient(const Patient& p) {
        q.push(p);
    }

    int getQueueSize() const {
        return q.size();
    }
};