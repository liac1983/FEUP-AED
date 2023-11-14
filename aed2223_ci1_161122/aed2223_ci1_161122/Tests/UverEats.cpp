#include "UverEats.h"

UverEats::UverEats() {}

void UverEats::addClient(Client client){
    clients.push_back(client);
}

void UverEats::addRestaurant(Restaurant restaurant) {
    restaurants.push_back(restaurant);
}

vector<Client> UverEats::getClients() const {
    return clients;
}

const list<Restaurant> &UverEats::getRestaurants() const {
    return restaurants;
}

void UverEats::addDriver(Driver driver) {
    drivers.insert(driver);
}

const set<Driver> &UverEats::getDrivers() const {
    return drivers;
}

//=============================================================================

//TODO
void UverEats::sortClients() {

}


//TODO
float UverEats::averageRestaurantRating(int numMinOrders) const {
    float average = 0.0;
    return average;
}


//TODO
void UverEats::removeRestaurants(float minRating) {

}


//TODO
vector<Driver> UverEats::getDriversWithOrders(int numOrders) const {
    vector<Driver> result;
    return result;
}


//TODO:
void UverEats::createRestaurantBranch(string restMain, string restBranch) {

}