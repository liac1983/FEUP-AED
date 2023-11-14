#ifndef PATIENT_H
#define PATIENT_H

class Patient {
public:
    Patient(int id, int n=0, int lcy=1900);
    int getID() const;
    int getNumConsultations() const;
    int getLastConsultationYear() const;
    bool operator<(const Patient &p2) const;

    int numConsultations;
    int lastConsultationYear;
    // Default constructor
    Patient() : idPatient(0), numConsultations(0), lastConsultationYear(0) {}

    int idPatient;
};

#endif
