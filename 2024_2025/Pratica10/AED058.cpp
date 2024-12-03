#include <iostream>
#include "graph.h"

int main() {

  // Read one input graph
  Graph *g = Graph::readGraph();

  // read q pairs of integers to indicate the queries
  int q;
  std::cin >> q;
  for (int i=0; i<q; i++) {
    int a, b;
    std::cin >> a >> b;
    std::cout << "g->distance(" << a << "," << b << ") = " << g->distance(a,b) << std::endl;    
  }
  
  delete g;
  
  return 0;
}
