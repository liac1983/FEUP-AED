#ifndef CALLCENTER_H_
#define CALLCENTER_H_

#include "agent.h"
#include "order.h"
#include "client.h"
#include <queue>
#include <list>
#include <stack>
#include <set>
#include <algorithm>
using namespace std;

class CallCenter {
    list<Agent> agents;
    vector<stack<Order> > orders;
    vector<Order> ordersDelivered;
    set<Client> clients;
public:
    CallCenter();
    vector<stack<Order> > getOrders() const;
    vector<Order> getOrdersDelivered() const;
    list<Agent> getAgents() const;
    set<Client> getClients() const;
    void setOrders(vector<stack<Order> > stOrd1);
    void addAgent(const Agent &a);
    void addClient(const Client& c);
    void addOrderDelivered(const Order &o);
    void sortOrdersDelivered();
    list<string> removeAgentsNoCalls ();
    string putInLessBusyAgent(unsigned call1);
    void updateClient(string name, string zc);
    void addAgent(string name);
    //void addOrder(Order order1);
    unsigned processOrders(string zc, unsigned n);
    set<Client> orderClientsSet(const set<Client>& originalSet) const;
};

#endif
