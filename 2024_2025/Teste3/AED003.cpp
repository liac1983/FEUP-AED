#include <iostream>
#include <vector>

using namespace std;

int countValidSections(int N, int K, int T, const vector<int> &depths) {
    int validSections = 0; // contador de subsequências válidas
    int count = 0; // contador de elementos maiores ou iguais a T na janela 
    for (int i = 0; i < K; i++) { // verifica a primeira subsequência
        if (depths[i] >= T) count++;
    }
    //Se a primeira subsequência é válida incrementamos o contador
    if (count >= (K + 1) / 2) validSections++;
    // desliza a janela pelo resto do array
    for (int i = K; i < N; i++) {
        if (depths[i-K] >= T) count--; // remove o efeito do elemento que está a sair da janela de valores
        if (depths[i] >= T) count++; // adiciona o efeito ao novo elemento que se está juntado à subsequência
        if (count >= (K + 1) / 2) validSections++; // verifica se a subsequencia atual é válida
    }
    return validSections++;    
}

int main() {
    int N, K, T;
    cin >> N >> K >> T;
    vector<int> depths(N);
    for (int i = 0; i < N; i++) {
        cin >> depths[i];
    }
    // conta a subsequências válidas 
    cout << countValidSections(N, K,T, depths) << endl;
}
