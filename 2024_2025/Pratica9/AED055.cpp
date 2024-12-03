#include <iostream>
#include <list>
#include "graph.h"

int main() {

  // Number of graphs to test
  int n;
  std::cin >> n;

  // For each graph: read, call the method and delete graph at the end
  for (int i=1; i<=n; i++) {
    Graph *g = Graph::readGraph();
    std::cout << "Graph #" << i << ": isBipartite() = " << (g->isBipartite()?"true":"false") << std::endl;
    delete g;
  }
    
  return 0;
}
