//
// Created by lara2 on 12/12/2023.
//

#ifndef TESTE_2_GRAPH_H
#define TESTE_2_GRAPH_H


#include <list>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>


using namespace std;


class graph {
    struct Edge {
        int dest; // Destination node
        int weight; // An integer weight
    };
    struct Node {
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited; // As the node been visited on a search?
    };
    int n; // Graph size (vertices are numbered from 1 to n)
    bool hasDir; // false: undirected; true: directed
    std::vector<Node> nodes; // The list of nodes being represented
    void dfs(int v); // An example implementation of dfs
    void bfs(int v); // An example implementation of bfs
public:
    // Constructor: nr nodes and direction (default: undirected)
    explicit graph(int nodes, bool dir = false);
    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1);
    vector<int> largestDegree();
    bool connected();
    int countNodes(int v, int k);

    bool disconnected(int u, int v);

    bool pathExists(int u, int v, const vector<int> &avoid);
};


#endif //TESTE_2_GRAPH_H
