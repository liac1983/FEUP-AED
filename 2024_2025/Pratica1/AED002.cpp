#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> sequence(N);
    for (int i = 0; i < N; ++i) {
        cin >> sequence[i];
    }

    // Algoritmo de Kadane
    int max_sum = sequence[0];
    int current_sum = sequence[0];
    for (int i = 1; i < N; ++i) {
        current_sum = max(sequence[i], current_sum + sequence[i]);
        max_sum = max(max_sum, current_sum);
    }

    cout << max_sum << endl;
}