#include <iostream>
#include "graph.h"
#include "FunWithGraphs.h"

using namespace std;

int main() {
    Graph g1 = FunWithGraphs::graph1();

    cout << g1.countNodes(5, 1) << endl; // Esperado: 3
    cout << g1.countNodes(6, 2) << endl; // Esperado: 2
    cout << g1.countNodes(1, 3) << endl; // Esperado: 1

    return 0;
}
~
