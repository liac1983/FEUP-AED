#include <iostream>
#include "GraphOps.h"
#include "Graph.h"

// Sample graph creation functions for testing
Graph<int> graph1() {
    Graph<int> g;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addEdge(1, 2, 1.0);
    g.addEdge(2, 3, 1.0);
    return g;
}

Graph<int> graph3() {
    Graph<int> g;
    g.addVertex(5);
    g.addVertex(10);
    g.addVertex(11);
    g.addEdge(5, 11, 1.0);
    g.addEdge(11, 10, 1.0);
    g.addEdge(10, 5, 1.0);  // Cycle here
    return g;
}

int main() {
    Graph<int> g1 = graph1();
    cout << GraphOps::isDAG(g1) << endl; // Expected: 1 (true)

    Graph<int> g3 = graph3();
    cout << GraphOps::isDAG(g3) << endl; // Expected: 0 (false)

    return 0;
}
