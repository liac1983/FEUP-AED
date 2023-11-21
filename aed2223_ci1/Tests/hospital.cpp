#include "hospital.h"

Hospital::Hospital() { }

void Hospital::addDoctor(const Doctor& d) {
	doctors.push_back(d);
}

void Hospital::addPatient(const Patient& p) {
    patients.push_back(p);
}

void Hospital::addOldPatient(const Patient& p) {
    oldPatients.insert(p);
}

void Hospital::addStackConsultations(const stack<Consultation>& s) {
    consultations.push_back(s);
}

vector<Doctor> Hospital::getDoctors() const {
	return doctors;
}

list<Patient> Hospital::getPatients() const {
    return patients;
}

set<Patient> Hospital::getOldPatients() const {
    return oldPatients;
}

list<stack<Consultation>> Hospital::getConsultations() const {
    return consultations;
}

void Hospital::setConsultations(const list<stack<Consultation>>& consults) {
    consultations = consults;
}


// --------------------------------------------------------------------

//TODO
void Hospital::sortDoctors() {
    // Definindo um comparador personalizado
    auto comparator = [](const Doctor& a, const Doctor& b) {
        // Ordenando por ordem decrescente de ocupação (número de doentes)
        if (a.toAttend.size() != b.toAttend.size()) {
            return a.toAttend.size() > b.toAttend.size();
        }
        // Em caso de igualdade, ordenando por ordem crescente de id
        return a.idDoctor < b.idDoctor;
    };

    // Ordenando a lista de médicos usando o comparador
    std::sort(doctors.begin(), doctors.end(), comparator);
}


// TODO
float Hospital::averageNPatients(string sp) const {
    return 0.0;
}


// TODO
int Hospital::removePatients(int minC) {
    return 0;
}


// TODO
vector<Patient> Hospital::getOldPatients(int y) const {
    vector<Patient> res;
    return res;
}


// TODO
void Hospital::processConsultation(Consultation c) {

}


// TODO
bool Hospital::addDoctor(int id2, string sp2, int id1) {
    return true;
}
