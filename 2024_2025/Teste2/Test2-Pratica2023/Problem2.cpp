#include <iostream>
#include "GraphOps.h"
#include "Graph.h"

// Sample graph creation function for testing
Graph<int> graph1() {
    Graph<int> g;
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addEdge(0, 1, 1.0);
    g.addEdge(0, 2, 1.0);
    g.addEdge(4, 3, 1.0);
    g.addEdge(4, 0, 1.0);
    return g;
}

Graph<int> graph2() {
    Graph<int> g;
    g.addVertex(0);
    g.addVertex(5);
    g.addVertex(7);
    g.addEdge(0, 1, 1.0);
    g.addEdge(0, 2, 1.0);
    g.addEdge(5, 3, 1.0);
    g.addEdge(5, 4, 1.0);
    g.addEdge(7, 6, 1.0);
    g.addEdge(7, 8, 1.0);
    return g;
}

int main() {
    Graph<int> g1 = graph1();
    auto v1 = GraphOps::largestOutDegree(g1);
    for (auto v : v1) cout << v << " ";
    cout << endl;

    Graph<int> g2 = graph2();
    auto v2 = GraphOps::largestOutDegree(g2);
    for (auto v : v2) cout << v << " ";
    cout << endl;

    return 0;
}
