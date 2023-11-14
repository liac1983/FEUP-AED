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
    // Filtrar os médicos pela especialidade
    auto doctorsOfSpeciality = std::count_if(doctors.begin(), doctors.end(),
                                             [&sp](const Doctor& doctor) { return doctor.specialty == sp; });

    if (doctorsOfSpeciality == 0) {
        // Não há médicos com a especialidade especificada
        return 0.0;
    }

    // Calcular a média do número de pacientes em espera
    auto totalPatients = std::accumulate(doctors.begin(), doctors.end(), 0,
                                         [&sp](int sum, const Doctor& doctor) {
                                             return (doctor.specialty == sp) ? sum + doctor.toAttend.size() : sum;
                                         });

    return static_cast<float>(totalPatients) / static_cast<float>(doctorsOfSpeciality);
}


// TODO
int Hospital::removePatients(int minC) {
    int removedPatients = 0;

    // Utilizando um iterador para percorrer a lista de pacientes
    auto it = patients.begin();
    while (it != patients.end()) {
        // Verificar se o paciente atende ao critério de remoção
        if (it->numConsultations < minC) {
            // Remover o paciente e atualizar o iterador
            it = patients.erase(it);
            removedPatients++;
        } else {
            // Avançar para o próximo paciente
            ++it;
        }
    }

    return removedPatients;
}


// TODO
vector<Patient> Hospital::getOldPatients(int y) const {
    vector<Patient> res;
    return res;
}


// TODO
void Hospital::processConsultation(Consultation c) {
    // Encontrar a especialidade médica da consulta
    string specialty = c.getSpecialty();

    // Procurar a pilha correspondente à especialidade
    auto it = find_if(consultations.begin(), consultations.end(),
                      [&specialty](const stack<Consultation>& s) {
                          return !s.empty() && s.top().getSpecialty() == specialty;
                      });

    if (it != consultations.end()) {
        // Se a pilha já existe, adicionar a consulta à pilha existente
        it->push(c);
    } else {
        // Se a pilha não existe, criar uma nova pilha e adicioná-la à lista
        stack<Consultation> newStack;
        newStack.push(c);
        consultations.push_back(newStack);
    }
}


// TODO
bool Hospital::addDoctor(int id2, string sp2, int id1) {
    return true;
}
