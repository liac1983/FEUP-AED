// -------------------------------------------------------------
// Algorithms and Data Structures 2024/2025 - LEIC (FCUP/FEUP)
// http://www.dcc.fc.up.pt/~pribeiro/aulas/aed2425/
// -------------------------------------------------------------
// Example of how to use the Graph class
// Last update: 24/11/2024
// -------------------------------------------------------------

#include "graph.h"

int main() {

  // Read a graph from standard input
  Graph *g = Graph::readGraph();
  
  // Print a DFS starting on node 1
  // (assumes nodes are unvisited before starting the DFS)
  std::cout << "DFS: ";
  g->dfs(1);
  std::cout << std::endl;

  // Print a BFS starting on node 1
  std::cout << "BFS: ";
  g->bfs(1);
  std::cout << std::endl;
  
  return 0;
}

