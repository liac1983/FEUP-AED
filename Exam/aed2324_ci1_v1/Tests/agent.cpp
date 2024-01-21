#include "agent.h"
#include <string>

using namespace std;

Agent::Agent(string nm): name(nm)
{}

string Agent::getName() const{
    return name;
}

queue<unsigned> Agent::getWaitingCalls() const {
    return waitingCalls;
}

void Agent::addCall(unsigned cod) {
    waitingCalls.push(cod);
}

void Agent::clearCalls() {
    while (!waitingCalls.empty())
        waitingCalls.pop();
}

void Agent::removeFirstCall() {
    waitingCalls.pop();
}

//---------------------------------------------------------------------

//TODO
unsigned Agent::verifyWaitingCall(unsigned nc) {
    queue<unsigned> tempCalls = waitingCalls;  // Create a temporary copy for iteration
    unsigned position = 0;

    // Iterate through the temporary queue to find the position of the call
    while (!tempCalls.empty()) {
        position++;
        if (tempCalls.front() == nc) {
            // Call found, return its position
            return position;
        }
        tempCalls.pop();
    }

    // If the call is not found, return 0
    return 0;
}

