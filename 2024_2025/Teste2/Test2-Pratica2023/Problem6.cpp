#include <iostream>
#include "GraphOps.h"
#include "Graph.h"

// Sample graph creation functions for testing
Graph<int> graph2() {
    Graph<int> g;
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addEdge(0, 1, 1.0);
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
    g.addVertex(15);  // A disconnected node
    return g;
}

int main() {
    Graph<int> g2 = graph2();
    cout << GraphOps::numberConnectedComponents(g2) << endl; // Expected: 3

    Graph<int> g3 = graph3();
    cout << GraphOps::numberConnectedComponents(g3) << endl; // Expected: 2

    return 0;
}


