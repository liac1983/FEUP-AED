#include "funWithBFS.h"


//=============================================================================
// Exercise 2.1: Nodes at distance k
//=============================================================================
// Subexercise 2.1.2: Nodes at distance k (BFS)
//=============================================================================
// TODO
vector<Person> FunWithBFS::nodesAtDistanceBFS(const Graph<Person> *g, const Person &source, int k) {
    vector<Person> res;

    // Find the vertex corresponding to the source person
    Vertex<Person> *sourceVertex = g->findVertex(source);

    // Check if the source vertex exists
    if (sourceVertex == nullptr) {
        return res; // Return an empty vector if source vertex doesn't exist
    }

    queue<pair<Vertex<Person>*, int>> bfsQueue; // Pair of vertex and its distance from the source
    bfsQueue.push({sourceVertex, 0});

    while (!bfsQueue.empty()) {
        auto current = bfsQueue.front();
        bfsQueue.pop();

        Vertex<Person> *currentVertex = current.first;
        int distance = current.second;

        if (distance == k) {
            res.push_back(currentVertex->getData());
        } else if (distance > k) {
            break; // We have reached the required distance, no need to explore further
        }

        currentVertex->setVisited(true);

        for (auto neighbor : currentVertex->getNeighbors()) {
            if (!neighbor.first->isVisited()) {
                bfsQueue.push({neighbor.first, distance + 1});
            }
        }
    }

    return res;
}

//=============================================================================
// Exercise 2.2: Max New Children
//=============================================================================
// TODO
int FunWithBFS::maxNewChildren(const Graph<Person> *g, const Person &source, Person &info) {
    // Find the vertex corresponding to the source person
    Vertex<Person> *sourceVertex = g->findVertex(source);

    // Check if the source vertex exists
    if (sourceVertex == nullptr) {
        return 0; // Return 0 if source vertex doesn't exist
    }

    queue<Vertex<Person>*> bfsQueue;
    bfsQueue.push(sourceVertex);

    int maxChildren = 0;

    while (!bfsQueue.empty()) {
        Vertex<Person> *currentVertex = bfsQueue.front();
        bfsQueue.pop();

        currentVertex->setVisited(true);

        int newChildren = 0;

        for (auto neighbor : currentVertex->getNeighbors()) {
            if (!neighbor.first->isVisited()) {
                bfsQueue.push(neighbor.first);
                newChildren++;
            }
        }

        if (newChildren > maxChildren) {
            maxChildren = newChildren;
            info = currentVertex->getData();
        }
    }

    // Reset visited status after BFS
    for (auto vertex : g->getAllVertices()) {
        vertex->setVisited(false);
    }

    return maxChildren;
}
