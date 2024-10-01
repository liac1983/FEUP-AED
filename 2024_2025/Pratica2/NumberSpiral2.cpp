#include <iostream>
#include <cmath>

using namespace std;

pair<long long, long long> findCoordinates(long long N) {
    if (N == 1) {
        return {0, 0}; // Posição do número 1
    }

    // Encontra o anel k em que N está. O anel k é tal que (2k-1)^2 < N <= (2k+1)^2
    long long k = (long long)((sqrt(N - 1) + 1) / 2); // Calcula o anel

    // O número no canto superior direito do anel k
    long long corner = (2 * k + 1) * (2 * k + 1);

    // Coordenadas do canto superior direito do anel
    long long x = k;
    long long y = k;

    // O tamanho do lado de um quadrado no anel k é 2k
    long long sideLength = 2 * k;

    // Vamos descobrir em qual lado da espiral o número N está e ajustar as coordenadas.
    if (N >= corner - sideLength) {
        // N está no lado direito, descendo
        return {x - (corner - N), y};
    }
    corner -= sideLength;

    if (N >= corner - sideLength) {
        // N está no lado superior, indo para a esquerda
        return {-x, y - (corner - N)};
    }
    corner -= sideLength;

    if (N >= corner - sideLength) {
        // N está no lado esquerdo, subindo
        return {-x + (corner - N), -y};
    }
    corner -= sideLength;

    // N está no lado inferior, indo para a direita
    return {x, -y + (corner - N)};
}

int main() {
    long long N;
    cin >> N;

    pair<long long, long long> coordinates = findCoordinates(N);
    cout << "(" << coordinates.first << "," << coordinates.second << ")" << endl;

    return 0;
}
