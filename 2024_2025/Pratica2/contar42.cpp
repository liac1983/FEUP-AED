#include <iostream>
using namespace std;

int main() {
    int Q;  // quantidade de números a serem processados
    cin >> Q;  // ler o valor de Q
    
    int count42 = 0;  // variável para contar quantas vezes o número 42 aparece
    
    for (int i = 0; i < Q; i++) {
        int ni;  // número atual
        cin >> ni;  // ler o número
        
        // Se o número for 42, incrementar o contador
        if (ni == 42) {
            count42++;
        }
    }
    
    // Imprimir a quantidade de vezes que o número 42 apareceu
    cout << count42 << endl;
    
    return 0;
}
