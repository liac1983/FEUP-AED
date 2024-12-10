#include <iostream>
#include "GraphOps.h"
#include "Graph.h"

// Sample graph creation function for testing
Graph<int> graph1() {
    Graph<int> g;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);
    g.addVertex(8);

    g.addEdge(1, 3, 1.0);
    g.addEdge(3, 4, 1.0);
    g.addEdge(4, 5, 1.0);
    g.addEdge(2, 3, 1.0);
    g.addEdge(4, 6, 1.0);
    g.addEdge(7, 8, 1.0);

    return g;
}

int main() {
    Graph<int> g1 = graph1();

    cout << GraphOps::pathExists(g1, 1, 5, {2}) << endl; // Expected: 1
    cout << GraphOps::pathExists(g1, 1, 5, {3}) << endl; // Expected: 0
    cout << GraphOps::pathExists(g1, 2, 6, {4}) << endl; // Expected: 0
    cout << GraphOps::pathExists(g1, 2, 6, {7, 8}) << endl; // Expected: 1

    return 0;
}

