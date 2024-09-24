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
    return driverId < d1.driverId;
}

// TODO
vector<string> Driver::checkCommonClients(const Driver &d2) {
    vector<string> commonClients;

    // Temporary stacks to store orders and preserve the original order
    stack<Order> tempToDeliver1 = toDeliver;
    stack<Order> tempToDeliver2 = d2.toDeliver;

    // set to keep track of unique client names
    set<string> uniqueClients;

    // Iterate through the forst driver's orders
    while (!tempToDeliver1.empty()) {
        uniqueClients.insert(tempToDeliver1.top().getClient());
        tempToDeliver1.pop();
    }

    //Iterate through the second driver's orders
    while (!tempToDeliver2.empty()) {
        // Check if the client is common between the two drivers
        if(uniqueClients.find(tempToDeliver2.top().getClinet()) != uniqueClients.end()) {
            commonClinets.push_back(tempToDeliver2.top().getClinet());
        }
        tempToDelivery2.pop();
    }
    return commonClients;
}

