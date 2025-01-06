#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) { // verifica divisor até raiz de n
        if (n % i == 0) return false; // encontra divisor, não é primo
    }
    return true; // nenhum divisor encontrado, é primo
}

int main() {
    int q;
    cin >> q; // ler a quantos numeros
    for (int i = 0; i < q; i++) {
        int n;
        cin >> n; // ler cada numero
        // verifica se cada numero é primo
        if (isPrime(n)) cout << n << " is prime" << endl;
        else cout << n << " is composite" << endl;
    }
    return 0;
}