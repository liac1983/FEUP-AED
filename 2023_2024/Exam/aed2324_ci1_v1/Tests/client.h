#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
using namespace std;

class Client {
    string name;
    string zipCode;
    unsigned numOrders;
public:
    Client(string nm, string zc, unsigned n=0);
    string getName() const;
    string getZipCode() const;
    unsigned getNumOrders() const;
    void incNumOrders();
    void setNumOrders(unsigned n);
    bool operator < (const Client& c) const;
    bool operator==(const Client& other) const {
        return name == other.name && zipCode == other.zipCode;
    }
};



#endif
