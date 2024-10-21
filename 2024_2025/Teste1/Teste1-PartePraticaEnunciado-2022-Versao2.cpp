#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <algorithm>

using namespace std;

// Forward declarations
class Patient;
class Doctor;
class Consultation;
class Hospital;

// Class Patient
class Patient {
    int idPatient;
    int numConsultations;
    int lastConsultationYear;

public:
    Patient(int id, int numConsultations, int lastYear)
        : idPatient(id), numConsultations(numConsultations), lastConsultationYear(lastYear) {}

    int getId() const { return idPatient; }
    int getNumConsultations() const { return numConsultations; }
    int getLastConsultationYear() const { return lastConsultationYear; }

    // Overload the comparison operators to organize oldPatients set
    bool operator<(const Patient &p) const {
        if (lastConsultationYear == p.lastConsultationYear)
            return idPatient < p.idPatient;
        return lastConsultationYear < p.lastConsultationYear;
    }
};

// Class Doctor
class Doctor {
    int idDoctor;
    string specialty;
    queue<Patient> toAttend;

public:
    Doctor(int id, string spec) : idDoctor(id), specialty(spec) {}

    int getId() const { return idDoctor; }
    string getSpecialty() const { return specialty; }
    queue<Patient> &getToAttendQueue() { return toAttend; }

    int getNumberOfPatients() const { return toAttend.size(); }

    // d) Move a patient with urgent need to the front of the queue
    void moveToFront(int idP) {
        queue<Patient> newQueue;
        Patient urgentPatient(0, 0, 0);
        bool found = false;

        while (!toAttend.empty()) {
            Patient current = toAttend.front();
            toAttend.pop();
            if (current.getId() == idP) {
                urgentPatient = current;
                found = true;
            } else {
                newQueue.push(current);
            }
        }

        if (found) {
            toAttend = newQueue;
            toAttend.push(urgentPatient);
        }
    }
};

// Class Consultation
class Consultation {
    int idPatient;
    string specialty;
    string description;

public:
    Consultation(int id, const string &spec, const string &desc)
        : idPatient(id), specialty(spec), description(desc) {}

    string getSpecialty() const { return specialty; }
};

// Class Hospital
class Hospital {
    vector<Doctor> doctors;
    list<Patient> patients;
    set<Patient> oldPatients;
    list<stack<Consultation>> consultations;

public:
    // a) Sort doctors by number of patients in descending order, and by id in ascending order if tied
    void sortDoctors() {
        sort(doctors.begin(), doctors.end(), [](const Doctor &d1, const Doctor &d2) {
            if (d1.getNumberOfPatients() == d2.getNumberOfPatients())
                return d1.getId() < d2.getId();
            return d1.getNumberOfPatients() > d2.getNumberOfPatients();
        });
    }

    // b) Calculate the average number of patients waiting for doctors of a specific specialty
    float averageNPatients(string sp) const {
        int totalPatients = 0;
        int doctorCount = 0;

        for (const auto &doctor : doctors) {
            if (doctor.getSpecialty() == sp) {
                totalPatients += doctor.getNumberOfPatients();
                doctorCount++;
            }
        }

        if (doctorCount == 0) return 0.0;
        return static_cast<float>(totalPatients) / doctorCount;
    }

    // c) Remove patients with fewer than minC consultations and return the number removed
    int removePatients(int minC) {
        int removedCount = 0;
        patients.remove_if([minC, &removedCount](const Patient &p) {
            if (p.getNumConsultations() < minC) {
                removedCount++;
                return true;
            }
            return false;
        });
        return removedCount;
    }

    // e) Get old patients with last consultation before year y
    vector<Patient> getOldPatients(int y) const {
        vector<Patient> result;

        for (const auto &patient : oldPatients) {
            if (patient.getLastConsultationYear() < y) {
                result.push_back(patient);
            }
        }

        return result;
    }

    // f) Process consultation and add it to the appropriate stack
    void processConsultation(Consultation c) {
        for (auto &consultationStack : consultations) {
            if (!consultationStack.empty() && consultationStack.top().getSpecialty() == c.getSpecialty()) {
                consultationStack.push(c);
                return;
            }
        }

        // If no stack exists for this specialty, create a new one
        stack<Consultation> newStack;
        newStack.push(c);
        consultations.push_back(newStack);
    }

    // g) Add a doctor and transfer some patients from an existing doctor
    bool addDoctor(int id2, string sp2, int id1) {
        Doctor *existingDoctor = nullptr;

        // Find the doctor with id1
        for (auto &doctor : doctors) {
            if (doctor.getId() == id1) {
                existingDoctor = &doctor;
                break;
            }
        }

        // If doctor id1 not found or specialties do not match
        if (!existingDoctor || existingDoctor->getSpecialty() != sp2) {
            doctors.push_back(Doctor(id2, sp2)); // Add new doctor with no patients
            return false;
        }

        // Add the new doctor
        Doctor newDoctor(id2, sp2);
        queue<Patient> &existingQueue = existingDoctor->getToAttendQueue();
        queue<Patient> newQueue;

        int position = 0;
        while (!existingQueue.empty()) {
            Patient currentPatient = existingQueue.front();
            existingQueue.pop();

            if (position % 2 == 1) {
                newDoctor.getToAttendQueue().push(currentPatient); // Transfer even-positioned patients
            } else {
                newQueue.push(currentPatient);
            }
            position++;
        }

        // Update the queue of the existing doctor and add the new doctor
        existingDoctor->getToAttendQueue() = newQueue;
        doctors.push_back(newDoctor);
        return true;
    }
};
