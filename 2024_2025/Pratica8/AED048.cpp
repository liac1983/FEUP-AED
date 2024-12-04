#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    // Read input
    int X, N; // Comprimento da estarda e o numero de semaforos a adicionar
    cin >> X >> N;
    // vetor para armazenar as posições onde os semaforors serão adicionados
    vector<int> positions(N);
    for (int i = 0; i < N; i++) {
        cin >> positions[i];
    }

    // Set to store traffic light positions
    set<int> lights;
    lights.insert(0); // posição inicial e final da estrada
    lights.insert(X);

    // Multiset to store lengths of segments
    multiset<int> gaps;
    gaps.insert(X); // Inicialmente, a estrada inteira é um único segmento

    // Process each traffic light addition
    for (int i = 0; i < N; i++) {
        int pos = positions[i]; // Nova posição do semaforo

        // Find neighbors
        auto it = lights.upper_bound(pos); // Primeiro elemento maior que pos
        int right = *it; // vizinho da direita 
        int left = *prev(it); // vizinho da esquerda

        // Remove the current gap
        gaps.erase(gaps.find(right - left));

        // Add new gaps
        gaps.insert(pos - left); // segmento entre left e pos
        gaps.insert(right - pos);

        // Add the new light position
        lights.insert(pos);

        // Output the largest gap
        cout << *gaps.rbegin() << (i == N - 1 ? "" : " ");
    }

    cout << endl;
    return 0;
}

