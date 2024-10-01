#include <iostream>
#include <vector>

using namespace std;

int countValidSections(int N, int K, int T, const vector<int> &depths) {
    int validSections = 0;  // Contador de subseções válidas
    int count = 0;  // Contador de elementos maiores ou iguais a T na janela

    // Verificar a primeira subseção (janela inicial)
    for (int i = 0; i < K; i++) {
        if (depths[i] >= T) {
            count++;
        }
    }

    // Se a primeira subseção é válida, incrementamos o contador
    if (count >= (K + 1) / 2) {
        validSections++;
    }

    // Deslizar a janela pelo resto do array
    for (int i = K; i < N; i++) {
        // Remover o efeito do elemento que está saindo da janela
        if (depths[i - K] >= T) {
            count--;
        }
        // Adicionar o efeito do novo elemento que está entrando na janela
        if (depths[i] >= T) {
            count++;
        }
        // Verificar se a subseção atual é válida
        if (count >= (K + 1) / 2) {
            validSections++;
        }
    }

    return validSections;
}

int main() {
    int N, K, T;
    cin >> N >> K >> T;

    vector<int> depths(N);
    for (int i = 0; i < N; i++) {
        cin >> depths[i];
    }

    // Contar as subseções válidas
    cout << countValidSections(N, K, T, depths) << endl;

    return 0;
}
