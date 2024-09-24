#ifndef AED2223_CI1_CLIENT_H
#define AED2223_CI1_CLIENT_H

#include <string>

using namespace std;

class Client {
    string name;
    int seniority;
public:
    Client(){ name = ""; seniority = 0; }
    Client(string name): name(name) {seniority = 0; }
    Client(string name, int seniority): name(name), seniority(seniority) {}
    const string &getName() const;
    int getSeniority() const;

    //TODO
    bool operator<(const Client &c) const;
};


#endif //AED2223_CI1_CLIENT_H
