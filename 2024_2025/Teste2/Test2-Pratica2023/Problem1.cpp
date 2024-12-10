#include <iostream>
#include "GraphOps.h"
#include "Graph.h"

// Sample graph creation function for testing
Graph<int> graph1() {
    Graph<int> g;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addEdge(1, 3, 1.0);
    return g;
}

Graph<int> graph4() {
    Graph<int> g;
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addEdge(2, 3, 1.0);
    return g;
}

int main() {
    Graph<int> g1 = graph1();
    std::cout << GraphOps::directlyUnconnected(g1, 1, 2) << std::endl; // Expected: 1
    std::cout << GraphOps::directlyUnconnected(g1, 1, 3) << std::endl; // Expected: 0
    std::cout << GraphOps::directlyUnconnected(g1, 3, 1) << std::endl; // Expected: 1

    Graph<int> g4 = graph4();
    std::cout << GraphOps::directlyUnconnected(g4, 2, 3) << std::endl; // Expected: 0
    std::cout << GraphOps::directlyUnconnected(g4, 4, 2) << std::endl; // Expected: 1

    return 0;
}

