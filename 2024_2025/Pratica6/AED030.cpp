#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct Customer {
    string name;
    int arrival;
    int products;
    int start_time;
    int departure_time;
};

struct Checkout {
    int id;
    int speed;
    queue<Customer> customer_queue;  // Renamed from 'queue' to 'customer_queue'
    int last_departure_time;
    
    Checkout(int i, int s) : id(i), speed(s), last_departure_time(0) {}
};

bool compareCheckouts(const Checkout* a, const Checkout* b, int products) {
    if (a->customer_queue.size() != b->customer_queue.size()) 
        return a->customer_queue.size() < b->customer_queue.size();
    if (!a->customer_queue.empty() && !b->customer_queue.empty()) {
        int last_a_products = a->customer_queue.back().products;
        int last_b_products = b->customer_queue.back().products;
        if (last_a_products != last_b_products)
            return last_a_products < last_b_products;
    }
    return a->id < b->id;
}

int calculateServiceTime(int products, int speed) {
    return 10 + products * speed;
}

int main() {
    int C; // Number of checkouts
    cin >> C;
    
    vector<Checkout> checkouts;
    for (int i = 0; i < C; ++i) {
        int speed;
        cin >> speed;
        checkouts.emplace_back(i + 1, speed); // Checkout IDs are 1-based
    }
    
    int N; // Number of customers
    cin >> N;
    vector<Customer> customers(N);
    
    for (int i = 0; i < N; ++i) {
        cin >> customers[i].name >> customers[i].arrival >> customers[i].products;
    }

    for (Customer &customer : customers) {
        // Find the best checkout according to the problem's criteria
        Checkout* best_checkout = &checkouts[0];
        for (Checkout &checkout : checkouts) {
            if (compareCheckouts(&checkout, best_checkout, customer.products)) {
                best_checkout = &checkout;
            }
        }

        // Determine start time for this customer
        customer.start_time = max(customer.arrival, best_checkout->last_departure_time);

        // Calculate the departure time based on the cashier's speed
        int service_time = calculateServiceTime(customer.products, best_checkout->speed);
        customer.departure_time = customer.start_time + service_time;
        
        // Update the checkout's last departure time
        best_checkout->last_departure_time = customer.departure_time;
        
        // Add customer to the checkout queue
        best_checkout->customer_queue.push(customer);
    }

    // Output format
    for (const Checkout &checkout : checkouts) {
        cout << "Checkout #" << checkout.id << ": " << checkout.customer_queue.size() << endl;
        queue<Customer> q = checkout.customer_queue;
        while (!q.empty()) {
            const Customer &customer = q.front();
            cout << ". " << customer.name << " " << customer.arrival << " " << customer.start_time << " " << customer.departure_time << endl;
            q.pop();
        }
    }

    return 0;
}