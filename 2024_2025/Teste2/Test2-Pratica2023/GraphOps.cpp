#include "GraphOps.h"
#include "Graph.h"
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

bool GraphOps::directlyUnconnected(Graph<int> g, int u, int v) {
    // Encontra o vertice u e v no grafo
    Vertex<int>* vertexU = g.findVertex(u);
    Vertex<int>* vertexV = g.findVertex(v);

    // Se ambos os vertices não existirem retorna true
    if (!vertexU || !vertexV) {
        return true;
    }

    // Verifica se é um direct edge de u até v
    for (const auto& edge : vertexU->getAdj()) {
        if (edge.getDest() == vertexV) {
            return false; // O Edge existe, então o grafo é directly connected
        }
    }

    // Se o edge não for encontrado, retorna true
    return true;
}

vector<int> GraphOps::largestOutDegree(Graph<int> g) {
    vector<int> result;
    int maxDegree = 0;

    // Itera por todos os vértices no grafo
    for (auto vertex : g.getVertexSet()) {
        int outDegree = vertex->getAdj().size(); // O grau de saída é o tamanho da lista de adjacências

        // Atualiza o maxDegree e reseta o resultado se a maior degree for encontrada
        if (outDegree > maxDegree) {
            maxDegree = outDegree;
            result.clear();
            result.push_back(vertex->getInfo());
        }
        // Se o degree for igual ao maxDegree, adiciona o vértice ao resultado
        else if (outDegree == maxDegree) {
            result.push_back(vertex->getInfo());
        }
    }

    return result;
}

bool GraphOps::isDAG(Graph<int> g) {
    // Dá reset a todos os vertices visitados e processa os estados
    for (auto vertex : g.getVertexSet()) {
        vertex->setVisited(false);
        vertex->setProcessing(false);
    }

    // Função auxiliar para o DFS detetar ciclos
    auto dfsCycleCheck = [](Vertex<int>* v, auto& dfsCycleCheckRef) -> bool {
        v->setProcessing(true);  // Marca o vértice no inicio do processo
        v->setVisited(true);     // Marca o vértice como visitado

        // Vertfica todos os vértices adjacentes
        for (const auto& edge : v->getAdj()) {
            auto neighbor = edge.getDest();
            if (neighbor->isProcessing()) {
                // Se o vizinho for processado, ele encontra um ciclo
                return true;
            }
            if (!neighbor->isVisited()) {
                // Corre o DFS nos vertices visinhos que ainda não foram visitados
                if (dfsCycleCheckRef(neighbor, dfsCycleCheckRef)) {
                    return true;  // ciclo para detetar recursão
                }
            }
        }

        v->setProcessing(false);  // Marca o processo como feito para estes vertices
        return false;
    };

    // Verifica se todos os vertices estão presentes no ciclo
    for (auto vertex : g.getVertexSet()) {
        if (!vertex->isVisited()) {
            if (dfsCycleCheck(vertex, dfsCycleCheck)) {
                return false;  // O ciclo é detetado
            }
        }
    }

    return true;  // Não foram encontrados ciclos
}

vector<int> GraphOps::numberSourcesSinks(Graph<int> g) {
    int sourceCount = 0, sinkCount = 0;

    // cria um mapa para analisar in-degrees para cada vértice
    unordered_map<int, int> inDegree;
    for (auto vertex : g.getVertexSet()) {
        inDegree[vertex->getInfo()] = 0;
    }

    // Conta in-degrees iterando por todos os edges
    for (auto vertex : g.getVertexSet()) {
        for (const auto& edge : vertex->getAdj()) {
            inDegree[edge.getDest()->getInfo()]++;
        }
    }

    // Itera pelos vértices até encontrar o souce and sink
    for (auto vertex : g.getVertexSet()) {
        int outDegree = vertex->getAdj().size(); // Out-degree é o tamanho da lista de adjacencia
        int info = vertex->getInfo();

        if (inDegree[info] == 0) {
            sourceCount++; // No incoming edges, this is a source
        }
        if (outDegree == 0) {
            sinkCount++; // No outgoing edges, this is a sink
        }
    }

    return {sourceCount, sinkCount};
}


bool GraphOps::pathExists(Graph<int> g, int s, int t, const vector<int>& skip) {
    // Converter o skip vector num set para maior eficiencia
    unordered_set<int> skipSet(skip.begin(), skip.end());

    // Se a origem ou o destino estiver na lista, retornar falso 
    if (skipSet.count(s) || skipSet.count(t)) {
        return false;
    }

    // encontrar a source e o target vertices
    Vertex<int>* source = g.findVertex(s);
    Vertex<int>* target = g.findVertex(t);

    // BFS para verificar se o caminho existe de s para t visitando skiping nodes
    queue<Vertex<int>*> q;
    unordered_set<int> visited;

    q.push(source);
    visited.insert(s);

    while (!q.empty()) {
        Vertex<int>* current = q.front();
        q.pop();

        // se encontrarmos o target
        if (current == target) {
            return true;
        }

        // Explore neighbors
        for (const auto& edge : current->getAdj()) {
            Vertex<int>* neighbor = edge.getDest();
            int neighborInfo = neighbor->getInfo();

            // Saltar nós no skip set ou já visitados
            if (skipSet.count(neighborInfo) || visited.count(neighborInfo)) {
                continue;
            }

            q.push(neighbor);
            visited.insert(neighborInfo);
        }
    }

    // Se não existir path retornar falso
    return false;
}



int GraphOps::numberConnectedComponents(Graph<int> g) {
    int componentCount = 0;

    // Mark all vertices as unvisited
    for (auto vertex : g.getVertexSet()) {
        vertex->setVisited(false);
    }

    // Helper function to perform BFS/DFS and mark reachable nodes as visited
    auto exploreComponent = [](Vertex<int>* startVertex) {
        queue<Vertex<int>*> q;
        q.push(startVertex);
        startVertex->setVisited(true);

        while (!q.empty()) {
            auto current = q.front();
            q.pop();

            for (const auto& edge : current->getAdj()) {
                auto neighbor = edge.getDest();
                if (!neighbor->isVisited()) {
                    neighbor->setVisited(true);
                    q.push(neighbor);
                }
            }
        }
    };

    // Loop through all vertices and find connected components
    for (auto vertex : g.getVertexSet()) {
        if (!vertex->isVisited()) {
            componentCount++;
            exploreComponent(vertex);  // Explore all nodes in this component
        }
    }

    return componentCount;
}

