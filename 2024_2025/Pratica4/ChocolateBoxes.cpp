#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    
    vector<int> chocolates(N);
    
    // Ler a quantidade de chocolates em cada caixa
    for (int i = 0; i < N; ++i) {
        cin >> chocolates[i];
    }
    
    // Ordenar as caixas de chocolates
    sort(chocolates.begin(), chocolates.end());
    
    // Variável para armazenar a menor diferença encontrada
    int minDifference = INT_MAX;
    
    // Verificar todas as subsequências de tamanho K
    for (int i = 0; i <= N - K; ++i) {
        int currentDifference = chocolates[i + K - 1] - chocolates[i];
        minDifference = min(minDifference, currentDifference);
    }
    
    // Imprimir a menor diferença
    cout << minDifference << endl;

    return 0;
}
