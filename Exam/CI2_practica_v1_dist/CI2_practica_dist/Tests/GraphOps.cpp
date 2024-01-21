// ------------------------------------------------------------

#include <cstddef>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#include "Graph.h"
#include "GraphOps.h"

// ------------------------------------------------------------
bool GraphOps::isDAG(Graph<int> g) {

    // Set to store visited vertices during DFS
    unordered_set<Vertex<int>*> visited;

    // Set to store vertices in the current DFS traversal
    unordered_set<Vertex<int>*> currentTraversal;

    // Perform DFS for each vertex in the graph
    for (Vertex<int> *vertex : g.getVertexSet()) {
        if (visited.find(vertex) == visited.end()) {
            if (!dfsIsDAG(vertex, visited, currentTraversal)) {
                // If a cycle is detected, the graph is not a DAG
                return false;
            }
        }
    }

    // If DFS traversal completes for all vertices without detecting a cycle, the graph is a DAG
    return true;
}

// Helper function for DFS traversal to detect cycles
bool GraphOps::dfsIsDAG(Vertex<int> *v, unordered_set<Vertex<int>*> &visited, unordered_set<Vertex<int>*> &currentTraversal) {
    visited.insert(v);
    currentTraversal.insert(v);

    for (const Edge<int> &edge : v->getAdj()) {
        Vertex<int> *w = edge.getDest();

        // If the neighbor is in the current traversal set, there is a cycle
        if (currentTraversal.find(w) != currentTraversal.end()) {
            return false;
        }

        // If the neighbor is not visited, perform DFS on it
        if (visited.find(w) == visited.end()) {
            if (!dfsIsDAG(w, visited, currentTraversal)) {
                return false;
            }
        }
    }

    // Remove the vertex from the current traversal set when backtracking
    currentTraversal.erase(v);

    return true;
}

// ------------------------------------------------------------
bool GraphOps::directlyUnconnected(Graph<int> g, int u, int v){

    // Find vertices with info fields u and v
    Vertex<int> *vertexU = g.findVertex(u);
    Vertex<int> *vertexV = g.findVertex(v);

    // If either of the vertices doesn't exist, return true
    if (vertexU == nullptr || vertexV == nullptr) {
        return true;
    }

    // Check if there is a direct edge from u to v
    for (const Edge<int> &edge : vertexU->getAdj()) {
        if (edge.getDest() == vertexV) {
            // There is a direct edge from u to v
            return false;
        }
    }

  return true;
}

// ------------------------------------------------------------
vector<int> GraphOps::largestOutDegree(Graph<int> g){
    unordered_map<int, int> outDegreeMap; // Map to store out-degrees

    // Calculate out-degrees for each vertex
    for (Vertex<int> *vertex : g.getVertexSet()) {
        outDegreeMap[vertex->getInfo()] = vertex->getAdj().size();
    }

    // Find the maximum out-degree
    int maxOutDegree = 0;
    for (const auto &entry : outDegreeMap) {
        maxOutDegree = max(maxOutDegree, entry.second);
    }

    // Collect vertices with the maximum out-degree
    vector<int> result;
    for (const auto &entry : outDegreeMap) {
        if (entry.second == maxOutDegree) {
            result.push_back(entry.first);
        }
    }

    return result;
}

// ---------------------------------------------------------------------
vector<int> GraphOps::numberSourcesSinks(Graph<int> g){
    vector<int> result(2, 0); // Initialize result vector with zeros

    // Count the number of incoming and outgoing edges for each vertex
    unordered_map<int, int> inDegreeMap;
    unordered_map<int, int> outDegreeMap;

    for (Vertex<int> *vertex : g.getVertexSet()) {
        for (const Edge<int> &edge : vertex->getAdj()) {
            // Increment out-degree for the source vertex
            outDegreeMap[vertex->getInfo()]++;

            // Increment in-degree for the destination vertex
            inDegreeMap[edge.getDest()->getInfo()]++;
        }
    }

    // Count the number of source nodes (nodes with zero in-degree)
    for (const auto &entry : outDegreeMap) {
        if (inDegreeMap.find(entry.first) == inDegreeMap.end() || inDegreeMap[entry.first] == 0) {
            result[0]++;
        }
    }

    // Count the number of sink nodes (nodes with zero out-degree)
    for (const auto &entry : inDegreeMap) {
        if (outDegreeMap.find(entry.first) == outDegreeMap.end() || outDegreeMap[entry.first] == 0) {
            result[1]++;
        }
    }

    return result;
}

// ---------------------------------------------------------------------
int GraphOps::numberConnectedComponents(Graph<int> g){
    int numComponents = 0; // Initialize the number of connected components

    // Set to store visited vertices during DFS
    unordered_set<Vertex<int>*> visited;

    // Perform DFS for each vertex in the graph
    for (Vertex<int>* vertex : g.getVertexSet()) {
        if (visited.find(vertex) == visited.end()) {
            // Start a new DFS traversal for a new connected component
            dfsConnectedComponents(vertex, visited);
            numComponents++;
        }
    }

    return numComponents;
}

// Helper function for DFS traversal to count connected components
void GraphOps::dfsConnectedComponents(Vertex<int>* current, unordered_set<Vertex<int>*>& visited) {
    // Mark the current vertex as visited
    visited.insert(current);

    // Iterate through adjacent vertices
    for (const Edge<int>& edge : current->getAdj()) {
        Vertex<int>* neighbor = edge.getDest();

        // If the neighbor is not visited, perform DFS on it
        if (visited.find(neighbor) == visited.end()) {
            dfsConnectedComponents(neighbor, visited);
        }
    }
}

// ---------------------------------------------------------------------
bool GraphOps::pathExists(Graph<int> g, int s, int t, vector<int> skip){

    // Set to store visited vertices during DFS
    unordered_set<Vertex<int>*> visited;

    // Perform DFS to find a path from s to t while avoiding nodes in skip
    return dfsPathExists(g.findVertex(s), g.findVertex(t), skip, visited);
}

// Helper function for DFS traversal to check if a path exists
bool GraphOps::dfsPathExists(Vertex<int> *current, Vertex<int> *target, const vector<int> &skip, unordered_set<Vertex<int>*> &visited) {
    // Mark the current vertex as visited
    visited.insert(current);

    // If the current vertex is the target, a path is found
    if (current == target) {
        return true;
    }

    // Iterate through adjacent vertices
    for (const Edge<int> &edge : current->getAdj()) {
        Vertex<int> *neighbor = edge.getDest();

        // Skip vertices specified in the skip vector
        if (find(skip.begin(), skip.end(), neighbor->getInfo()) != skip.end()) {
            continue;
        }

        // If the neighbor is not visited, perform DFS on it
        if (visited.find(neighbor) == visited.end()) {
            if (dfsPathExists(neighbor, target, skip, visited)) {
                return true; // Path found
            }
        }
    }

    return false; // No path found
}
