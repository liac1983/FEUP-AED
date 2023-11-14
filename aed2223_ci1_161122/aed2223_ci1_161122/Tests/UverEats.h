#ifndef AED2223_CI1_UVEREATS_H
#define AED2223_CI1_UVEREATS_H

#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include "Driver.h"
#include "Restaurant.h"
#include "Client.h"

using namespace std;

class UverEats {
    set <Driver> drivers;
    list <Restaurant> restaurants;
    vector<Client> clients;
public:
    UverEats();
    void addClient(Client client);
    void addRestaurant(Restaurant restaurant);
    void addDriver(Driver driver);
    const set<Driver> &getDrivers() const;
    vector<Client> getClients() const;
    const list<Restaurant> &getRestaurants() const;
    //TODO:
    void sortClients();
    float averageRestaurantRating(int numMinOrders) const;
    void removeRestaurants(float minRating);
    vector<Driver> getDriversWithOrders(int numOrders) const;
    void createRestaurantBranch(string restMain, string restBranch);
};


#endif //AED2223_CI1_UVEREATS_H
