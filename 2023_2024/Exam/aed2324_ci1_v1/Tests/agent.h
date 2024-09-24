#ifndef AGENT_H_
#define AGENT_H_

#include <string>
#include <queue>
using namespace std;

class Agent {
    string name;
    queue<unsigned> waitingCalls;
public:
    Agent(string nm);
    void addCall(unsigned cod);
    string getName() const;
    void removeFirstCall();
    queue<unsigned> getWaitingCalls() const;
    void clearCalls();
    unsigned verifyWaitingCall(unsigned nc);
};

#endif