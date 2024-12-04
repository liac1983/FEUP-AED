#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N; // Numero de elementos da sequencia
    // Mapa para contar as ocorrências de cada numero 
    // chave é o numero e o valor é a sua frequencia
    map<int, int> frequency; // Map to count occurrences of each number

    // Read the sequence and populate the map
    for (int i = 0; i < N; i++) {
        int num; // numero da sequecia
        cin >> num;
        frequency[num]++; // incrementa a frequencia do numero no mapa
    }

    // Calculate the total number of removals
    int removals = 0; // Numero de remoções necessárias
    // Itera sobre o mapa para calcular o numero de remoções necessárias
    for (const auto &entry : frequency) {
        int x = entry.first;  // The number
        int f = entry.second; // Frequency of the number

        if (f < x) {
            // If frequency is less than the number, remove all occurrences
            removals += f;
        } else {
            // If frequency is greater, remove excess occurrences
            removals += f - x;
        }
    }

    // Output the total removals
    cout << removals << endl;

    return 0;
}

