#include "graph.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>


bool Graph::disconnected(int u, int v) {
    // Percorrer a lista de adjacências do nó `u`
    for (const auto& edge : nodes[u].adj) {
        // Verificar se existe uma aresta com destino `v`
        if (edge.dest == v) {
            return false; // Aresta encontrada, nós estão conectados
        }
    }
    return true; // Aresta não encontrada, nós estão desconectados
}


vector<int> Graph::largestDegree() {
    vector<int> result;
    int maxDegree = 0;

    // Iterar sobre todos os nós do grafo
    for (int i = 1; i <= n; ++i) {  // Nós são numerados de 1 a n
        int degree = nodes[i].adj.size();  // O grau de um nó é o tamanho da lista de adjacências

        // Atualizar o grau máximo e o vetor de resultados
        if (degree > maxDegree) {
            maxDegree = degree;  // Atualizar grau máximo
            result.clear();      // Limpar nós previamente armazenados
            result.push_back(i); // Adicionar o nó atual
        } else if (degree == maxDegree) {
            result.push_back(i); // Adicionar nó ao vetor se tiver o mesmo grau máximo
        }
    }

    return result;
}


bool Graph::connected() {
    // Verificar se o grafo está vazio
    if (n == 0) return true;

    // Resetar o estado de todos os nós para "não visitado"
    for (int i = 1; i <= n; ++i) {
        nodes[i].visited = false;
    }

    // Realizar uma BFS a partir do primeiro nó
    int visitedCount = 0; // Contador de nós visitados
    std::queue<int> q;
    q.push(1); // Assumimos que os nós são numerados de 1 a n
    nodes[1].visited = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        visitedCount++;

        // Percorrer os vizinhos do nó atual
        for (const auto& edge : nodes[current].adj) {
            int neighbor = edge.dest;
            if (!nodes[neighbor].visited) {
                nodes[neighbor].visited = true;
                q.push(neighbor);
            }
        }
    }

    // Verificar se todos os nós foram visitados
    return (visitedCount == n);
}

int Graph::countNodes(int v, int k) {
    // Verificar se o nó está dentro do intervalo válido
    if (v < 1 || v > n) return 0;

    // Inicializar a distância de todos os nós como -1 (não visitado)
    std::vector<int> distances(n + 1, -1);
    distances[v] = 0; // A distância para o nó inicial é 0

    // Realizar BFS para calcular as distâncias
    std::queue<int> q;
    q.push(v);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Percorrer os vizinhos do nó atual
        for (const auto& edge : nodes[current].adj) {
            int neighbor = edge.dest;
            if (distances[neighbor] == -1) { // Se ainda não foi visitado
                distances[neighbor] = distances[current] + 1; // Atualizar distância
                q.push(neighbor);
            }
        }
    }

    // Contar os nós que estão a distância k
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (distances[i] == k) {
            count++;
        }
    }

    return count;
}


bool Graph::pathExists(int u, int v, const vector<int>& avoid) {
    // Criar um conjunto para os nós a evitar
    unordered_set<int> avoidSet(avoid.begin(), avoid.end());

    // Se os nós de origem ou destino estão na lista de nós a evitar, não há caminho
    if (avoidSet.count(u) || avoidSet.count(v)) {
        return false;
    }

    // Vetor para marcar nós visitados
    vector<bool> visited(n + 1, false);

    // Fila para BFS
    std::queue<int> q;
    q.push(u);
    visited[u] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Verificar se alcançamos o nó de destino
        if (current == v) {
            return true;
        }

        // Percorrer os vizinhos do nó atual
        for (const auto& edge : nodes[current].adj) {
            int neighbor = edge.dest;

            // Verificar se o vizinho está na lista de "evitar" ou já foi visitado
            if (avoidSet.count(neighbor) || visited[neighbor]) {
                continue;
            }

            // Marcar o vizinho como visitado e adicionar à fila
            visited[neighbor] = true;
            q.push(neighbor);
        }
    }

    // Se sairmos do loop sem encontrar o nó de destino, não há caminho
    return false;
}
