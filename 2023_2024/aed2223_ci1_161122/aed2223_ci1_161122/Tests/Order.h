#ifndef AED2223_CI1_ORDER_H
#define AED2223_CI1_ORDER_H

#include <string>

using namespace std;

class Order {
    string orderNumber;
    string client;
    string restaurant;
public:
    Order(const string &orderNumber, const string &client) : orderNumber(orderNumber), client(client) {}
    const string &getOrderNumber() const;
    const string &getClient() const;
};


#endif //AED2223_CI1_ORDER_H
