#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;
// remove espaços e converte minusculas e ordena
string sortPhrase(const string &s) {
    string result;
    for (char c : s) { // remove espaços e converte para letras minusculas
        if (!isspace(c)) {
            result += tolower(c);
        }
    }
    sort(result.begin(), result.end()); // ordena a string resultante
    return result;
}

int main() {
    int N;
    cin >> N; //ler o numero
    cin.ignore(); // ignora o '\n' 
    unordered_map<string, int> anagramCount;
    for (int i = 0; i < N, ++i) { // ler as N frases e aplicar sortPhrase
        string phrase;
        getline(cin, phrase);
        string sortedPhrase = sortPhrase(phrase);
        anagramCount[sortedPhrase]++; // contar cada versão cormalizada
    }
    int anagramClasses = 0; // contar o numero de classes de anagramas 
    for (const auto &entry : anagramCount) { // verifica quantas classes têm mais de uma frase
        if (entry.second > 1) {
            anagramClasses++;
        }
    }
    // numero de classes de anagramas 
    cout << anagramClasses << endl;
    return 0;
}
