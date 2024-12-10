#include <iostream>
#include "graph.h"
#include "FunWithGraphs.h"

using namespace std;

int main() {
    Graph g1 = FunWithGraphs::graph1();
    auto v1 = g1.largestDegree();
    for (auto v : v1) cout << v << " ";
    cout << endl;

    Graph g2 = FunWithGraphs::graph2();
    auto v2 = g2.largestDegree();
    for (auto v : v2) cout << v << " ";
    cout << endl;

    return 0;
}
