// ------------------------------------------------------------

#include <cstddef>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#include "Graph.h"

class GraphOps {
public:
  static bool directlyUnconnected(Graph<int> g, int u, int v);
  static vector<int> largestOutDegree(Graph<int> g);
  static bool isDAG(Graph<int> g);
  static bool dfsIsDAG(Vertex<int> *v, unordered_set<Vertex<int>*> &visited, unordered_set<Vertex<int>*> &currentTraversal);
  static vector<int> numberSourcesSinks(Graph<int> g);
  static bool pathExists(Graph<int> g, int s, int t, vector<int> skip);
  static int numberConnectedComponents(Graph<int> g);
  static void dfsConnectedComponents(Vertex<int>* current, unordered_set<Vertex<int>*>& visited);
  static bool dfsPathExists(Vertex<int> *current, Vertex<int> *target, const vector<int> &skip, unordered_set<Vertex<int>*> &visited);
};

// ------------------------------------------------------------
