#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>
using namespace std;

struct Customer {
    string name; // nome do cliente
    int money; // dinheiro oferecido
    int duration; // duração da viagem em dias
    int arrival_time; // dia em que o cliente fez o pedido

    // Comparator for priority queue: higher money first, then earlier arrival
    bool operator<(const Customer& other) const {
        if (money == other.money) // Se o dinheiro for igual
            return arrival_time > other.arrival_time; // Earlier requests first
        return money < other.money; // Max-heap for money
    }
};

int main() {
    int S, N;
    cin >> S >> N;

    priority_queue<Customer> pq; // Priority queue to manage customer requests
    vector<tuple<string, int, int>> results; // Stores results (name, money, waiting_time)
    queue<Customer> waiting_customers; // Queue to track customers who haven't arrived yet

    for (int i = 0; i < N; i++) {
        Customer c;
        cin >> c.name >> c.money >> c.duration >> c.arrival_time;
        waiting_customers.push(c);
    }

    int current_day = S; // Start of operation

    while (!waiting_customers.empty() || !pq.empty()) {
        // Add customers to the priority queue whose arrival_time <= current_day
        while (!waiting_customers.empty() && waiting_customers.front().arrival_time <= current_day) {
            pq.push(waiting_customers.front());
            waiting_customers.pop();
        }

        if (!pq.empty()) {
            // Serve the highest-priority customer
            Customer top = pq.top();
            pq.pop();

            int waiting_time = current_day - top.arrival_time;
            results.emplace_back(top.name, top.money, waiting_time);

            // Update the current day after serving the customer
            current_day += top.duration;
        } else {
            // If no customers are ready, move current_day to the arrival_time of the next customer
            current_day = waiting_customers.front().arrival_time;
        }
    }

    // Sort results: descending by money, then by arrival_time
    sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        if (get<1>(a) == get<1>(b)) // If money is the same
            return get<2>(a) < get<2>(b); // Sort by waiting_time (earlier is first)
        return get<1>(a) > get<1>(b); // Sort by money descending
    });

    // Output results
    for (const auto& res : results) {
        cout << get<0>(res) << " " << get<1>(res) << " " << get<2>(res) << endl;
    }

    return 0;
}
