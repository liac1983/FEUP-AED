#include "Client.h"

const string &Client::getName() const {
    return name;
}

int Client::getSeniority() const {
    return seniority;
}

//=============================================================================

//TODO
bool Client::operator<(const Client &c) const {
    return true;
}
