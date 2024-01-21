#include "order.h"

Order::Order(unsigned i, string zc): id (i), zipCode(zc)
{ }

unsigned Order::getId() const {
    return id;
}

string Order::getZipCode() const {
    return zipCode;
}
