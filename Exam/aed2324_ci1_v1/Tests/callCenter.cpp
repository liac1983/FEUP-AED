#include "callCenter.h"

CallCenter::CallCenter()
{}

list<Agent> CallCenter::getAgents() const {
    return agents;
}

set<Client> CallCenter::getClients() const {
    return clients;
}

void CallCenter::addAgent(const Agent &a) {
    agents.push_back(a);
}

void CallCenter::addClient(const Client &c) {
        clients.insert(c);
}

void CallCenter::addOrderDelivered(const Order &o) {
    ordersDelivered.push_back(o);
}

vector<stack<Order> >CallCenter::getOrders() const {
    return orders;
}

vector<Order>CallCenter::getOrdersDelivered() const {
    return ordersDelivered;
}

void CallCenter::setOrders(vector<stack<Order> > stOrd1) {
    orders = stOrd1;
}

//---------------------------------------------------------------------

//TODO
void CallCenter::sortOrdersDelivered() {
    // Custom comparator function for sorting ordersDelivered
    auto orderComparator = [](const Order &a, const Order &b) {
        // First, compare by zip code in lexicographical order
        if (a.getZipCode() != b.getZipCode()) {
            return a.getZipCode() < b.getZipCode();
        }

        // If zip codes are the same, compare by customer identifier in descending order
        return a.getId() > b.getId();
    };

    // Use std::sort with the custom comparator to sort ordersDelivered
    std::sort(ordersDelivered.begin(), ordersDelivered.end(), orderComparator);
}



//TODO
list<string> CallCenter::removeAgentsNoCalls () {
    list <string> res;
    // Iterate through the list of agents
    for (auto it = agents.begin(); it != agents.end(); ) {
        // Check if the agent has no calls to process
        if (it->getWaitingCalls().empty()) {
            // Add the agent's name to the result list
            res.push_back(it->getName());

            // Remove the agent from the list
            it = agents.erase(it);
        } else {
            // Move to the next agent in the list
            ++it;
        }
    }
    return res;
}

//TODO
string CallCenter::putInLessBusyAgent(unsigned call1) {
    if (agents.empty()) {
        // No agents in the list
        return "noAgent";
    }

    // Find the agent with the least number of waiting calls
    auto lessBusyAgent = agents.begin();
    for (auto it = agents.begin(); it != agents.end(); ++it) {
        if (it->getWaitingCalls().size() < lessBusyAgent->getWaitingCalls().size()) {
            lessBusyAgent = it;
        }
    }

    // Add the call to the queue of the selected agent
    lessBusyAgent->addCall(call1);

    // Return the name of the selected agent
    return lessBusyAgent->getName();
}


//TODO
void CallCenter::updateClient(string name, string zc){
    // Create a temporary Client with the specified name and zip code
    Client tempClient(name, zc);

    // Check if the client already exists in the set
    auto it = clients.find(tempClient);

    if (it != clients.end()) {
        // Client found, update the number of orders
        const_cast<Client&>(*it).incNumOrders();  // Use const_cast to remove constness
    } else {
        // Client not found, add to the set with numOrders set to 1
        tempClient.setNumOrders(1);
        clients.insert(tempClient);
    }

    // Reorder the set based on the required criteria (zip code and name)
    clients = orderClientsSet(clients);
}

// Function to order the set of clients alphabetically by zip code and name
set<Client> CallCenter::orderClientsSet(const set<Client>& originalSet) const {
    // Create a vector from the original set for sorting
    vector<Client> tempVector(originalSet.begin(), originalSet.end());

    // Custom comparator function for sorting clients
    auto clientComparator = [](const Client& a, const Client& b) {
        // First, compare by zip code in lexicographical order
        if (a.getZipCode() != b.getZipCode()) {
            return a.getZipCode() < b.getZipCode();
        }

        // If zip codes are the same, compare by name in lexicographical order
        return a.getName() < b.getName();
    };

    // Use std::sort with the custom comparator to sort the vector
    std::sort(tempVector.begin(), tempVector.end(), clientComparator);

    // Convert the sorted vector back to a set
    set<Client> orderedSet(tempVector.begin(), tempVector.end());

    return orderedSet;
}


//TODO
void CallCenter::addAgent(string name){
    // Create a new agent with the specified name
    Agent newAgent(name);

    // Add the new agent to the end of the list
    agents.push_back(newAgent);

    // Iterate through the list of agents (excluding the newly added one)
    for (auto it = agents.begin(); it != std::prev(agents.end()); ++it) {
        // Check if the waitingCalls queue has more than 2 elements
        if (it->getWaitingCalls().size() > 2) {
            // Reassign the first call from each remaining agent's queue
            newAgent.addCall(it->getWaitingCalls().front());
            it->removeFirstCall();
        }
    }

    // Reassign the first call from the last agent's queue, if any
    if (!agents.empty() && agents.back().getWaitingCalls().size() > 0) {
        newAgent.addCall(agents.back().getWaitingCalls().front());
        agents.back().removeFirstCall();
    }
}


//TODO
unsigned CallCenter::processOrders(string zc, unsigned n) {
    unsigned ordersProcessed = 0;

    // Iterate through the vector of stacks
    for (auto& orderStack : orders) {
        // Process orders with the specified zip code
        while (!orderStack.empty() && ordersProcessed < n) {
            // Get the top order from the stack
            Order currentOrder = orderStack.top();

            // Check if the order has the specified zip code
            if (currentOrder.getZipCode() == zc) {
                // Remove the order from the stack
                orderStack.pop();
                ++ordersProcessed;
            } else {
                // If the order doesn't match the zip code, move to the next stack
                break;
            }
        }

        // If the stack becomes empty, remove it from the vector
        if (orderStack.empty()) {
            auto it = std::remove_if(orders.begin(), orders.end(), [&](const stack<Order>& s) {
                return &s == &orderStack;
            });
            orders.erase(it, orders.end());
        }

        // Check if the required number of orders has been processed
        if (ordersProcessed >= n) {
            break;
        }
    }

    return ordersProcessed;
}