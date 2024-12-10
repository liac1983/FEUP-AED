#include <iostream>
#include "GraphOps.h"
#include "Graph.h"

// Sample graph creation functions for testing
Graph<int> graph4() {
    Graph<int> g;
    g.addVertex(0);
    g.addVertex(7);
    g.addVertex(5);
    g.addEdge(0, 1, 1.0);
    g.addEdge(2, 3, 1.0);
    return g;
}

int main() {
    Graph<int> g4 = graph4();
    auto v1 = GraphOps::numberSourcesSinks(g4);

    cout << v1[0] << endl; // Number of sources
    cout << v1[1] << endl; // Number of sinks

    return 0;
}
