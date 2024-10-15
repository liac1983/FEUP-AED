#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Função para remover espaços, converter para minúsculas e ordenar
string sortPhrase(const string &s) {
    string result;

    // Remover espaços e converter para letras minúsculas
    for (char c : s) {
        if (!isspace(c)) {
            result += tolower(c);
        }
    }

    // Ordenar a string resultante
    sort(result.begin(), result.end());

    return result;
}

int main() {
    int N;
    cin >> N;
    cin.ignore();  // Para ignorar o '\n' depois de ler o número N

    unordered_map<string, int> anagramCount;  // Mapa para contar quantas vezes cada versão aparece
    
    // Ler as N frases e aplicar sortPhrase
    for (int i = 0; i < N; ++i) {
        string phrase;
        getline(cin, phrase);
        string sortedPhrase = sortPhrase(phrase);
        anagramCount[sortedPhrase]++;  // Contar cada versão normalizada
    }

    // Contar o número de classes de anagramas
    int anagramClasses = 0;

    // Verificar quantas classes têm mais de uma frase
    for (const auto &entry : anagramCount) {
        if (entry.second > 1) {
            anagramClasses++;
        }
    }

    // Output: número de classes de anagramas
    cout << anagramClasses << endl;

    return 0;
}
