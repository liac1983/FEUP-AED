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

// CONTA O NUMERO DE COMPONENTES CONNECTADOS
int weightOutDegree(int v) {
    if (v < 1 || v > n) return 0;
    int totalWeight = 0;
    for (const auto& edge : nodes[v].adj) {
        totalWeight += edge.weight;
    }
    return totalWeight;
}

int nrConnectedComponents() {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false; // marca todos os nos como não viisitados
    }
    for (int i = 1; i <= 0; i++) { // itera pelos nos 
        if (!nodes[i].visited) { // se o nó não for visitado, inicia o dfs a partir dele
            count++;
            dfs5(i); // visita todos os nos conectados ao componente atual
        }
    }
    return count; // retorna o numero de componentes conectados
}

void dfs5(int v) {
    nodes[v].visited = true; //marca o nó atual como visitado
    for (auto e : nodes[v].adj) { // itera pelos vizinhos
        int w = e.dest; // obtém o odestinod o nó atual
        if (!nodes[w].visited) // verifica se o vizinho não foi visitados
            dfs5(w);
    }
}

// tamanho do maior componente conectado no grafo
int dfsCountNodes(int v) {
    nodes[v].visited = true; // marca os nós como visitados
    int count = 1; // começa a contagem no currente nó
    for (const auto& edge: nodes[v].adj) { // visita os visinhos
        int neighbor = edge.dest;
        if (!nodes[neighbor].visited) {
            count += dfsCountNodes(neighbor); // adiciona a contagem dos nos conectados 
        }
    }
    return count; // retorna o numero de componenetes conectados
}

int largestComponent() {
    // marca todos os nós como não visitados inicialmete
    for (int i = 1; i <= n; i++) {
        nodes[i].visited = false;
    }
    int largestSize = 0; // tamanho do maior componente
    for (int i = 1; i <= n; i++) { // itera por todos os nós 
        if (!nodes[i].visited) { // verifica se o nó ainda não foi visitado
            int componentSize = dfsCountNodes(i); // calcula o tamanho do componente conectado
            if (componentSize > largestSize) { // atualiza o tamanho do maior componente conectado
                largestSize = componentSize;
            }
        }
    }
    return largestSize;
}

// realiza a ordenação topologica de um grafo
void dfsTopological(int v, std::vector<bool>& visited, std::list<int>& order) {
    visited[v] = true; // marca o nó atual como visitado
    for (const auto& edge : nodes[v].adj) { // visita os seus visinhos
        int neighbor = edge.dest;
        if (!visited[neighbor]) {
            dfsTopological(neighbor, visited, order);
        }
    }
    // adiciona o nó à frente e depois os seus descendentes 
    order.push_front(v);
}

std::list<int> topologicalSorting() {
    std::vector<bool> visited(n+1, false); // procura os nós visitados no DFS
    std::list<int> order; // lista para guardar os nós ordenados topologicamente
    for (int i = 1; i <= n; i++) { // percorre o dfs pelos nós que ainda não foram visitados
        if (!visited[i]) {
            dfsTopological(i,visited, order);
        }
    }
    return order; // retorna os nós do grafos ordenados topologicamente
}

// deteta ciclos no grafo
bool dfsCycleDetection(int v, std::vector<int>& color) {
    color[v] = 1; // marca os nós vsistados a cinzento
    for (const auto& edge : nodes[v].adj) { // itera pelos nós visinhos 
        int neighbor = edge.dest; // nó seguinte 
        if (color[neighbor] == 1) {
            return true; // encontra um back edge (ciclo)
        }
        if (color[neighbor] == 0) {
            if (dfsCycleDetection(neighbor, color)) { // se o neighbor ainda não foi visitado verifica
                return true;
            }
        }
    } //marca os nós visitados a preto
    color[v] = 2;
    return false;
}

bool hasCycle() {
    std::vector<int> color(n+1, 0); // 0 não visitado, 1 atual, 2 visitado
    for (int i = 1; i <= n; i++) { // percorre o dfs por todos o s nós não visitados
        if (color[i] == 0) {
            if (dfsCycleDetection(i,color)) {
                return true; // deteta ciclos
            }
        }
    }
    return false; // não encontra nenhum ciclo
}

// biparity DFS
bool dfsCheckBipartite(int v, std::vector<int>& color, int currentColor) {
    color[v] = currentColor; // colorir o nó atual
    for (const auto& edge : nodes[v].adj) { // atravessa os visinhos
        int neighbor = edge.dest;
        if (color[neighbor] == 1) { // se o visinho não foi visitado, colorir da cor oposta
            if (!dfsCheckBipartite(neighbor, color, 1-currentColor)) {
                return false;
            }

        } else if (color[neighbor] == currentColor) { // se o visinho já foi visitado colorir da mesma cor e não é um grafo bipartido
            return false;
        }
    }
    return true;
}

bool isBipartite() {
    std::vector<int> color(n+1, -1); // -1 significa não visitado, 0 e 1 são duas cores
    for (int i = 1; i <= n; i++) { // começa o dfs pelos nós não visitados ( grafoconectado)
        if (color[i] == -1) {
            if (!dfsCheckBipartite(i,color, 0)) {
                return false; // se algum componente não é bipartido, o grafo também não é
            }
        }
    }
    return true; // caso contrario grafo bipartido 
}



};

#endif