#pragma once
#include <vector>
#include "Doctor.h"
#include "Patient.h"

void listDoctors(const std::vector<Doctor>& doctors);
void showQueues(const std::vector<Doctor>& doctors);
void addPatient(std::vector<Doctor>& doctors, int& patientCounter);
void processPatients(std::vector<Doctor>& doctors,
    std::vector<Patient>& treated,
    std::vector<Patient>& untreated);
void saveResults(const std::vector<Patient>& treated,
    const std::vector<Patient>& untreated);
void processPatient(const Patient& p, const std::string& doctor,
    std::vector<Patient>& treated,
    std::vector<Patient>& untreated);