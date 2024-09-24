#include "funWithGraphs.h"


//=============================================================================
// Exercise 2: Vertex degrees
//=============================================================================
// Subexercise 2.1: outDegree
//=============================================================================
//TODO
// funWithGraphs.cpp

#include "funWithGraphs.h"

int FunWithGraphs::outDegree(const Graph<int> g, const int &v) {
    // Find the vertex with the given content
    Vertex<int>* vertex = g.findVertex(v);

    // Check if the vertex exists
    if (vertex == nullptr) {
        // Node does not exist
        return -1;
    }

    // Return the out-degree of the vertex (size of the adjacency list)
    return vertex->getAdj().size();
}



//=============================================================================
// Subexercise 2.2: inDegree
//=============================================================================
//TODO
int FunWithGraphs::inDegree(const Graph<int> g, const int &v) {
    // Find the vertex with the given content
    Vertex<int>* vertex = g.findVertex(v);

    // Check if the vertex exists
    if (vertex == nullptr) {
        // Node does not exist
        return -1;
    }

    // Count the in-degree by checking the number of vertices with an edge to the given vertex
    int inDegree = 0;
    for (Vertex<int>* otherVertex : g.getVertexSet()) {
        for (const Edge<int>& edge : otherVertex->getAdj()) {
            if (edge.getDest() == vertex) {
                // Found an incoming edge to the given vertex
                inDegree++;
            }
        }
    }

    return inDegree;
}

//=============================================================================
// Subexercise 2.3: weightedOutDegree
//=============================================================================
// TODO
int FunWithGraphs::weightedOutDegree(const Graph<int> g, const int &v) {
    // Find the vertex with the given content
    Vertex<int>* vertex = g.findVertex(v);

    // Check if the vertex exists
    if (vertex == nullptr) {
        // Node does not exist
        return -1;
    }

    // Calculate the weighted out-degree by summing the weights of outgoing edges
    int weightedOutDegree = 0;
    for (const Edge<int>& edge : vertex->getAdj()) {
        weightedOutDegree += edge.getWeight();
    }

    return weightedOutDegree;
}

int FunWithGraphs::degree(const Graph<int> g, const int &v) {
    // Find the vertex with the given content
    Vertex<int>* vertex = g.findVertex(v);

    // Check if the vertex exists
    if (vertex == nullptr) {
        // Node does not exist
        return -1;
    }

    // Return the degree of the vertex (size of the adjacency list)
    return vertex->getAdj().size();
}

