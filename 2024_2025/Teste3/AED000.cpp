#include <iostream>
using namespace std;

int main() {
    int Q; // quantidade de numeros a serem processados 
    cin >> Q; // ler Q
    int count42 = 0; // Variável para contar o numero de vezes que aparece 42
    for (int i = 0; i < Q; i++) { // Processamos cada numero 
        int ni; // numero atual
        cin >> ni; // ler o numero atual
        if (ni == 42) { 
            count42++; // incrementar o contador se o numero for igual a 42
        }
    }
    cout << count42 << endl; // imprimir quantas vezes aparece o numero 42
}