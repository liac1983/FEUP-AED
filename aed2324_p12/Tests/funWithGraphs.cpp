#include "funWithGraphs.h"

//=============================================================================
// Exercise 2.1: Connected Components
//=============================================================================
// TODO
void dfsVisit(Vertex<int> *v);
int funWithGraphs::connectedComponents(Graph<int> *g) {
    // Reset visited flags for all vertices
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    int components = 0;

    for (auto v : g->getVertexSet()) {
        if (!v->isVisited()) {
            dfsVisit(v);
            components++;
        }
    }

    return components;
}

void dfsVisit(Vertex<int> *v) {
    v->setVisited(true);
    for (auto &e : v->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            dfsVisit(w);
        }
    }
}


//=============================================================================
// Exercise 2.2: Giant Component
//=============================================================================
// TODO
int dfsGC(Vertex<int> *v);
int funWithGraphs::giantComponent(Graph<int> *g) {
    int maxComponentSize = 0;

    // Reset visited flags for all vertices
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    for (auto v : g->getVertexSet()) {
        if (!v->isVisited()) {
            int componentSize = dfsGC(v);
            maxComponentSize = max(maxComponentSize, componentSize);
        }
    }

    return maxComponentSize;
}

int dfsGC(Vertex<int> *v) {
    v->setVisited(true);
    int componentSize = 1;

    for (auto &e : v->getAdj()) {
        auto w = e.getDest();
        if (!w->isVisited()) {
            componentSize += dfsGC(w);
        }
    }

    return componentSize;
}


//=============================================================================
// Exercise 2.3: Strongly Connected Components
//=============================================================================
// TODO
void dfs_scc(Graph<int> *g, Vertex<int> *v, stack<int> &s, list<list<int>> &l, int &i);
list<list<int>> funWithGraphs::scc(Graph<int> *g){
    list<list<int>> res;

    return res;
}

void dfs_scc(Graph<int> *g, Vertex<int> *v, stack<int> &s, list<list<int>> &l, int &i){}


//=============================================================================
// Exercise 2.4: Articulation Points
//=============================================================================
// TODO
void dfs_art(Graph<int> *g, Vertex<int> *v, stack<int> &s, unordered_set<int> &res, int &i);
unordered_set<int> funWithGraphs::articulationPoints(Graph<int> *g) {
    unordered_set<int> res;
    stack<int> s;
    int i = 0;  // Counter for assigning "num" attributes

    for (auto v : g->getVertexSet()) {
        if (!v->isVisited()) {
            dfs_art(g, v, nullptr, i, s, res);
        }
    }

    return res;
}

void dfs_art(Graph<int> *g, Vertex<int> *v, Vertex<int> *parent, int &i, stack<int> &s, unordered_set<int> &res) {
    v->setVisited(true);
    v->setNum(i);
    v->setLow(i);
    i++;

    int children = 0;  // Count of children in DFS tree

    for (auto &e : v->getAdj()) {
        auto w = e.getDest();

        if (!w->isVisited()) {
            children++;
            s.push(v->getInfo());  // Use getInfo() instead of getID()
            s.push(w->getInfo());  // Use getInfo() instead of getID()

            dfs_art(g, w, v, i, s, res);

            // Update low value after child's traversal
            v->setLow(min(v->getLow(), w->getLow()));

            // Check if the current vertex is an articulation point
            if ((parent == nullptr && children > 1) || (parent != nullptr && w->getLow() >= v->getNum())) {
                res.insert(v->getInfo());  // Use getInfo() instead of getID()
            }
        } else if (w != parent && v->getNum() > w->getNum()) {
            // Back edge: update low value
            v->setLow(min(v->getLow(), w->getNum()));
            s.push(v->getInfo());  // Use getInfo() instead of getID()
            s.push(w->getInfo());  // Use getInfo() instead of getID()
        }
    }

    // Check for root articulation point
    if (parent == nullptr && children > 1) {
        res.insert(v->getInfo());  // Use getInfo() instead of getID()
    }

    // Pop vertices from the stack for the current connected component
    while (!s.empty() && s.top() != v->getInfo()) {  // Use getInfo() instead of getID()
        s.pop();
    }
}
