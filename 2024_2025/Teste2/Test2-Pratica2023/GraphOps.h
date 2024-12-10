#ifndef GRAPHOPS_H
#define GRAPHOPS_H

#include "Graph.h"
#include <vector>

class GraphOps {
public:
    static bool directlyUnconnected(Graph<int> g, int u, int v);
    static vector<int> largestOutDegree(Graph<int> g);
    static bool isDAG(Graph<int> g);
    static vector<int> numberSourcesSinks(Graph<int> g);
    static bool pathExists(Graph<int> g, int s, int t, const vector<int>& skip);
    static int numberConnectedComponents(Graph<int> g);
};

#endif // GRAPHOPS_H
