#ifndef SRC_FUNWITHGRAPHS_H
#define SRC_FUNWITHGRAPHS_H

#include <list>
#include <unordered_set>
#include "Graph.h"
#include <unordered_map>
#include <stack>
#include <vector>
#include <algorithm>



class funWithGraphs {
public:
    static int connectedComponents(Graph<int> *g);
    static int giantComponent(Graph<int> *g);
    static list<list<int>> scc(Graph<int> *g);
    static unordered_set<int> articulationPoints(Graph<int> *g);
};

#endif
