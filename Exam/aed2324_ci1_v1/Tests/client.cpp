#include "client.h"

Client::Client(string nm, string zp, unsigned n): name(nm), zipCode(zp), numOrders(n)
{ }

string Client::getName() const {
    return name;
}

string Client::getZipCode() const {
    return zipCode;
}

unsigned Client::getNumOrders() const {
    return numOrders;
}


void Client::setNumOrders(unsigned n) {
    numOrders = n;
}

void Client::incNumOrders() {
    numOrders++;
}


// --------------------------------------------

//TODO
bool Client::operator<(const Client& other) const {
    if (zipCode != other.zipCode) {
        return zipCode < other.zipCode;
    }
    return name < other.name;
}
