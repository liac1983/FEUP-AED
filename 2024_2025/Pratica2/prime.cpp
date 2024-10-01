#include <iostream>
#include <cmath>  // Para usar a função sqrt

using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    
    // Verificar divisores até sqrt(n)
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;  // Encontrou um divisor, então n não é primo
        }
    }
    
    return true;  // Nenhum divisor encontrado, então n é primo
}

int main() {
    int q;
    cin >> q;  // Ler a quantidade de números a serem processados
    
    for (int i = 0; i < q; i++) {
        int n;
        cin >> n;  // Ler o número
        
        // Verificar se o número é primo
        if (isPrime(n)) {
            cout << n << " is prime" << endl;
        } else {
            cout << n << " is composite" << endl;
        }
    }
    
    return 0;
}
