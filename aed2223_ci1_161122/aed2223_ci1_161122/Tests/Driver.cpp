#include "Driver.h"

Driver::Driver(unsigned int idDriver, const string &nameDriver) : driverId(idDriver), driverName(nameDriver) {}

unsigned int Driver::getIdDriver() const {
    return driverId;
}

const string &Driver::getNameDriver() const {
    return driverName;
}

const stack<Order> &Driver::getToDeliver() const {
    return toDeliver;
}

void Driver::insertOrder(Order order) {
    toDeliver.push(order);
}

//=============================================================================

// TODO
bool Driver::operator<(const Driver &d1) const {
    return true;
}

// TODO
vector<string> Driver::checkCommonClients(const Driver &d2) {
    vector<string> result;
    return result;
}

