#include <iostream>
#include "graph.h"

int main() {

  // Read one input graph
  Graph *g = Graph::readGraph();

  // Lê o numero de pares de consulta a serem processados 
  int q;
  std::cin >> q; // Ususario informa o numero de ocnsultas
  for (int i=0; i<q; i++) {
    int a, b;
    // Lê dois inteiros que representam os vertices para os quais queremos encontrar o caminho mais curto
    std::cin >> a >> b;
    // Mostra o prefixo da saida para a consulta
    std::cout << "g->shortestPath(" << a << "," << b << ") =";
    // Chama o metodo shortestPath para encontrar o caminho mais curto entre os vertices a e b
    std::list<int> path = g->shortestPath(a,b);
    // Verifica se o caminhos retornado está vazio (não há mais caminho entre os vertices)
    if (path.size() == 0) std::cout << " EMPTY";
    // Itera pelo caminhos retornando e imprime os vertices 
    else for (int v : path) std::cout << " " << v;
    // Finaliza a linha de saida para a consulta
    std::cout << std::endl;
  }
  // Liberta a memoria alocada para o grafo
  delete g;
  
  return 0;
}
