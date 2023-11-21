/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cstddef>
#include <vector>
#include <queue>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field
    bool processing;       // auxiliary field

    void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);
    friend class Graph<T>;
};

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    double getWeight() const;
    void setWeight(double weight);
    friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    int inDegree(const T &v) const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}

template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}

template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

template<class T>
double Edge<T>::getWeight() const {
    return weight;
}

template<class T>
void Edge<T>::setWeight(double weight) {
    Edge::weight = weight;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}


//=============================================================================
// Exercise 1: Graph implementation
//=============================================================================
// Subexercise 1.1: addVertex
//=============================================================================
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
//TODO
template <class T>
bool Graph<T>::addVertex(const T &in) {
    // Check if the vertex already exists
    if (findVertex(in) != nullptr) {
        // Vertex with the same content already exists
        return false;
    }

    // If not, create a new vertex and add it to the graph
    Vertex<T>* newVertex = new Vertex<T>{in};
    vertexSet.push_back(newVertex);

    return true;
}


//=============================================================================
// Subexercise 1.2: addEdge
//=============================================================================
/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
//TODO
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    // Use findVertex to obtain pointers to the source and destination vertices
    Vertex<T>* sourceVertex = findVertex(sourc);
    Vertex<T>* destVertex = findVertex(dest);

    // Check if both source and destination vertices exist
    if (sourceVertex == nullptr || destVertex == nullptr) {
        // One or both of the vertices do not exist
        return false;
    }

    // Add the edge to the source vertex
    sourceVertex->addEdge(destVertex, w);

    return true;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    // Create a new edge with the given destination vertex and weight
    Edge<T> newEdge(d, w);

    // Add the edge to the adj vector of the current vertex
    adj.push_back(newEdge);
}

//=============================================================================
// Subexercise 1.3: removeEdge
//=============================================================================
/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
//TODO
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    // Use findVertex to obtain pointers to the source and destination vertices
    Vertex<T>* sourceVertex = findVertex(sourc);
    Vertex<T>* destVertex = findVertex(dest);

    // Check if both source and destination vertices exist
    if (sourceVertex == nullptr || destVertex == nullptr) {
        // One or both of the vertices do not exist
        return false;
    }

    // Remove the edge from the source vertex
    return sourceVertex->removeEdgeTo(destVertex);
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    // Use an iterator to scan the "adj" vector and erase the edge if found
    for (auto it = adj.begin(); it != adj.end(); ++it) {
        if (it->dest == d) {
            adj.erase(it);
            return true; // Edge successfully removed
        }
    }

    return false; // Edge does not exist
}


//=============================================================================
// Subexercise 1.4: removeVertex
//=============================================================================
/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
//TODO
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    // Find the vertex with the given content
    auto it = find_if(vertexSet.begin(), vertexSet.end(),
                      [&](Vertex<T>* vertex) { return vertex->getInfo() == in; });

    // Check if the vertex with the given content was found
    if (it == vertexSet.end()) {
        // Vertex does not exist
        return false;
    }

    // Remove outgoing edges from the vertex
    for (auto edgeIt = (*it)->getAdj().begin(); edgeIt != (*it)->getAdj().end(); ++edgeIt) {
        // Remove the edge from the destination vertex (incoming edge)
        edgeIt->getDest()->removeEdgeTo(*it);
    }

    // Erase the vertex from the vertexSet
    delete *it;
    vertexSet.erase(it);

    return true;
}


#endif /* GRAPH_H_ */



