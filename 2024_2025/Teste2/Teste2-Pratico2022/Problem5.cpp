#include <iostream>
#include "graph.h"
#include "FunWithGraphs.h"

using namespace std;

int main() {
    Graph g1 = FunWithGraphs::graph1();

    cout << g1.pathExists(1, 5, {2}) << endl;    // Esperado: 1 (true)
    cout << g1.pathExists(1, 5, {2, 3}) << endl; // Esperado: 0 (false)
    cout << g1.pathExists(2, 6, {4}) << endl;    // Esperado: 0 (false)
    cout << g1.pathExists(2, 6, {9, 8}) << endl; // Esperado: 1 (true)

    return 0;
}


