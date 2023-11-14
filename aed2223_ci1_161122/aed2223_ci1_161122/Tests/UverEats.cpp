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
    // Custom comparison function to sort clients by seniority and then by name
    auto compareClients = [](const Client& client1, const Client& client2) {
        if (client1.getSeniority() > client2.getSeniority()) {
            return true;
        } else if (client1.getSeniority() == client2.getSeniority()) {
            return client1.getName() < client2.getName();
        }
        return false;
    };

    // Sorting the clients vector using the custom comparison function
    std::sort(clients.begin(), clients.end(), compareClients);
}


//TODO
float UverEats::averageRestaurantRating(int numMinOrders) const {
    float totalRating = 0.0;
    int numRestaurantsAboveMinOrders = 0;

    for (const auto& restaurant : restaurants) {
        if (restaurant.getNumOrders() > numMinOrders) {
            totalRating += restaurant.getRating();
            numRestaurantsAboveMinOrders++;
        }
    }

    // Check if there are restaurants with orders above numMinOrders
    if (numRestaurantsAboveMinOrders > 0) {
        return totalRating / numRestaurantsAboveMinOrders;
    } else {
        // No restaurants with orders above numMinOrders
        return 0.0;
    }
}


//TODO
void UverEats::removeRestaurants(float minRating) {
    // Temporary list to hold restaurants that meet the criteria
    list<Restaurant> tempRestaurants;

    // Iterate through the restaurants in the original list
    for (const auto& restaurant : restaurants) {
        // Check if the restaurant's rating is above or equal to minRating
        if (restaurant.getRating() >= minRating) {
            //Restaurant meets the criteria, add it to the temporary list
            tempRestaurants.push_back(restaurant);
        }
        // Otherwise, skip the restaurant
    }

    // Update the original list with the filtered restaurants
    restaurants = tempRestaurants;
}


//TODO
vector<Driver> UverEats::getDriversWithOrders(int numOrders) const {
    // Temporary vector to hold drivers that meet the criteria
    vector<Driver> result;

    // Custom comparison function for sorting drivers
    auto copareDrivers = [](const Driver& d1, const Driver& d2) {
        if (d1.getToDelivery().size() == d2.getToDeliver().size()) {
            return d1.getIdDriver() < d2.getIdDriver();
        }
        return d1.getToDeliver().size() > d2.getToDeliver().size();
    };

    //Iterate through the set of drivers
    for (const auto& driver : drivers) {
        // Cjeck if the driver has fewer than numOrders
        if(driver.getToDelivery().size() < numOrders) {
            // Add the driver to the temporary vector
            result.push_back(driver);
        }
    }

    // Sort the vector using the custom comparison function
    sort(result.begin(), result.end(), compareDrivers);

    return result;
}


//TODO:
void UverEats::createRestaurantBranch(string restMain, string restBranch) {
     // Find the main restaurant by name
     auto mainRestaurant = std::find_if(
             restaurant.begin(), restaurants.end(),
             [restMain](const Restaurant& restaurant) {
                 return restaurant.getName() == restMain;
             }
             );

     // Check is the main restaurant exists
     if (mainRestaurant !=  restaurants.end()) {
        // Create a new restaurant branch
        Restaurant branch(restBranch);

        // Transfer orders from the main restaurant to the branch
        auto& mainOrders = mainRestaurant->getOrders();
        int orderIndex = 1; // Start from the 2nd position (1-based index)

        while (!mainOrders.empty()) {
            // Trasfer orders from even positions to the branch
            if (orderIndex % 2 == 0) {
                branch.insertOrder(mainOrders.front());
                mainOrders.pop();
            }
            else  {
                mainOrders.pop(); // Skip orders at odd posions
            }
            orderIndex++;
        }

        // Add the new restaurant branch to the end of the list
        restaurants.push_back(branch);
     }
}