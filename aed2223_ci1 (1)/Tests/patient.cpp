#include "patient.h"

Patient::Patient(int id, int n, int lcy): idPatient(id), numConsultations(n), lastConsultationYear(lcy)
{}

int Patient::getID() const {
    return idPatient;
}

int Patient::getNumConsultations() const {
    return numConsultations;
}

int Patient::getLastConsultationYear() const {
    return lastConsultationYear;
}

// --------------------------------------------------------------------

//TODO
bool Patient::operator<(const Patient &p2) const {
    if (lastConsultationYear != p2.lastConsultationYear) {
        return lastConsultationYear < p2.lastConsultationYear;
    }
    return idPatient < p2.idPatient;
}