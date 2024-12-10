#include <iostream>
#include "graph.h"
#include "FunWithGraphs.h"

using namespace std;

int main() {
    Graph g1 = FunWithGraphs::graph1();
    cout << g1.disconnected(1, 2) << endl; // Esperado: 0 (conectados)
    cout << g1.disconnected(1, 4) << endl; // Esperado: 1 (desconectados)
    cout << g1.disconnected(3, 1) << endl; // Esperado: 0 (conectados)

    Graph g4 = FunWithGraphs::graph4();
    cout << g4.disconnected(2, 4) << endl; // Esperado: 0 (conectados)
    cout << g4.disconnected(4, 2) << endl; // Esperado: 1 (desconectados)

    return 0;
}
