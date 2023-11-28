#include "funWithDFS.h"


//=============================================================================
// Exercise 2.1: Nodes at distance k
//=============================================================================
// Subexercise 2.1.1: Nodes at distance k (DFS)
//=============================================================================
// TODO
void nodesAtDistanceDFSVisit(const Graph<Person> *g, Vertex<Person> *v, int k, vector<Person> &res);
vector<Person> FunWithDFS::nodesAtDistanceDFS(const Graph<Person> *g, const Person &source, int k) {
    vector<Person> res;

    // Find the vertex corresponding to the source person
    Vertex<Person> *sourceVertex = g->findVertex(source);

    // Check if the source vertex exists and perform DFS
    if (sourceVertex != nullptr) {
        nodesAtDistanceDFSVisit(g, sourceVertex, k, res);
    }

    return res;
}

// TODO
void nodesAtDistanceDFSVisit(const Graph<Person> *g, Vertex<Person> *v, int k, vector<Person> &res) {
    if (k == 0) {
        res.push_back(v->getData()); // Add the person at distance k to the result
        return;
    }

    v->setVisited(true);

    for (auto neighbor : v->getNeighbors()) {
        if (!neighbor.first->isVisited()) {
            nodesAtDistanceDFSVisit(g, neighbor.first, k - 1, res);
        }
    }

    v->setVisited(false); // Reset the visited status after exploring neighbors
}


//=============================================================================
// Exercise 2.3: Directed Acyclic Graph
//=============================================================================
// TODO
bool dfsIsDAG(Vertex<int> *v);
bool FunWithDFS::isDAG(Graph<int> g) {
    return false;
}

// TODO
bool dfsIsDAG(Vertex<int> *v) {
    return false;
}

