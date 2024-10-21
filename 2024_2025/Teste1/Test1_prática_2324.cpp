

#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>

using namespace std;

class Order {
    unsigned id;
    string zipCode;
public:
    Order(unsigned id, const string &zipCode) : id(id), zipCode(zipCode) {}

    // Getter methods for id and zipCode
    unsigned getId() const { return id; }
    string getZipCode() const { return zipCode; }
};

class Client {
    string name;
    string zipCode;
    unsigned numOrders;
public:

    // d
    // Constructor
    Client(const string &name, const string &zipCode, unsigned numOrders = 1) 
        : name(name), zipCode(zipCode), numOrders(numOrders) {}

    // Getters
    string getName() const { return name; }
    string getZipCode() const { return zipCode; }
    unsigned getNumOrders() const { return numOrders; }

    // Increment the number of orders
    void incrementOrders() {
        numOrders++;
    }
    // Overload the less-than operator for ordering
    bool operator<(const Client &other) const {
        if (zipCode == other.zipCode) {
            return name < other.name;  // If zip codes are the same, compare by name
        }
        return zipCode < other.zipCode;  // Otherwise, compare by zip code
    }

    // Friend class to allow CallCenter access to private members
    friend class CallCenter;


    // ...
};

class Agent {
    string name;
    queue<unsigned> waitingCalls;
public:
    // b
    Agent(const std::string &name, const std::queue<unsigned> &calls) : name(name), waitingCalls(calls) {}
    unsigned Agent::verifyWaitingCall (unsigned nc) {
        queue<unsigned> tempQueue = waitingCalls;
        unsigned position = 1;

        while (!tempQueue.empty()) {
            if (tempQueue.front() == nc) {
                return position;
            }
            tempQueue.pop();
            position++;
        }
        return 0;

    };
    // Function to add a call to the queue (for testing purposes)
    void addCall(unsigned callId) {
        waitingCalls.push(callId);
    };

    // f
    // Method to remove the first call from the queue
    unsigned removeFirstCall() {
        if (!waitingCalls.empty()) {
            unsigned callId = waitingCalls.front();
            waitingCalls.pop();
            return callId;
        }
        return 0;  // Return 0 if there are no calls
    }

    // Function to check if the agent has any waiting calls
    bool hasCalls() const {
        return !waitingCalls.empty();
    };

    // Getter for the agent's name
    string getName() const {
        return name;
    };

    unsigned getNumberOfCalls() const {
        return waitingCalls.size();
    };
    // Function to display all waiting calls (for testing purposes)
    void displayCalls() const {
        queue<unsigned> tempQueue = waitingCalls;
        cout << "Calls for " << name << ": ";
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << " ";
            tempQueue.pop();
        }
        cout << endl;
    }
    friend class CallCenter;
};

class CallCenter {
    list<Agent> agents;
    vector<stack<Order>> orders;
    vector<Order> ordersDelivered;
    set<Client> clients;

public:
//g
    void addOrder(const Order &order) {
        // Find the stack for the given zip code
        for (auto &orderStack : orders) {
            if (!orderStack.empty() && orderStack.top().getZipCode() == order.getZipCode()) {
                orderStack.push(order);  // Add the order to the existing stack
                return;
            }
        }

        // If no stack exists for the zip code, create a new stack
        stack<Order> newStack;
        newStack.push(order);
        orders.push_back(newStack);
    };

    unsigned processOrders(const string &zip1, unsigned n) {
        unsigned ordersProcessed = 0;

        // Iterate through the vector of stacks to find the stack with zip code zip1
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if (!it->empty() && it->top().getZipCode() == zip1) {
                // Process up to n orders from this stack
                while (!it->empty() && ordersProcessed < n) {
                    it->pop();
                    ordersProcessed++;
                }

                // If the stack becomes empty, remove it from the vector
                if (it->empty()) {
                    orders.erase(it);
                }

                // Return the number of processed orders
                return ordersProcessed;
            }
        }

        // Return the total number of orders processed (could be less than n)
        return ordersProcessed;
    };
     void displayOrders() const {
        for (const auto &orderStack : orders) {
            if (!orderStack.empty()) {
                cout << "Stack for zip code: " << orderStack.top().getZipCode() << endl;
                stack<Order> tempStack = orderStack;
                while (!tempStack.empty()) {
                    cout << "  Order ID: " << tempStack.top().getId() << endl;
                    tempStack.pop();
                }
            }
        }
    };


// a
    void sortOrdersDelivered() {
        auto comparator = [](const Order& a, const Order& b) {
            if (a.getZipCode() != b.getZipCode()) {
                return a.getZipCode() < b.getZipCode();
            } else {
                return a.getId() > b.getId();
            }
        };

        std::sort(ordersDelivered.begin(), ordersDelivered.end(), comparator);
    }
    // c
    /* void addAgent(const Agent &agent) {
        agents.push_back(agent);
    }; */

    // f
    /*void addAgent(const string &name) {
        // Create the new agent
        Agent newAgent(name);
        agents.push_back(newAgent);  // Add the new agent to the end of the list

        // Iterator for the newly added agent (last element in the list)
        auto newAgentIt = --agents.end();

        // Iterate over the other agents in the list
        for (auto it = agents.begin(); it != newAgentIt; ++it) {
            if (it->getNumberOfCalls() > 2) {
                // Remove the first call from this agent and add it to the new agent
                unsigned callId = it->removeFirstCall();
                newAgentIt->addCall(callId);
            }
        }
    }*/

    void displayAllAgents() const {
        for (const auto &agent : agents) {
            agent.displayCalls();
        }
    }

    void addAgentWithoutReassignment(const Agent &agent) {
        agents.push_back(agent);
    }

    list<string> removeAgentsNoCalls() {
        list<string> removedAgentNames;

        // Use an iterator to traverse the agents list
        for (auto it = agents.begin(); it != agents.end();) {
            if (!it->hasCalls()) {  // If the agent has no waiting calls
                removedAgentNames.push_back(it->getName());  // Add their name to the list
                it = agents.erase(it);  // Remove the agent and get the next iterator
            } else {
                ++it;  // Move to the next agent if not removed
            }
        }

        return removedAgentNames;
    }

    // Function to display the names of all agents in the call center (for testing purposes)
    void displayAgents() const {
        for (const auto &agent : agents) {
            cout << agent.getName() << endl;
        }
    }

    // d
    // Function to put a call in the least busy agent's queue
    string putInLessBusyAgent(unsigned call1) {
        if (agents.empty()) {
            return "noAgent";  // Return "noAgent" if there are no agents
        }

        // Initialize a pointer to the least busy agent
        auto leastBusyAgent = agents.begin();
        unsigned minCalls = leastBusyAgent->getNumberOfCalls();

        // Iterate through the list of agents to find the least busy one
        for (auto it = agents.begin(); it != agents.end(); ++it) {
            unsigned numCalls = it->getNumberOfCalls();
            if (numCalls < minCalls) {
                leastBusyAgent = it;
                minCalls = numCalls;
            }
        }

        // Add the call to the least busy agent's queue
        leastBusyAgent->addCall(call1);

        // Return the name of the selected agent
        return leastBusyAgent->getName();
    }
    // d
    // Function to update or add a client when they place an order
    void updateClient(const string &name, const string &zc) {
        // Create a temporary client object to search in the set
        Client tempClient(name, zc);

        // Try to find the client in the set
        auto it = clients.find(tempClient);

        if (it != clients.end()) {
            // Client exists, so we need to update the order count
            Client updatedClient = *it;  // Copy the existing client
            clients.erase(it);           // Remove the old entry from the set
            updatedClient.incrementOrders();  // Increment the number of orders
            clients.insert(updatedClient);    // Reinsert the updated client
        } else {
            // Client does not exist, add them with numOrders set to 1
            clients.insert(Client(name, zc, 1));
        }
    }

    // Function to display all clients (for testing purposes)
    void displayClients() const {
        for (const auto &client : clients) {
            cout << "Client: " << client.getName() << ", Zip Code: " << client.getZipCode() 
                 << ", Orders: " << client.getNumOrders() << endl;
        }
    }

    // Additional methods and members...
};

int main() {
    // f
    /*CallCenter center;

    // Add some orders
    center.addOrder(Order(1001, "12345"));
    center.addOrder(Order(1002, "12345"));
    center.addOrder(Order(1003, "12345"));
    center.addOrder(Order(2001, "54321"));
    center.addOrder(Order(2002, "54321"));

    // Display the orders before processing
    cout << "Orders before processing:" << endl;
    center.displayOrders();

    // Process 2 orders with zip code "12345"
    unsigned processed = center.processOrders("12345", 2);
    cout << "\nProcessed " << processed << " orders with zip code 12345.\n";

    // Display the orders after processing
    cout << "\nOrders after processing:" << endl;
    center.displayOrders();*/

    // a
    // Example usage
    //CallCenter center;

    // Adding some sample orders to ordersDelivered
    //center.sortOrdersDelivered();

    // b
    /*// Example usage
    std::queue<unsigned> calls;
    calls.push(1001);
    calls.push(1002);
    calls.push(1003);
    
    Agent agent("John", calls);
    
    unsigned callPosition = agent.verifyWaitingCall(1002);
    if (callPosition > 0) {
        std::cout << "Call found at position: " << callPosition << std::endl;
    } else {
        std::cout << "Call not found." << std::endl;
    }*/

   // c
   /*// Example usage
    CallCenter center;

    // Adding agents
    Agent agent1("John");
    Agent agent2("Jane");
    Agent agent3("Alice");

    // Adding some calls to agents
    agent1.addCall(1001);  // John has calls
    agent3.addCall(1003);  // Alice has calls

    // Adding agents to the call center
    center.addAgent(agent1);
    center.addAgent(agent2);  // Jane has no calls
    center.addAgent(agent3);

    // Display agents before removal
    cout << "Agents before removal:" << endl;
    center.displayAgents();

    // Remove idle agents and get their names
    list<string> removedAgents = center.removeAgentsNoCalls();

    // Display removed agents
    cout << "\nRemoved agents:" << endl;
    for (const auto &name : removedAgents) {
        cout << name << endl;
    }

    // Display agents after removal
    cout << "\nAgents after removal:" << endl;
    center.displayAgents();
*/

    // d
    /*// Example usage
    CallCenter center;

    // Adding agents
    Agent agent1("John");
    Agent agent2("Jane");
    Agent agent3("Alice");

    // Adding some calls to agents
    agent1.addCall(1001);  // John has 1 call
    agent3.addCall(1003);  // Alice has 1 call
    agent3.addCall(1004);  // Alice has 2 calls

    // Adding agents to the call center
    center.addAgent(agent1);
    center.addAgent(agent2);  // Jane has no calls
    center.addAgent(agent3);

    // Display agents before adding the new call
    cout << "Agents before adding the call:" << endl;
    center.displayAgents();

    // Put a new call in the queue of the least busy agent
    string selectedAgent = center.putInLessBusyAgent(2001);
    cout << "\nCall assigned to: " << selectedAgent << endl;

    // Display agents after adding the new call
    cout << "\nAgents after adding the call:" << endl;
    center.displayAgents();*/

    // e
   /*   CallCenter center;

    // Adding clients with orders
    center.updateClient("Alice", "1001");
    center.updateClient("Bob", "1002");
    center.updateClient("Charlie", "1001");

    // Update clients by adding more orders
    center.updateClient("Alice", "1001");  // Alice places another order
    center.updateClient("David", "1002");

    // Display all clients
    center.displayClients();

     */

    // f
    /*// Example usage
    CallCenter center;

    // Adding existing agents with some calls
    Agent agent1("John");
    agent1.addCall(1001);
    agent1.addCall(1002);
    agent1.addCall(1003);  // John has 3 calls

    Agent agent2("Jane");
    agent2.addCall(2001);
    agent2.addCall(2002);  // Jane has 2 calls

    Agent agent3("Alice");
    agent3.addCall(3001);
    agent3.addCall(3002);
    agent3.addCall(3003);
    agent3.addCall(3004);  // Alice has 4 calls

    // Add agents to the call center
    center.addAgentWithoutReassignment(agent1);
    center.addAgentWithoutReassignment(agent2);
    center.addAgentWithoutReassignment(agent3);

    // Display agents before adding the new agent
    cout << "Before adding the new agent:" << endl;
    center.displayAllAgents();

    // Add the new agent "Bob" and reassign calls
    center.addAgent("Bob");

    // Display agents after adding the new agent
    cout << "\nAfter adding the new agent:" << endl;
    center.displayAllAgents();*/

    //g



    return 0;
}
