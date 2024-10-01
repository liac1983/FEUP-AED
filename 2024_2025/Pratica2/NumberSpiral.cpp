#include <iostream>
#include <cmath>

using namespace std;

pair<int, int> findCoordinates(long long N) {
    if (N == 1) {
        return {0, 0};
    }

    // Encontre o anel k tal que N esteja nesse anel
    long long k = (long long)(sqrt(N - 1) + 1) / 2;

    // O número no canto superior direito do anel k
    long long corner = (2 * k + 1) * (2 * k + 1);

    // Coordenadas do canto superior direito
    long long x = k;
    long long y = k;

    // Determine a posição de N no anel k
    long long sideLength = 2 * k;
    if (N >= corner - sideLength) {
        return {x - (corner - N), y}; // Descendo pelo lado direito
    }
    corner -= sideLength;

    if (N >= corner - sideLength) {
        return {-x, y - (corner - N)}; // Indo para a esquerda pelo lado superior
    }
    corner -= sideLength;

    if (N >= corner - sideLength) {
        return {-x + (corner - N), -y}; // Subindo pelo lado esquerdo
    }
    corner -= sideLength;

    return {x, -y + (corner - N)}; // Indo para a direita pelo lado inferior
}

int main() {
    long long N;
    cin >> N;

    pair<int, int> coordinates = findCoordinates(N);
    cout << "(" << coordinates.first << "," << coordinates.second << ")" << endl;

    return 0;
}
