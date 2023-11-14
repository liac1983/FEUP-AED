#ifndef AED2223_CI1_DRIVER_H
#define AED2223_CI1_DRIVER_H

#include <string>
#include <vector>
#include <stack>
#include "Order.h"

using namespace std;

class Driver {
    unsigned driverId;
    string driverName;
    stack<Order> toDeliver;
public:\
    Driver();
    Driver(unsigned int idDriver, const string &nameDriver);
    unsigned int getIdDriver() const;
    const string &getNameDriver() const;
    const stack<Order> &getToDeliver() const;
    void insertOrder(Order order);

    //TODO
    vector<string> checkCommonClients(const Driver &d2);
    bool operator<(const Driver &d1) const;
};


#endif //AED2223_CI1_DRIVER_H
