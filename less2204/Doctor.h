#pragma once
#include <queue>
#include <string>
#include "Patient.h"

struct Doctor {
    std::string surname;
    std::string name;
    std::string specialization;
    std::queue<Patient> q;

    std::string toString() const {
        return specialization + " — " + surname + " " + name;
    }
};