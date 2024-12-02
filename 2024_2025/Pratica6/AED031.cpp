#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

// Função para encontrar os bilhetes vencedores
// Parâmetros:
// N - Número total de bilhetes
// K - Passos para eliminar um bilhete
// W - Número de bilhetes vencedores
vector<int> findWinningTickets(int N, int K, int W) {
    deque<int> tickets; // Inicializa uma deque com os bilhetes de 1 a N
    for (int i = 1; i <= N; ++i) {
        tickets.push_back(i);
    }

    vector<int> winners; // Vetor para armazenar os bilhetes vencedores
    int index = 0; // Índice do bilhete atual

    while ((int)tickets.size() > W) {
        // Calcula o índice do bilhete a ser eliminado
        index = (index + K - 1) % tickets.size();
        // Remove o bilhete do deque
        tickets.erase(tickets.begin() + index);
    }
    // Adiciona os bilhetes restantes como vencedores
    winners.assign(tickets.begin(), tickets.end());
    sort(winners.begin(), winners.end()); // Ordena os bilhetes vencedores em ordem crescente

    return winners;
}

int main() {
    int N, K, W;
    cin >> N >> K >> W;

    vector<int> winners = findWinningTickets(N, K, W);

    for (int ticket : winners) {
        cout << ticket << endl;
    }

    return 0;
}


