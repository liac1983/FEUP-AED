#include <iostream>
#include <vector>
#include <algorithm> // Para usar a função max

using namespace std;

int maxSum(const vector<int> &v) {
    int n = v.size();
    int maxSoFar = v[0];
    int maxEndingHere = v[0];

    // Iteramos pela sequência a partir da segunda posição
    for (int i = 1; i < n; i++) {
        // Verificamos se é melhor continuar a subsequência atual ou começar uma nova
        maxEndingHere = max(v[i], maxEndingHere + v[i]);
        // Atualizamos a soma máxima
        maxSoFar = max(maxSoFar, maxEndingHere);
    }

    return maxSoFar;
}

int main() {
    int N;
    cin >> N;

    vector<int> sequence(N);
    for (int i = 0; i < N; i++) {
        cin >> sequence[i];
    }

    cout << maxSum(sequence) << endl;

    return 0;
}
