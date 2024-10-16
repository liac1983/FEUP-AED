#ifndef DOCTOR_H_
#define DOCTOR_H_

#include <string>
#include <queue>
#include "patient.h"
using namespace std;

class Doctor {
    string specialty;
public:
  Doctor(int id, string sp);
  int getID() const;
  string getSpecialty() const;
  queue<Patient> getPatientsToAttend() const;
  void setSpecialty(string sp);
  void setPatientsToAttend(queue<Patient> toAtt);
  void addPatientToAttend(const Patient& p1);
  void moveToFront(int idP);

    int idDoctor;
    queue<Patient> toAttend;
};

#endif
