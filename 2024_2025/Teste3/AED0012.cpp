#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, K; // N numero de jogadores, K numero de top players
    cin >> N >> K;
    vector<int> skill_levels(N);
    for (int i = 0; i < N; i++) {
        cin >> skill_levels[i]; // ler o skill levels
    }
    // ordena os skill levels por ordem crescente
    sort(skill_levels.begin(), skill_levels.end());
    // output dos K players em ordem decrescente
    for (int i = N -1; i >= N - K; i--) {
        cout << skill_levels[i] << endl;
    }
    return 0;
}
