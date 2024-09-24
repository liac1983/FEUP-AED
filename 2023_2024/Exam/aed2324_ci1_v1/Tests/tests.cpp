#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "callCenter.h"
#include "order.h"
#include "client.h"
#include "agent.h"
#include <string>
#include <queue>
#include <list>
#include <set>

using testing::Eq;
using namespace std;

TEST(test, test_sortOrders){
    CallCenter cc1;

    cc1.sortOrdersDelivered();
    vector<Order> v = cc1.getOrdersDelivered();

    // test empty vector
    EXPECT_EQ(0, v.size());
    v.clear();

    Order o1(1, "4200");
    Order o2(2, "4400");
    Order o3(3, "4100");
    Order o4(4, "4500");
    cc1.addOrderDelivered(o1);
    cc1.addOrderDelivered(o2);
    cc1.addOrderDelivered(o3);
    cc1.addOrderDelivered(o4);

    // test criteria 1 ordering: zipCode
    cc1.sortOrdersDelivered();
    v = cc1.getOrdersDelivered();
    EXPECT_EQ(4, v.size());
    if (v.size() == 4) {
        EXPECT_EQ(3, v[0].getId());
        EXPECT_EQ(1, v[1].getId());
        EXPECT_EQ(2, v[2].getId());
        EXPECT_EQ(4, v[3].getId());
    }

    CallCenter cc2;
    Order o12(1, "4200");
    Order o22(7, "4300");
    Order o32(6, "4100");
    Order o42(5, "4100");
    Order o52(4, "4300");
    cc2.addOrderDelivered(o12);
    cc2.addOrderDelivered(o22);
    cc2.addOrderDelivered(o32);
    cc2.addOrderDelivered(o42);
    cc2.addOrderDelivered(o52);

    // test criteria 1 and 2 ordering
    cc2.sortOrdersDelivered();
    v = cc2.getOrdersDelivered();
    EXPECT_EQ(5, v.size());
    if (v.size() == 5) {
        EXPECT_EQ(6, v[0].getId());
        EXPECT_EQ(5, v[1].getId());
        EXPECT_EQ(1, v[2].getId());
        EXPECT_EQ(7, v[3].getId());
        EXPECT_EQ(4, v[4].getId());
    }

}


TEST(test, test_verifyCall){
    Agent a1("joao");
    a1.addCall(2);
    a1.addCall(7);
    a1.addCall(9);
    a1.addCall(11);

    // test call exists 1
    unsigned pos = a1.verifyWaitingCall(2);
    EXPECT_EQ(1, pos);

    queue<unsigned> calls = a1.getWaitingCalls();
    EXPECT_EQ(4,calls.size());
    if (calls.size() == 4) {
        EXPECT_EQ(2,calls.front()); calls.pop();
        EXPECT_EQ(7,calls.front()); calls.pop();
        EXPECT_EQ(9,calls.front()); calls.pop();
        EXPECT_EQ(11,calls.front());
    }

    // test call exists n
    a1.clearCalls();
    a1.addCall(2);
    a1.addCall(7);
    a1.addCall(9);
    pos = a1.verifyWaitingCall(9);
    EXPECT_EQ(3, pos);

    calls = a1.getWaitingCalls();
    EXPECT_EQ(3, calls.size());
    if (calls.size() == 3) {
        EXPECT_EQ(2,calls.front()); calls.pop();
        EXPECT_EQ(7,calls.front()); calls.pop();
        EXPECT_EQ(9,calls.front());
    }


    // test call exists
    a1.clearCalls();
    a1.addCall(1);
    a1.addCall(8);
    a1.addCall(9);
    a1.addCall(15);
    pos = a1.verifyWaitingCall(8);
    EXPECT_EQ(2, pos);

    calls = a1.getWaitingCalls();
    EXPECT_EQ(4,calls.size());
    if (calls.size() == 4) {
        EXPECT_EQ(1,calls.front()); calls.pop();
        EXPECT_EQ(8,calls.front()); calls.pop();
        EXPECT_EQ(9,calls.front()); calls.pop();
        EXPECT_EQ(15,calls.front());
    }

   // test call does not exist
    a1.clearCalls();
    a1.addCall(1);
    a1.addCall(4);
    a1.addCall(5);
    pos = a1.verifyWaitingCall(3);
    EXPECT_EQ(0, pos);

    calls = a1.getWaitingCalls();
    EXPECT_EQ(3,calls.size());
    if (calls.size() == 3) {
        EXPECT_EQ(1,calls.front()); calls.pop();
        EXPECT_EQ(4,calls.front()); calls.pop();
        EXPECT_EQ(5,calls.front());
    }

}


TEST(test, test_removeAgents){
    CallCenter cc1;
    Agent a1("joao");
    a1.addCall(2);
    Agent a2("ana");
    Agent a3("rui");
    a3.addCall(2);
    Agent a4("luis");
    a4.addCall(2);
    cc1.addAgent(a1);
    cc1.addAgent(a2);
    cc1.addAgent(a3);
    cc1.addAgent(a4);

    // test remove one agent
    list<string> res = cc1.removeAgentsNoCalls();

    // -- test res
    EXPECT_EQ(1,res.size());
    if (res.size()==1)
        EXPECT_EQ(res.front(),"ana");

    // -- test remaining
    list<Agent> agents = cc1.getAgents();
    EXPECT_EQ(3,agents.size());
    if (agents.size()==3) {
        list<Agent>::iterator it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="joao"); });
        EXPECT_EQ(false, it==agents.end());
        it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="rui"); });
        EXPECT_EQ(false, it==agents.end());
        it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="luis"); });
        EXPECT_EQ(false, it==agents.end());
    }

    CallCenter cc2;
    Agent a12("joao");
    a12.addCall(2);
    Agent a22("ana");
    Agent a32("rosa");
    a32.addCall(2);
    Agent a42("luis");
    cc2.addAgent(a12);
    cc2.addAgent(a22);
    cc2.addAgent(a32);
    cc2.addAgent(a42);

    // test remove no consecutive agents
    res = cc2.removeAgentsNoCalls();

    // -- test res
    EXPECT_EQ(2,res.size());
    if (res.size()==2) {
        list<string>::iterator it= find(res.begin(), res.end(),"ana");
        EXPECT_EQ(false, it==res.end());
        it= find(res.begin(), res.end(),"luis");
        EXPECT_EQ(false, it==res.end());
    }

    // -- test remaining
    agents = cc2.getAgents();
    EXPECT_EQ(2,agents.size());
    if (agents.size()==2) {
        list<Agent>::iterator it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="rosa"); });
        EXPECT_EQ(false, it==agents.end());
        it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="joao"); });
        EXPECT_EQ(false, it==agents.end());
    }

    CallCenter cc3;
    Agent a13("joao");
    Agent a23("ana");
    Agent a33("rosa");
    Agent a43("luis");
    a43.addCall(2);
    Agent a53("mario");
    a53.addCall(2);
    cc3.addAgent(a13);
    cc3.addAgent(a23);
    cc3.addAgent(a33);
    cc3.addAgent(a43);
    cc3.addAgent(a53);

    // test remove consecutive agents
    res = cc3.removeAgentsNoCalls();

    // -- test res
    EXPECT_EQ(3,res.size());
    if (res.size()==3) {
        list<string>::iterator it= find(res.begin(), res.end(),"ana");
        EXPECT_EQ(false, it==res.end());
        it= find(res.begin(), res.end(),"joao");
        EXPECT_EQ(false, it==res.end());
        it= find(res.begin(), res.end(),"rosa");
        EXPECT_EQ(false, it==res.end());
    }

    // -- test remaining
    agents = cc3.getAgents();
    EXPECT_EQ(2,agents.size());
    if (agents.size()==2) {
        list<Agent>::iterator it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="mario"); });
        EXPECT_EQ(false, it==agents.end());
        it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="luis"); });
        EXPECT_EQ(false, it==agents.end());
    }

}


TEST(test, test_PutInLessBusyAgent){
    CallCenter cc;

    EXPECT_EQ("noAgent",cc.putInLessBusyAgent(33));
    EXPECT_EQ(0, cc.getAgents().size());
        
    CallCenter cc1;
    Agent a1 ("rui");
    a1.addCall(1);
    a1.addCall(2);
    a1.addCall(3);
    cc1.addAgent(a1);
    Agent a2 ("luis");
    cc1.addAgent(a2);
    Agent a3 ("ana");
    a3.addCall(4);
    a3.addCall(5);
    cc1.addAgent(a3);
    Agent a4 ("maria");
    a4.addCall(6);
    cc1.addAgent(a4);

    // test one minimum
    // -- test result
    EXPECT_EQ("luis",cc1.putInLessBusyAgent(8));
    list<Agent> agents = cc1.getAgents();
    EXPECT_EQ(4,agents.size());

    if (agents.size()==4) {
        // -- test add call
        list<Agent>::iterator it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="luis"); });
        EXPECT_EQ(false, it==agents.end());
        if (it!=agents.end())
            EXPECT_EQ(1,it->getWaitingCalls().size());

        // -- test remaining agents
        it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="rui"); });
        EXPECT_EQ(false, it==agents.end());
        if (it!=agents.end())
            EXPECT_EQ(3,it->getWaitingCalls().size());
        it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="maria"); });
        EXPECT_EQ(false, it==agents.end());
        if (it!=agents.end())
            EXPECT_EQ(1,it->getWaitingCalls().size());
    }


    CallCenter cc2;
    Agent a12 ("rui");
    a12.addCall(1);
    a12.addCall(2);
    cc2.addAgent(a12);
    Agent a22 ("rosa");
    a22.addCall(3);
    cc2.addAgent(a22);
    Agent a32 ("ana");
    a32.addCall(4);
    cc2.addAgent(a32);

    // test more than one minimum
    // -- test result
    EXPECT_EQ("rosa",cc2.putInLessBusyAgent(8));
    agents = cc2.getAgents();
    EXPECT_EQ(3,agents.size());

    if (agents.size()==3) {
        // -- test add call
        list<Agent>::iterator it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="rosa"); });
        EXPECT_EQ(false, it==agents.end());
        if (it!=agents.end())
            EXPECT_EQ(2,it->getWaitingCalls().size());

        // -- test remaining agents
        it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="rui"); });
        EXPECT_EQ(false, it==agents.end());
        if (it!=agents.end())
            EXPECT_EQ(2,it->getWaitingCalls().size());
        it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="ana"); });
        EXPECT_EQ(false, it==agents.end());
        if (it!=agents.end())
            EXPECT_EQ(1,it->getWaitingCalls().size());
    }

}


TEST(test, test_updateClient){
    CallCenter cc1;
    cc1.addClient(Client("joao","4500", 2));
    cc1.addClient(Client("rui","4100", 5));
    cc1.addClient(Client("ana","4200", 9));
    set<Client> s= cc1.getClients();

    // test build set: 1 criteria
    EXPECT_EQ(3, s.size());
    if (s.size() == 3) {
        Client c = *s.begin();
        EXPECT_EQ("4100", c.getZipCode());
        c = *s.rbegin();
        EXPECT_EQ("4500", c.getZipCode());
    }

    CallCenter cc2;
    cc2.addClient(Client("joao","4400", 4));
    cc2.addClient(Client("rui","4100", 1));
    cc2.addClient(Client("ana","4100", 10));
    cc2.addClient(Client("maria","4200", 6));
    s= cc2.getClients();

    // test build set: 2 criteria
    EXPECT_EQ(4, s.size());
    if (s.size() == 4) {
        Client c = *s.begin();
        EXPECT_EQ("4100", c.getZipCode());
        EXPECT_EQ("ana", c.getName());
        c = *s.rbegin();
        EXPECT_EQ("4400", c.getZipCode());
        EXPECT_EQ("joao", c.getName());
    }

    cc1.updateClient("ana","4200");
    // test update 1 criteria, client exists
    // -- test res same size
    s= cc1.getClients();
    EXPECT_EQ(3,s.size());
    // -- test set
    if (s.size()==3) {
        Client c=*s.begin();
        EXPECT_EQ("rui", c.getName());
        s.erase(s.begin());
        c=*s.begin();
        EXPECT_EQ("ana", c.getName());
        // -- test update
        EXPECT_EQ(10,c.getNumOrders());
    }

    cc2.updateClient("vasco","4200");
    // test update 2 criteria2, client does not exist
    // -- test res same size
    s= cc2.getClients();
    EXPECT_EQ(5,s.size());
    // -- test set
    if (s.size()==5) {
        Client c=*s.begin();
        EXPECT_EQ("ana", c.getName());
        s.erase(s.begin());
        c=*s.begin();
        EXPECT_EQ("rui", c.getName());
        s.erase(s.begin());
        c=*s.begin();
        EXPECT_EQ("maria", c.getName());
        s.erase(s.begin());
        c=*s.begin();
        // -- test add
        EXPECT_EQ("vasco", c.getName());
        EXPECT_EQ(1,c.getNumOrders());
    }

}


TEST(test, test_addAgent){
    CallCenter cc1;
    Agent a1("joao");
    a1.addCall(1);
    cc1.addAgent(a1);
    Agent a2("rui");
    a2.addCall(2);
    a2.addCall(3);
    a2.addCall(4);
    cc1.addAgent(a2);
    Agent a3 ("mario");
    a3.addCall(5);
    cc1.addAgent(a3);

    // test calls from 1 agent
    cc1.addAgent("vasco");
    list<Agent> agents = cc1.getAgents();

    // -- test add:size
    EXPECT_EQ(4, agents.size());
    if (agents.size()==4) {

        // -- test new agent, name and queue
        Agent an = agents.back();
        EXPECT_EQ("vasco", an.getName());
        EXPECT_EQ(1, an.getWaitingCalls().size());
        EXPECT_EQ(2, an.getWaitingCalls().front());

        // -- test removed call, agent name and queue
        list<Agent>::iterator it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="rui"); });
        EXPECT_EQ(false, it==agents.end());
        if (it!=agents.end())
            EXPECT_EQ(2,it->getWaitingCalls().size());

        // -- test remaining agents
        it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="joao"); });
        EXPECT_EQ(false, it==agents.end());
        if (it!=agents.end())
            EXPECT_EQ(1,it->getWaitingCalls().size());

        it= find_if(agents.begin(), agents.end(),[](Agent const &o) {
            return (o.getName()=="mario"); });
        EXPECT_EQ(false, it==agents.end());
        if (it!=agents.end())
            EXPECT_EQ(1,it->getWaitingCalls().size());

    }


    CallCenter cc2;
    Agent a4("rita");
    a4.addCall(10); a4.addCall(11);
    a4.addCall(12); a4.addCall(13);
        cc1.addAgent(a1);
    cc2.addAgent(a1);
    cc2.addAgent(a2);
    cc2.addAgent(a4);
    cc2.addAgent(a3);

    // test calls from several agents
    cc2.addAgent("sara");
    agents = cc2.getAgents();

    // -- test add:size
    EXPECT_EQ(5, agents.size());
    if (agents.size()==5) {

        // -- test new agent, name and queue
        Agent an = agents.back();
        EXPECT_EQ("sara", an.getName());
        EXPECT_EQ(2, an.getWaitingCalls().size());

        // -- test removed call, agent name and queue
        list<Agent>::iterator it = find_if(agents.begin(), agents.end(), [](Agent const &o) {
            return (o.getName() == "rui");
        });
        EXPECT_EQ(false, it == agents.end());
        if (it != agents.end())
            EXPECT_EQ(2, it->getWaitingCalls().size());

        it = find_if(agents.begin(), agents.end(), [](Agent const &o) {
            return (o.getName() == "rita");
        });
        EXPECT_EQ(false, it == agents.end());
        if (it != agents.end())
            EXPECT_EQ(3, it->getWaitingCalls().size());

        // -- test remaining agents
        it = find_if(agents.begin(), agents.end(), [](Agent const &o) {
            return (o.getName() == "joao");
        });
        EXPECT_EQ(false, it == agents.end());
        if (it != agents.end())
            EXPECT_EQ(1, it->getWaitingCalls().size());

        it = find_if(agents.begin(), agents.end(), [](Agent const &o) {
            return (o.getName() == "mario");
        });
        EXPECT_EQ(false, it == agents.end());
        if (it != agents.end())
            EXPECT_EQ(1, it->getWaitingCalls().size());
    }

}


TEST(test, test_processOrder){
    CallCenter cc1;
    vector<stack<Order> > orders;
    stack<Order> s1;
    s1.push(Order(1, "4100"));
    s1.push(Order(2,"4100"));
    s1.push(Order(3,"4100"));
    s1.push(Order(4,"4100"));
    orders.push_back(s1);
    stack<Order> s2;
    s2.push(Order(11,"4300"));
    orders.push_back(s2);
    cc1.setOrders(orders);

    // test numOrders > n
    unsigned numO = cc1.processOrders("4100",3);
    EXPECT_EQ(3,numO);

    // -- test remaining
    orders.clear();
    orders = cc1.getOrders();
    EXPECT_EQ(2,orders.size());
    if (orders.size()==2) {
        vector<stack<Order>>::iterator it= find_if(orders.begin(), orders.end(),[](stack<Order> const &o) {
            return (o.size()==1 && o.top().getZipCode()=="4100" && o.top().getId()==1); });
        EXPECT_EQ(false, it==orders.end());
        it= find_if(orders.begin(), orders.end(),[](stack<Order> const &o) {
            return (o.size()==1 && o.top().getZipCode()=="4300" && o.top().getId()==11); });
        EXPECT_EQ(false, it==orders.end());
    }


    CallCenter cc2;
    orders.clear();
    stack<Order> s12;
    s12.push(Order(15,"4100"));
    orders.push_back(s12);
    stack<Order> s22;
    s22.push(Order(23,"4300"));
    s22.push(Order(24,"4300"));
    s22.push(Order(25,"4300"));
    s22.push(Order(26,"4300"));
    orders.push_back(s22);
    stack<Order> s32;
    s32.push(Order(31,"4000"));
    orders.push_back(s32);
    stack<Order> s42;
    s42.push(Order(42,"4600"));
    s42.push(Order(43,"4600"));
    orders.push_back(s42);
    cc2.setOrders(orders);

    // test numOrders < n
    numO =  cc2.processOrders("4300",7);
    EXPECT_EQ(4,numO);

    // -- test remaining
    orders.clear();
    orders = cc2.getOrders();
    EXPECT_EQ(3,orders.size());

    // -- test stack remove
    vector<stack<Order>>::iterator it= find_if(orders.begin(), orders.end(),[](stack<Order> const &o) {
        return (o.size()>0 && o.top().getZipCode()=="4300"); });
    EXPECT_EQ(true, it==orders.end());

    if (orders.size()==3) {
        it= find_if(orders.begin(), orders.end(),[](stack<Order> const &o) {
            return (o.size()==1 && o.top().getZipCode()=="4100" && o.top().getId()==15); });
        EXPECT_EQ(false, it==orders.end());
        it= find_if(orders.begin(), orders.end(),[](stack<Order> const &o) {
            return (o.size()==1 && o.top().getZipCode()=="4000" && o.top().getId()==31); });
        EXPECT_EQ(false, it==orders.end());
        it= find_if(orders.begin(), orders.end(),[](stack<Order> const &o) {
            return (o.size()==2 && o.top().getZipCode()=="4600" && o.top().getId()==43); });
        EXPECT_EQ(false, it==orders.end());
    }

}
