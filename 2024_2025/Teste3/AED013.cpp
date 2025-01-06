#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// conta o numero de 1 na representaçáo binária do número
int countBits(int n) {
    int count = 0;
    while(n) {
        count += n & 1; // incrementa o contagem se o bit menos significativo for 1
        n >>= 1; // shift à direita 1 bit para verificar o proximo bit
    }
    return count;
}
//ordena a sequencia baseada no numero de bits 1 na representação binária dos números
bool customComparator(int x, int y ) {
    int countX = countBits(x);
    int countY = countBits(y);
    if (countX != countY) { // ordena por ordem decrescente
        return countX > countY; // um bit a mais fica em primeiro
    }
    return x < y; // ordena ascendente
}

int main() {
    int n;
    cin >> n; // numero de inteiros
    vector<int> numbers(n);
    for (int i = 0; i < n; i++) { // itera pelos numeros
        cin >> numbers[i];
    }
    // ordena os numeros usando o customComparator
    sort(numbers.begin(), numbers.end(), customComparator);
    for (int i = 0; i < n; i++) {
        cout << numbers[i] << endl; // dá output dos numeros ordenados
    }
    return 0;
}