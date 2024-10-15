#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;  // Read N (number of players) and K (number of top players)

    vector<int> skill_levels(N);
    for (int i = 0; i < N; i++) {
        cin >> skill_levels[i];  // Read the skill levels of N players
    }

    // Sort the skill levels in increasing order
    sort(skill_levels.begin(), skill_levels.end());

    // Output the top K players in decreasing order
    for (int i = N - 1; i >= N - K; i--) {
        cout << skill_levels[i] << endl;
    }

    return 0;
}
