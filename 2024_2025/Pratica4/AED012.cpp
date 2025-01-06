#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> skill_levels(N);
    for (int i = 0; i < N; i++) {
        cin >> skill_levels[i];
    }

    sort(skill_levels.begin(), skill_levels.end());
    
    for (int i = N - 1; i >= N - K; i--) {
        cout << skill_levels[i] << endl;
    }

    return 0;
}
