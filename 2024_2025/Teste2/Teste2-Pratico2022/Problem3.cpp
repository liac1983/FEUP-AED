#include <iostream>
#include "graph.h"
#include "FunWithGraphs.h"

using namespace std;

int main() {
    Graph g1 = FunWithGraphs::graph1();
    cout << g1.connected() << endl; // Esperado: 1 (true)

    Graph g2 = FunWithGraphs::graph2();
    cout << g2.connected() << endl; // Esperado: 0 (false)

    return 0;
}
