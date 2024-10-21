#include <iostream>
#include <string>
#include <set>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

// Forward declaration of classes
class Driver;
class Restaurant;
class Client;
class Order;
class UverEats;

// Class Client
class Client {
    string name;
    int seniority;
public:
    Client(const string &name, int seniority) : name(name), seniority(seniority) {}

    string getName() const { return name; }
    int getSeniority() const { return seniority; }

    // Overload the < operator to sort by seniority (descending) and name (alphabetically)
    bool operator<(const Client &c) const {
        if (seniority == c.seniority) {
            return name < c.name;
        }
        return seniority > c.seniority;
    }
};

// Class Order
class Order {
    string orderNumber;
    string client;
    string restaurant;
public:
    Order(const string &orderNumber, const string &client, const string &restaurant)
        : orderNumber(orderNumber), client(client), restaurant(restaurant) {}

    string getClient() const { return client; }
    string getOrderNumber() const { return orderNumber; }
};

// Class Restaurant
class Restaurant {
    string name;
    float rating;
    queue<Order *> orders;

public:
    Restaurant(const string &name, float rating) : name(name), rating(rating) {}

    string getName() const { return name; }
    float getRating() const { return rating; }
    queue<Order *> &getOrders() { return orders; }

    // Remove order by client and order number
    void removeOrder(string client, string orderNumber) {
        queue<Order *> newQueue;
        while (!orders.empty()) {
            Order *currentOrder = orders.front();
            orders.pop();
            if (!(currentOrder->getClient() == client && currentOrder->getOrderNumber() == orderNumber)) {
                newQueue.push(currentOrder);
            } else {
                delete currentOrder; // Remove the order
            }
        }
        orders = newQueue; // Update the orders queue
    }
};

// Class Driver
class Driver {
    unsigned driverId;
    string driverName;
    stack<Order> toDeliver;

public:
    Driver(unsigned id, const string &name) : driverId(id), driverName(name) {}

    string getName() const { return driverName; }
    unsigned getId() const { return driverId; }
    int getNumberOfOrders() const { return toDeliver.size(); }
    stack<Order> &getToDeliver() { return toDeliver; }

    // Overload operator < to sort by number of orders (descending), then by ID (ascending)
    bool operator<(const Driver &d1) const {
        if (toDeliver.size() == d1.toDeliver.size()) {
            return driverId < d1.driverId;
        }
        return toDeliver.size() > d1.toDeliver.size();
    }

    // Find common clients between two drivers
    vector<string> checkCommonClients(const Driver &d2) {
        set<string> clients1, commonClients;
        stack<Order> temp = toDeliver;

        // Get all clients from this driver's orders
        while (!temp.empty()) {
            clients1.insert(temp.top().getClient());
            temp.pop();
        }

        // Check for common clients in d2's orders
        temp = d2.toDeliver;
        while (!temp.empty()) {
            if (clients1.find(temp.top().getClient()) != clients1.end()) {
                commonClients.insert(temp.top().getClient());
            }
            temp.pop();
        }

        return vector<string>(commonClients.begin(), commonClients.end());
    }
};

// Class UverEats
class UverEats {
    set<Driver> drivers;
    list<Restaurant> restaurants;
    vector<Client> clients;

public:
    // a) Sort clients by seniority and name
    void sortClients() {
        sort(clients.begin(), clients.end());
    }

    // b) Calculate average rating of restaurants with more than numMinOrders
    /* float averageRestaurantRating(int numMinOrders) const {
        float totalRating = 0;
        int count = 0;

        for (const auto &restaurant : restaurants) {
            if (restaurant.getOrders().size() > numMinOrders) {
                totalRating += restaurant.getRating();
                count++;
            }
        }

        if (count == 0) return 0.0;
        return totalRating / count;
    } */

    // c) Remove orders by client and order number in a specific restaurant
    void removeOrderFromRestaurant(const string &restaurantName, const string &client, const string &orderNumber) {
        for (auto &restaurant : restaurants) {
            if (restaurant.getName() == restaurantName) {
                restaurant.removeOrder(client, orderNumber);
                break;
            }
        }
    }

    // d) Remove restaurants below the minimum rating
    void removeRestaurants(float minRating) {
        restaurants.remove_if([minRating](const Restaurant &r) {
            return r.getRating() < minRating;
        });
    }

    // e) Find common clients between two drivers
   /*  vector<string> checkCommonClients(unsigned d1, unsigned d2) {
        const Driver *driver1 = nullptr;
        const Driver *driver2 = nullptr;

        for (const auto &driver : drivers) {
            if (driver.getId() == d1) driver1 = &driver;
            if (driver.getId() == d2) driver2 = &driver;
        }

        if (driver1 && driver2) {
            return driver1->checkCommonClients(*driver2);
        }

        return {}; // Return empty if either driver is not found
    } */

    // f) Get drivers with less than a specific number of orders
    vector<Driver> getDriversWithOrders(int numOrders) const {
        vector<Driver> result;

        for (const auto &driver : drivers) {
            if (driver.getNumberOfOrders() < numOrders) {
                result.push_back(driver);
            }
        }

        // Sort the result by number of orders (descending) and driver ID (ascending)
        sort(result.begin(), result.end(), [](const Driver &a, const Driver &b) {
            if (a.getNumberOfOrders() == b.getNumberOfOrders()) {
                return a.getId() < b.getId();
            }
            return a.getNumberOfOrders() > b.getNumberOfOrders();
        });

        return result;
    }

    // g) Create a restaurant branch and move orders from the main restaurant
    void createRestaurantBranch(string restMain, string restBranch) {
        auto mainIt = find_if(restaurants.begin(), restaurants.end(), [&restMain](const Restaurant &r) {
            return r.getName() == restMain;
        });

        if (mainIt == restaurants.end()) return; // Main restaurant not found

        // Create the new branch
        Restaurant newBranch(restBranch, mainIt->getRating());

        // Move even-positioned orders (2nd, 4th, etc.)
        queue<Order *> &mainOrders = mainIt->getOrders();
        queue<Order *> newQueue;

        int count = 0;
        while (!mainOrders.empty()) {
            Order *currentOrder = mainOrders.front();
            mainOrders.pop();

            if (count % 2 == 1) {
                newBranch.getOrders().push(currentOrder);
            } else {
                newQueue.push(currentOrder);
            }
            count++;
        }

        // Update the main restaurant's order queue
        mainIt->getOrders() = newQueue;

        // Add the new branch to the list of restaurants
        restaurants.push_back(newBranch);
    }
};

