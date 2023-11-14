#include "Restaurant.h"

void Restaurant::insertOrder(Order* order) {
    orders.push(order);
}

void Restaurant::removeFrontOrder() {
    orders.pop();
}

const string &Restaurant::getName() const {
    return name;
}

float Restaurant::getRating() const {
    return rating;
}

const queue<Order *> &Restaurant::getOrders() const {
    return orders;
}


//=============================================================================

//TODO
void Restaurant::removeOrder(string client, string orderNumber) {

}
