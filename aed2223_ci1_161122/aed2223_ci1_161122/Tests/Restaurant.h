#ifndef AED2223_CI1_RESTAURANT_H
#define AED2223_CI1_RESTAURANT_H

#include <string>
#include <queue>
#include "Order.h"

using namespace std;

class Restaurant {
    string name;
    float rating;
    queue<Order *> orders;
public:
    Restaurant() {rating = 0.0; }
    Restaurant(string name): name(name) {rating = 0.0; }
    Restaurant(string name, float rating): name(name), rating(rating) {}
    const string &getName() const;
    float getRating() const;
    const queue<Order *> &getOrders() const;
    void insertOrder(Order* order);
    void removeFrontOrder();

    //TODO
    void removeOrder(string client, string orderNumber );
};

#endif //AED2223_CI1_RESTAURANT_H
