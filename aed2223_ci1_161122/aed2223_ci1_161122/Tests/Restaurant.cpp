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
    // Temporary queue to hold orders taht do not match the criteria
    queue<Order *> tempQueue;

    // Iterate through the orders in the queue
    while (!orders.empty()) {
        // Get the front order
        Order *currentOrder = orders.front();

        // Check if the order matches the specified client and order number
        if (currentOrder->getClient() == client && currentOrder->getOrderNumber() == orderNumber) {
            // Found the order to be removed, free the memory and move to the next order
            delete currentOrder;
            orders.pop();
        } else {
            // Order doesn't match the criteria, move it to the temporary queue
            tempQueue.push(currentOrder);
            orders.pop();
        }
    }

    // Restore the orders in the original queue, excluding the removed order
    orders = tempQueue;
}
