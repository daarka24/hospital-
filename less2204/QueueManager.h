#pragma once
#include <vector>
#include "Doctor.h"
#include "Patient.h"

void listDoctors(const vector<Doctor>& doctors);
void showQueues(const vector<Doctor>& doctors);
void addPatient(vector<Doctor>& doctors, int& patientCounter);
void processPatients(vector<Doctor>& doctors, vector<Patient>& treated, vector<Patient>& untreated);
void saveResults(const vector<Patient>& treated, const vector<Patient>& untreated);
void listDoctorsBySpecialization(const vector<Doctor>& doctors);
void processPatient(Patient& p, const string& doctor, vector<Patient>& treated, vector<Patient>& untreated);
