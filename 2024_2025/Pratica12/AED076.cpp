#include <iostream>
#include <vector>
#include <string>

using namespace std;
// Tabela global para armazenar combinações C(n, k)
vector<vector<int>> comb(27, vector<int>(27, 0));

// Function to calculate combinations C(n, k)
void computeCombinations() {
    for (int n = 0; n <= 26; n++) {
        comb[n][0] = comb[n][n] = 1; // C(n, 0) = 1 and C(n, n) = 1
        for (int k = 1; k < n; k++) {
            // Relação recursiva: C(n, k) = C(n-1, k-1) + C(n-1, k)
            comb[n][k] = comb[n-1][k-1] + comb[n-1][k];
        }
    }
}

// Function to compute the index of a word
int computeIndex(const string& word) {
    int index = 0; // Índice da palavra
    int len = word.size(); // Comprimento da palavra

    // Add all words of smaller lengths
    for (int k = 1; k < len; k++) {
        index += comb[26][k]; // Cálculo das combinações C(26, k)
    }

    // Count words of the same length lexicographically smaller
    int prev = 0; // Último caractere processado (para garantir ordenação)
    for (int i = 0; i < len; i++) {
        char c = word[i];
        for (char ch = prev + 1; ch < c; ch++) {
            int remaining = 26 - (ch - 'a');  // Letras restantes no alfabeto
            if (remaining >= len - i - 1) { // Ensure valid bounds
                index += comb[remaining][len - i - 1]; // Contar combinações válidas
            }
        }
        prev = c; // Atualizar o último caractere processado
    }

    return index + 1; // Words are 1-based index
}

int main() {
    int N; // Número de palavras a serem processadas
    cin >> N;

    computeCombinations(); // Precompute combinations

    vector<string> words(N); // Vetor para armazenar as palavras
    for (int i = 0; i < N; i++) {
        cin >> words[i]; // Ler cada palavra
    }
    // Calcular e imprimir o índice de cada palavra
    for (const string& word : words) {
        cout << word << " " << computeIndex(word) << endl;
    }

    return 0;
}
