#ifndef ORDER_H_
#define ORDER_H_

#include <string>
using namespace std;

class Order {
    unsigned id;
    string zipCode;
public:
    Order(unsigned i, string zc);
    unsigned getId () const;
    string getZipCode () const;
};

#endif
