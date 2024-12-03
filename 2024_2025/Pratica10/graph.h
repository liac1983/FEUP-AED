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
#include <stack>
#include <set>


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
    std::cout << v << " "; // show node order
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
  void bfs(int v) {
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
  }
  
  
  // --------------------------------------------------------------

  // ---------------------------------------------------------
  // TODO: put the functions you need to implement below this
  // ---------------------------------------------------------

    // ---------------------------------------------------------
  // New method: Find shortest distance between two nodes
  // ---------------------------------------------------------
  // Verifica se o grafo é conectado antes de calcular o diâmetro.
bool isConnected() {
    std::vector<bool> visited(n + 1, false);
    auto bfs = [&](int start) {
        std::queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto e : nodes[u].adj) {
                int v = e.dest;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    };

    // Inicia a BFS do primeiro nó válido.
    for (int i = 1; i <= n; i++) {
        if (!nodes[i].adj.empty()) {
            bfs(i);
            break;
        }
    }

    // Verifica se todos os nós foram visitados.
    for (int i = 1; i <= n; i++) {
        if (!nodes[i].adj.empty() && !visited[i]) return false;
    }

    return true;
}

  
  
  int distance(int a, int b) {
    if (!isConnected()) return -1;
    // Se o nó de origem for igual ao nó de destino
    if (a == b) return 0; // Distance to self is 0
    // vetor para armazenar a distancia de a para cada nó
    std::vector<int> dist(n + 1, -1); // Distance from 'a' to each node (-1 means not visited)
    std::queue<int> q; // queue para realizar a busca em largura (BFS), com os nós que precisam de ser processados 

    q.push(a); // nó de origem a
    dist[a] = 0; // distancia a 0, de a para a a distancia é 0

    while (!q.empty()) {
        // retira o proximo nó da fila para processar 
      int u = q.front();
      q.pop();
    // Itera por todos os vizinhos do nó atual u
      for (auto e : nodes[u].adj) {
        int v = e.dest; // obtem o nó vizinho (destino)
        if (dist[v] == -1) { // If not visited
          dist[v] = dist[u] + 1; // distancia do vizinho é a distancia do nó atual mais 1
          if (v == b) return dist[v]; // Early exit if we reach target
          q.push(v); // Adiciona o nó vizinho à fila para processar seus vizinhos no futuro
        }
      }
    }

    return -1; // If 'b' is not reachable from 'a'
  }

    int diameter() {
    // Vetor para verificar se um nó pertence a um componente conectado.
    // Inicialmente, nenhum nó foi visitado.
    std::vector<bool> visited(n + 1, false);

    // Função auxiliar para realizar a busca em largura (BFS) e calcular as distâncias
    // do nó inicial para todos os outros nós no componente conectado.
    auto bfs = [&](int start) -> std::vector<int> {
        // Vetor para armazenar as distâncias do nó inicial. 
        // Distâncias começam como -1 (indicando "não alcançável").
        std::vector<int> dist(n + 1, -1);
        std::queue<int> q; // Fila usada para a BFS.

        // Inicializa a BFS a partir do nó "start".
        q.push(start);
        dist[start] = 0; // Distância do nó inicial para ele mesmo é 0.

        while (!q.empty()) {
            int u = q.front(); // Remove o próximo nó da fila.
            q.pop();

            // Itera sobre todos os vizinhos do nó atual.
            for (auto e : nodes[u].adj) {
                int v = e.dest; // Nó vizinho.

                // Se o nó vizinho ainda não foi visitado (distância -1):
                if (dist[v] == -1) {
                    // Atualiza a distância do vizinho.
                    dist[v] = dist[u] + 1;

                    // Adiciona o vizinho à fila para explorar seus vizinhos no futuro.
                    q.push(v);
                }
            }
        }

        // Retorna o vetor de distâncias calculadas a partir do nó inicial.
        return dist;
    };

    int maxDiameter = 0; // Armazena o maior diâmetro encontrado.

    // Itera sobre todos os nós do grafo para calcular o diâmetro.
    for (int i = 1; i <= n; i++) {
        // Verifica se o nó atual já foi visitado como parte de outro componente conectado.
        if (!visited[i]) {
            // Realiza uma BFS a partir do nó atual e obtém as distâncias.
            std::vector<int> distFromI = bfs(i);

            // Marca todos os nós alcançáveis a partir do nó atual como visitados.
            for (int j = 1; j <= n; j++) {
                if (distFromI[j] != -1) visited[j] = true;
            }

            // Calcula a maior distância a partir do nó atual.
            int localMax = 0;
            for (int d : distFromI) {
                if (d == -1) continue; // Ignora nós que não são alcançáveis.
                localMax = std::max(localMax, d); // Atualiza a maior distância local.
            }

            // Atualiza o diâmetro máximo com a maior distância encontrada neste componente.
            maxDiameter = std::max(maxDiameter, localMax);
        }
    }

    // Verifica se existem componentes desconectados no grafo.
    for (int i = 1; i <= n; i++) {
        // Se algum nó ainda não foi visitado, o grafo possui mais de um componente.
        if (!visited[i]) return -1; // Retorna -1 se o grafo não for conectado.
    }

    // Retorna o maior diâmetro encontrado.
    return maxDiameter;
}

    // --------------------------------------------------------------
  // Strongly Connected Components (Tarjan's Algorithm)
  // --------------------------------------------------------------
  int countSCCs() {
    std::vector<int> low(n + 1, -1);       // Lowest reachable index
    std::vector<int> ids(n + 1, -1);      // Node IDs for discovery
    std::vector<bool> onStack(n + 1, false); // Nodes in current stack
    std::stack<int> stack;                // Stack for Tarjan's algorithm
    int sccCount = 0;                     // Count of strongly connected components
    int id = 0;                           // Current ID for nodes

    // Recursive function for Tarjan's algorithm
    auto dfs = [&](int u, auto&& dfs) -> void {
      stack.push(u);
      onStack[u] = true;
      ids[u] = low[u] = id++;
      
      for (const auto& edge : nodes[u].adj) {
        int v = edge.dest;
        if (ids[v] == -1) {  // Node v has not been visited
          dfs(v, dfs);
          low[u] = std::min(low[u], low[v]);
        } else if (onStack[v]) {  // Node v is in the current stack
          low[u] = std::min(low[u], ids[v]);
        }
      }

      // On finishing, if u is a root node of an SCC
      if (ids[u] == low[u]) {
        while (!stack.empty()) {
          int node = stack.top();
          stack.pop();
          onStack[node] = false;
          low[node] = ids[u]; // Assign the same component
          if (node == u) break;
        }
        sccCount++; // Increment the count of SCCs
      }
    };

    // Start Tarjan's algorithm for every node
    for (int i = 1; i <= n; i++) {
      if (ids[i] == -1) dfs(i, dfs);
    }

    return sccCount;
  }

    std::list<int> shortestPath(int a, int b) {
    std::vector<int> dist(n + 1, -1);       // Distância mínima de `a` para cada nó
    std::vector<int> pred(n + 1, -1);       // Predecessor de cada nó
    std::queue<int> q;                      // Fila para BFS

    // Inicializa a BFS
    q.push(a);
    dist[a] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const auto& edge : nodes[u].adj) {
            int v = edge.dest;

            // Verifica se encontramos um caminho mais curto ou lexicograficamente menor
            if (dist[v] == -1 || dist[v] > dist[u] + 1 || 
                (dist[v] == dist[u] + 1 && u < pred[v])) {
                dist[v] = dist[u] + 1;
                pred[v] = u;
                q.push(v);
            }
        }
    }

    // Se não há caminho até `b`, retorna lista vazia
    if (dist[b] == -1) return {};

    // Reconstrói o caminho de `b` para `a` usando os predecessores
    std::list<int> path;
    for (int at = b; at != -1; at = pred[at]) {
        path.push_front(at);
    }

    return path;
}

    std::set<std::set<int>> listSCCs() {
    std::vector<int> ids(n + 1, -1);       // ID de descoberta de cada nó
    std::vector<int> low(n + 1, -1);       // Menor ID alcançável
    std::vector<bool> onStack(n + 1, false); // Indica se um nó está na pilha
    std::stack<int> stack;                 // Pilha para o algoritmo
    int id = 0;                            // ID atual
    std::set<std::set<int>> sccs;          // Conjunto de SCCs para retornar

    // Função recursiva para Tarjan
    auto dfs = [&](int u, auto&& dfs) -> void {
        stack.push(u);
        onStack[u] = true;
        ids[u] = low[u] = id++;

        for (const auto& edge : nodes[u].adj) {
            int v = edge.dest;
            if (ids[v] == -1) {  // Se `v` ainda não foi visitado
                dfs(v, dfs);
                low[u] = std::min(low[u], low[v]);
            } else if (onStack[v]) {  // Se `v` está na pilha
                low[u] = std::min(low[u], ids[v]);
            }
        }

        // Identifica um SCC
        if (ids[u] == low[u]) {
            std::set<int> scc;
            while (true) {
                int node = stack.top();
                stack.pop();
                onStack[node] = false;
                scc.insert(node);
                if (node == u) break;
            }
            sccs.insert(scc);
        }
    };

    // Executa o algoritmo para todos os nós não visitados
    for (int i = 1; i <= n; ++i) {
        if (ids[i] == -1) {
            dfs(i, dfs);
        }
    }

    return sccs;
}

    std::set<int> articulationPoints() {
    std::vector<int> ids(n + 1, -1);  // ID for discovery time of each node
    std::vector<int> low(n + 1, -1);  // Lowest discovery time reachable from each node
    std::vector<bool> visited(n + 1, false);
    std::set<int> articulation;      // Set to store articulation points
    int id = 0, rootChildren = 0, root = 1;

    // Recursive function for DFS
    auto dfs = [&](int u, int parent, auto&& dfs) -> void {
        visited[u] = true;
        ids[u] = low[u] = id++;
        int children = 0;

        for (const auto& edge : nodes[u].adj) {
            int v = edge.dest;
            if (v == parent) continue;  // Skip the edge to the parent node

            if (!visited[v]) {
                children++;
                dfs(v, u, dfs);
                low[u] = std::min(low[u], low[v]);

                // Check articulation point condition for non-root nodes
                if (parent != -1 && low[v] >= ids[u]) {
                    articulation.insert(u);
                }
            } else {
                // Update low[u] for back edge
                low[u] = std::min(low[u], ids[v]);
            }
        }

        // Check articulation point condition for root nodes
        if (parent == -1 && children > 1) {
            articulation.insert(u);
        }
    };

    // Start DFS from the first node (assuming graph is connected)
    dfs(root, -1, dfs);

    return articulation;
}

  
};

#endif