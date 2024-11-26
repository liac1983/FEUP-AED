#include <iostream>
#include "graph.h"

int main() {

  // Read one input graph
  Graph *g = Graph::readGraph();

  // read q integer indicating nodes to ask for outDegree
  int q;
  std::cin >> q;
  for (int i=0; i<q; i++) {
    int x;
    std::cin >> x;
    std::cout << "g->weightedOutDegree(" << x << ") = " << g->weightedOutDegree(x) << std::endl;    
  }
  
  delete g;
  
  return 0;
}

