// -------------------------------------------------------------
// Algorithms and Data Structures 2024/2025 - LEIC (FCUP/FEUP)
// http://www.dcc.fc.up.pt/~pribeiro/aulas/aed2425/
// -------------------------------------------------------------
// A simple lightweight graph class
// Last update: 24/11/2024
// -------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>

class Graph {
  struct Edge {
    int dest;   // Destination node 
    int weight; // An integer weight
  };
	
  struct Node {
    std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    bool visited;        // Has the node been visited in a graph traversal?
  };
	
  int n;                   // Graph size (vertices are numbered from 1 to n)
  bool hasDir;             // false: undirected; true: directed
  std::vector<Node> nodes; // The list of nodes being represented
	
public:  
  // Constructor: nr nodes and direction (default: undirected)
  Graph(int num, bool dir = false) : n(num), hasDir(dir), nodes(num+1) {}
  
  // Add edge from source to destination with a certain weight
  void addEdge(int src, int dest, int weight = 1) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
  }
  
  // --------------------------------------------------------------
  
  // Read a graph in the format:
  // nr_nodes directed/undirected weighted/unweighted
  // nr_edges
  // src_1 dest_1 <weight_1>
  // src_2 dest_2 <weight_2>
  // ...
  // src_n dest_n <weight_n>
  static Graph *readGraph() {
    int n;
    std::string sdirection, sweight;
    std::cin >> n >> sdirection >> sweight;  
    bool directed = (sdirection == "directed")?true:false;
    bool weighted = (sweight == "weighted")?true:false;
  
    Graph *g = new Graph(n, directed);
    int e;
    std::cin >> e;
    for (int i=0; i<e; i++) {
      int u, v, w = 1;
      std::cin >> u >> v;
      if (weighted) std::cin >> w;
      g->addEdge(u, v, w);
    }
    return g;
  }

  // --------------------------------------------------------------
  // Depth-First Search (DFS): example implementation
  // --------------------------------------------------------------
  void dfs(int v) {
    //std::cout << v << " "; // show node order
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
      int w = e.dest;
      if (!nodes[w].visited)
        dfs(w);
    }
  }
  
  // --------------------------------------------------------------
  // Breadth-First Search (BFS): example implementation
  // --------------------------------------------------------------
  /*void bfs(int v) {
    for (int i=1; i<=n; i++) nodes[i].visited = false;
    std::queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
      int u = q.front(); q.pop();      
      std::cout << u << " ";  // show node order
      for (auto e : nodes[u].adj) {
        int w = e.dest;
        if (!nodes[w].visited) {
          q.push(w);
          nodes[w].visited = true;
        }
      }
    }
  }*/
  
  
  // --------------------------------------------------------------

  // ---------------------------------------------------------
  // TODO: put the functions you need to implement below this
  // ---------------------------------------------------------


  // --------------------------------------------------------------
  // New method to calculate the outgoing degree of a node
  // --------------------------------------------------------------
  int outDegree(int v) { // Calcula o grau de saida de um nó
    if (v < 1 || v > n) return 0; // Check if node is valid
    return nodes[v].adj.size();   // Return size of adjacency list
  }
  
  // --------------------------------------------------------------
  // New method to calculate the weighted outgoing degree of a node
  // --------------------------------------------------------------
  int weightedOutDegree(int v) {
    if (v < 1 || v > n) return 0; // Check if node is valid
    int totalWeight = 0;
    for (const auto& edge : nodes[v].adj) {
      totalWeight += edge.weight; // Sum up the weights of the edges
    }
    return totalWeight;
  }
  // return the number of connected components of the graph
  int nrConnectedComponents() {
    // Marca todos os nós como não visitados
    int count = 0;
    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
    }

    // Itera por todos os nós
    for (int i = 1; i <= n; i++) {
        // Se o nó não foi visitado, inicia uma DFS a partir dele
        if (!nodes[i].visited) {
            count++;
            dfs5(i); // Visita todos os nós conectados ao componente atual
        }
    }

        return count; // Retorna o número de componentes conectados
  }

  // Retorna o numero de componentes connectados
  /*int nrConnectedComponents() {
    int count = 0;
    // marca todos os nós como não visitados
    for (int i = 1; i <= n; i++) {
      nodes[i].visited = false;
    }
    // Itera por todos os nós
    for (int i = 1; i <= n; i++) {
      // Se o nó foi visitado, inicia um dfs a partir dele
      if (!nodes[i].visited) {
        count++;
        dfs5(i); // visita todos os nós conectados ao componente atual
      }
    }
    return count;
  }*/

void dfs5(int v) {
    //std::cout << v << " "; // show node order
    nodes[v].visited = true; // Marca o nó atual como visitado e explora os seus vizinhos
    for (auto e : nodes[v].adj) { // iterar pelos vizinhos do nó
      int w = e.dest; // Obtém o destino do nó atual
      if (!nodes[w].visited) // Verificar se o nó de destino ainda não foi visitado
        dfs5(w); // Chama o DFS no nó de destino
    }
  }

/*void dfs5(int v) {
  // marca o nó atual como visitado
  nodes[v].visited = true; 
  // Itera por os nós vizinhos
  for (auto e : nodes[v].adj) {
    // obtém o destino do nó atual
    int w = e.dest;
    // Verifica se o nó de destino ainda não foi visitado
    if (!nodes[w].visited) {
      dfs5(w); // chama o dfs no nó de destino 
    }
  }
}*/

int dfsCountNodes(int v) {
    nodes[v].visited = true; // Mark the node as visited
    int count = 1; // Start count with the current node

    // Visit all neighbors
    for (const auto& edge : nodes[v].adj) {
        int neighbor = edge.dest;
        if (!nodes[neighbor].visited) {
            count += dfsCountNodes(neighbor); // Add count of nodes in the connected component
        }
    }

    return count; // Return the total count of nodes in this component
}

/*int dfsCountNodes(int v) {
  nodes[v].visited = true; // marca os nós como visitados
  int count = 1; // começa a contar o primeiro nó
  for (const auto& edge : nodes[v].adj) { // visita os nós adjacentes
    int neighbor = edge.dest; 
    if (!nodes[neighbor].visited) {
      count += dfsCountNodes(neighbor); // adiciona os nós à contagem
    }
  }
  return count; // Retorna o numero total de nós 
}*/

// Função para encontrar o tamanho do maior componente conectado num grafo
int largestComponent() {
    // Mark all nodes as unvisited initially
    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
    }
    // Tamanho do maior componente
    int largestSize = 0;

    // Iterate over all nodes
    for (int i = 1; i <= n; i++) {
      // Verififca se o nó aind anão foi visitado
        if (!nodes[i].visited) {
            // Calculate the size of the connected component
            int componentSize = dfsCountNodes(i);
            // Update the largest size if this component is larger
            if (componentSize > largestSize) {
                largestSize = componentSize;
            }
        }
    }

    return largestSize; // Return the size of the largest component
}

/*int largestComponent() {
  for (int i = 1; i <= n; i++) {
    nodes[i].visited = false; // marca todos os nós como não visitados inicialmenete
  }
  int largestSize = 0; // tamanho do maior componente
  for (int i = 1; i <= n; i++) { // itera pelos nós
    if (!nodes[i].visited) { // verifica se o nó ainda não foi visitado
      int componentSize = dfsCountNodes(i); // Calcula o tamanho dos componentes conectados
      if (componentSize > largestSize) {
        largestSize = componentSize; // atualiza o tamanho do maior componente
      }
    }
  }
  return largestSize; // Retorna o tamanho maximo de componentes conectados num grafo
}*/

void dfsTopological(int v, std::vector<bool>& visited, std::list<int>& order) {
    visited[v] = true; // Mark the current node as visited

    // Visit all neighbors
    for (const auto& edge : nodes[v].adj) {
        int neighbor = edge.dest;
        if (!visited[neighbor]) {
            dfsTopological(neighbor, visited, order);
        }
    }

    // Add the node to the front of the order after all its descendants
    order.push_front(v);
}

/*void dfsTopological(int v, std::vector<bool>& visited, std::list<int>&order) {
  visited[v] = true; // marca todos os nós como visitados
  for (const auto& edge : nodes[v].adj) { // visita os nós adjacentes
    int neighbor = edge.dest;
    if (!visited[neighbor]) {
      dfsTopological(neighbor, visited, order);
    }
  }
  order.push_front(v); // Adiciona o nó à frente da ordem e depois o seu descendente
}*/


// Função para realizar a ordenação topologica de um grafo orientado DAG
std::list<int> topologicalSorting() {
    std::vector<bool> visited(n + 1, false); // Track visited nodes DFS
    std::list<int> order; // List to store the topological order

    // Perform DFS for all nodes
    // cada no é considerado ponto inicial se aind anão foi visitado
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfsTopological(i, visited, order);
        }
    }

    return order; // Return the topological order
}

/*std::list<int> topologicalSorting() {
  std::vector<bool> visited(n+1, false); // conta os nós visitados
  std::list<int> order; // ordena topologicamente
  for (int i = 1; i <= n; i++) { // utiliza um dfs em todos os nós
    if (!visited[i]) { // os nós iniciais são os que ainda não foram visitados
      dfsTopological(i, visited, order);
    }
  }
  return order; // retorna os nós do grafos ordenados topologicamente
}*/

// Função para detectar ciclos em um grafo direcionado usando DFS.
bool dfsCycleDetection(int v, std::vector<int>& color) {
    color[v] = 1; // Mark the node as "visiting" (gray)
    // Itera sobre todos os vizinhos do nó atual.
    for (const auto& edge : nodes[v].adj) {
        int neighbor = edge.dest; // Obtém o nó vizinho.

        if (color[neighbor] == 1) {
            // Found a back edge indicating a cycle
            return true;
        }

        if (color[neighbor] == 0) {
            // If the neighbor is unvisited, recursively check it
            if (dfsCycleDetection(neighbor, color)) {
                return true;
            }
        }
    }

    color[v] = 2; // Mark the node as "visited" (black)
    return false;
}

/*bool dfsCycleDetection(int v, std::vector<int>& color) {
  color[v] = 1; //  marca o nó atual a cinzento
  for (const auto& edge : nodes[v].adj) { // itera por todos os nós vizinhos do atual
    int neighbor = edge.dest; // obtém o nó vizinho
    if (color[neighbor] == 1) return true; // encontra um ciclo
    if (color[neighbor] == 0) {
      if (dfsCycleDetection(neighbor, color)) { // verifica o nó vizinho
        return true;
      }
    }
  }
  color[v] = 2; // marca os nós visitados a preto
  return false;
}*/

bool hasCycle() {
    std::vector<int> color(n + 1, 0); // 0: unvisited, 1: visiting, 2: visited

    // Perform DFS from every unvisited node
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            if (dfsCycleDetection(i, color)) {
                return true; // Cycle detected
            }
        }
    }

    return false; // No cycles found
}

/*bool hasCycle() {
  std::vector<int> color(n+1, 0);
  for (int i = 1; i <= n; i++) { // corre o dfs em todos os nós não visitados
     if (dfsCycleDetection(i,color)) {
        return true; // deteta um ciclo
     }
  }
  return false; // não encontrou ciclos
}
*/

bool dfsCheckBipartite(int v, std::vector<int>& color, int currentColor) {
    color[v] = currentColor; // Color the current node

    // Traverse all neighbors
    for (const auto& edge : nodes[v].adj) {
        int neighbor = edge.dest;

        if (color[neighbor] == -1) {
            // If the neighbor is unvisited, color it with the opposite color
            if (!dfsCheckBipartite(neighbor, color, 1 - currentColor)) {
                return false; // Found a conflict
            }
        } else if (color[neighbor] == currentColor) {
            // If the neighbor is already colored with the same color, it's not bipartite
            return false;
        }
    }

    return true; // No conflicts found
}

/*bool dfsCheckBipartite(int v, std::vector<int>& color, int currentColor) {
  color[v] = currentColor; // colorir o nó atual
  for (const auto& edge : nodes[v].adj) { // atravessar os vizinhos
    int neighbor = edge.dest;
    if (color[neighbor] == -1) {
      // se o vizinho for não visitado, colorir com a cor oposta
      if (!dfsCheckBipartite(neighbor, color, 1-currentColor)) {
        return false;
      }
    } else if (color[neighbor] == currentColor) { // Se o vizinho já estiver colorido, não há biparity
      return false;
    }
  }
  return true; // Nenhum conflito encontrado
}*/

bool isBipartite() {
    std::vector<int> color(n + 1, -1); // -1 means unvisited; 0 and 1 are the two colors

    // Start the DFS from each unvisited node (though the graph is connected)
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            if (!dfsCheckBipartite(i, color, 0)) {
                return false; // If any component is not bipartite, the graph is not bipartite
            }
        }
    }

    return true; // The graph is bipartite
}

/*bool isBipartite() {
  std::vector<int> color(n+1,-1); // -1 significa não visitado, 0 e 1 são as duas cores
  for (int i = 1; i <= n; i++) { // começa o dfs por cada nó não visitado(grafo conectado)
    if (color[i] == -1) {
      if (!dfsCheckBipartite(i,color,0)) {
        return false; // se algum componente não for bipartite, o grafo é não bipartido
      }
    }
  }
  return true; // o grafo é bipartido 
}*/



  
};

#endif

