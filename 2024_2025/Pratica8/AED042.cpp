#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N; // Numero de eventos

    vector<int> events(N); // vetor para armazenar eventos
    for (int i = 0; i < N; i++) {
        cin >> events[i]; // Lê cada evento
    }
    // Mapa para armazenar a ultima ocorrencia de cada evento
    // A chave é o evento, e o valor é a posição 
    unordered_map<int, int> lastPosition; // To store the last occurrence of each event
    vector<int> result(N); // To store the output
    // vetor para ramazenar o resultado final
    for (int i = 0; i < N; i++) {
        int event = events[i]; // evento atual

        // Check if the event exists in the map
        if (lastPosition.find(event) != lastPosition.end()) {
            // Se o evento já apareceu antes, armazenamos a ultima posição em que apareceu
            result[i] = lastPosition[event]; // Get last occurrence
        } else {
            result[i] = -1; // First occurrence
        }

        // Update the last position of the current event
        lastPosition[event] = i + 1; // Store 1-based index
    }

    // Print the result
    for (int i = 0; i < N; i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;

    return 0;
}

