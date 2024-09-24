//
// Created by lara2 on 12/12/2023.
//

#include "graph.h"

graph::graph(int nodes, bool dir) : n(nodes), hasDir(dir), nodes(nodes + 1) {}

void graph::addEdge(int src, int dest, int weight) {
    if (src < 1 || dest < 1 || src > n || dest > n) {
        // Verifica se os índices são válidos
        cerr << "Erro: índices inválidos para addEdge." << endl;
        return;
    }

    Edge newEdge;
    newEdge.dest = dest;
    newEdge.weight = weight;

    nodes[src].adj.push_back(newEdge);

    if (!hasDir && src != dest) {
        // Se o grafo for não direcionado, adiciona também uma aresta no sentido contrário
        Edge reverseEdge;
        reverseEdge.dest = src;
        reverseEdge.weight = weight;
        nodes[dest].adj.push_back(reverseEdge);
    }
}

void graph::dfs(int v) {
    // Implementação básica de DFS (Depth-First Search)
    // Aqui, a função apenas imprime o número do nó durante a travessia.

    if (v < 1 || v > n) {
        cerr << "Erro: índice inválido para dfs." << endl;
        return;
    }

    nodes[v].visited = true;
    cout << v << " ";

    for (const auto &edge : nodes[v].adj) {
        if (!nodes[edge.dest].visited) {
            dfs(edge.dest);
        }
    }
}

void graph::bfs(int v) {
    // Implementação básica de BFS (Breadth-First Search)
    // Aqui, a função apenas imprime o número do nó durante a travessia.

    if (v < 1 || v > n) {
        cerr << "Erro: índice inválido para bfs." << endl;
        return;
    }

    queue<int> q;
    q.push(v);
    nodes[v].visited = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << current << " ";

        for (const auto &edge : nodes[current].adj) {
            if (!nodes[edge.dest].visited) {
                q.push(edge.dest);
                nodes[edge.dest].visited = true;
            }
        }
    }
}

bool graph::disconnected(int u, int v) {
    if (u < 1 || v < 1 || u > n || v > n) {
        // Verifica se os índices são válidos
        return true;
    }

    for (const auto &edge : nodes[u].adj) {
        // Procura por uma aresta do nó u para o nó v
        if (edge.dest == v) {
            return false; // Aresta encontrada
        }
    }

    return true; // Nenhuma aresta encontrada
}

vector<int> graph::largestDegree() {
    if (hasDir) {
        cerr << "Erro: Função chamada para grafo dirigido." << endl;
        return vector<int>();
    }

    int maxDegree = 0;
    vector<int> result;

    for (int i = 1; i <= n; ++i) {
        int degree = 0;

        for (const auto &edge : nodes[i].adj) {
            // Conta as arestas de entrada e saída
            if (!hasDir || (hasDir && edge.dest >= i)) {
                ++degree;
            }
        }

        if (degree > maxDegree) {
            // Encontrou um novo máximo
            maxDegree = degree;
            result.clear(); // Limpa o vetor resultante
            result.push_back(i);
        } else if (degree == maxDegree) {
            // Adiciona ao vetor resultante
            result.push_back(i);
        }
    }

    return result;
}

bool graph::connected() {
    // Verifica se o grafo é conexo usando uma busca em largura (BFS)
    if (n < 1) {
        cerr << "Erro: grafo vazio." << endl;
        return false;
    }

    // Marca todos os nós como não visitados
    for (int i = 1; i <= n; ++i) {
        nodes[i].visited = false;
    }

    // Inicia a busca em largura a partir do primeiro nó
    bfs(1);

    // Verifica se todos os nós foram visitados durante a BFS
    for (int i = 1; i <= n; ++i) {
        if (!nodes[i].visited) {
            return false; // Encontrou um componente não visitado
        }
    }

    return true; // Todos os nós foram visitados, o grafo é conexo
}

int graph::countNodes(int v, int k) {
    // Função para contar a quantidade de nós a uma certa distância do nó v
    if (v < 1 || v > n || k < 0) {
        cerr << "Erro: índices inválidos para countNodes." << endl;
        return -1;
    }

    // Marca todos os nós como não visitados
    for (int i = 1; i <= n; ++i) {
        nodes[i].visited = false;
    }

    // Fila para a busca em largura (BFS)
    queue<pair<int, int>> q;  // Alteração: a fila agora armazena o nó e a distância até ele

    // Inicializa a fila com o nó inicial e a distância 0
    q.push({v, 0});
    nodes[v].visited = true;

    // Armazena a quantidade de nós na distância k
    int count = 0;

    // Realiza a busca em largura
    while (!q.empty()) {
        int current = q.front().first;
        int distance = q.front().second;
        q.pop();

        // Se a distância é igual a k, incrementa o contador
        if (distance == k) {
            ++count;
        }

        // Se a distância é maior que k, interrompe a busca
        if (distance > k) {
            break;
        }

        for (const auto &edge : nodes[current].adj) {
            if (!nodes[edge.dest].visited) {
                q.push({edge.dest, distance + 1});
                nodes[edge.dest].visited = true;
            }
        }
    }

    return count;
}

bool graph::pathExists(int u, int v, const vector<int> &avoid) {
    // Função para verificar se existe um caminho entre os nós u e v,
    // evitando os nós indicados no vetor avoid

    if (u < 1 || u > n || v < 1 || v > n) {
        cerr << "Erro: índices inválidos para pathExists." << endl;
        return false;
    }

    // Marca todos os nós como não visitados
    for (int i = 1; i <= n; ++i) {
        nodes[i].visited = false;
    }

    // Fila para a busca em largura (BFS)
    queue<int> q;

    // Inicializa a fila com o nó inicial
    q.push(u);
    nodes[u].visited = true;

    // Realiza a busca em largura
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Verifica se chegou ao nó de destino
        if (current == v) {
            return true;
        }

        for (const auto &edge : nodes[current].adj) {
            int dest = edge.dest;

            // Verifica se o nó de destino não está na lista de nós a evitar
            if (!nodes[dest].visited && find(avoid.begin(), avoid.end(), dest) == avoid.end()) {
                q.push(dest);
                nodes[dest].visited = true;
            }
        }
    }

    // Não encontrou um caminho entre u e v
    return false;
}


class FunWithGraphs {
public:
    static graph graph1() {
        graph g(4);
        g.addEdge(1, 2);
        g.addEdge(3, 1);
        return g;
    }

    static graph graph4() {
        graph g(4);
        g.addEdge(2, 4);
        return g;
    }
};

int main() {
    // Adicione seus testes aqui
    /*graph g(4);
    g.addEdge(1, 2);
    g.addEdge(3, 1);

    // Teste da função disconnected
    cout << g.disconnected(1, 2) << endl; // Deve imprimir 0
    cout << g.disconnected(1, 4) << endl; // Deve imprimir 1
    cout << g.disconnected(3, 1) << endl; // Deve imprimir 0

    // Testes ex 1
    graph g1 = FunWithGraphs::graph1();
    cout << g1.disconnected(1, 2) << endl; // Deve imprimir 0
    cout << g1.disconnected(1, 4) << endl; // Deve imprimir 1

    graph g4 = FunWithGraphs::graph4();
    cout << g4.disconnected(2, 4) << endl; // Deve imprimir 0
    cout << g4.disconnected(4, 2) << endl; // Deve imprimir 1

    // Testes ex 2
    graph g1 = FunWithGraphs::graph1();
    auto v1 = g1.largestDegree();
    cout << "Graph 1 Largest Degree Nodes: ";
    for (auto v : v1) {
        cout << v << " ";
    }
    cout << endl;

    graph g2 = FunWithGraphs::graph4();
    auto v2 = g2.largestDegree();
    cout << "Graph 2 Largest Degree Nodes: ";
    for (auto v : v2) {
        cout << v << " ";
    }
    cout << endl;

    graph g1 = FunWithGraphs::graph1();
    cout << g1.connected() << endl; // Deve imprimir 1

    // Testes para a função countNodes
    graph g1 = FunWithGraphs::graph1();
    cout << g1.countNodes(5, 1) << endl; // Deve imprimir 3
    cout << g1.countNodes(6, 2) << endl; // Deve imprimir 2
    cout << g1.countNodes(1, 3) << endl; // Deve imprimir 1*/

    graph g1 = FunWithGraphs::graph1();

    cout << g1.pathExists(1, 5, {2}) << endl;  // Deve imprimir 1
    cout << g1.pathExists(1, 5, {2, 3}) << endl;  // Deve imprimir 0
    cout << g1.pathExists(2, 6, {4}) << endl;  // Deve imprimir 0
    cout << g1.pathExists(2, 6, {9, 8}) << endl;  // Deve imprimir 1

    return 0;
}
