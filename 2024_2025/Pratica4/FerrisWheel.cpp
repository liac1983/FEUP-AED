#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> weights(N);

    // Ler os pesos das crianças
    for (int i = 0; i < N; ++i) {
        cin >> weights[i];
    }

    // Ordenar os pesos em ordem crescente
    sort(weights.begin(), weights.end());

    int cabins = 0;
    int l = 0;         // Ponteiro para o mais leve
    int h = N - 1;     // Ponteiro para o mais pesado

    // Usar dois ponteiros para emparelhar as crianças
    while (l <= h) {
        if (weights[l] + weights[h] <= K) {
            // Se a criança mais leve e a mais pesada podem ir juntas
            l++;
            h--;
        } else {
            // Caso contrário, a criança mais pesada vai sozinha
            h--;
        }
        // Sempre usamos uma cabine a cada iteração
        cabins++;
    }

    // Output: número mínimo de cabines necessárias
    cout << cabins << endl;

    return 0;
}
