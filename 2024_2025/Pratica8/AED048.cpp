#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    // Read input
    int X, N;
    cin >> X >> N;

    vector<int> positions(N);
    for (int i = 0; i < N; i++) {
        cin >> positions[i];
    }

    // Set to store traffic light positions
    set<int> lights;
    lights.insert(0);
    lights.insert(X);

    // Multiset to store lengths of segments
    multiset<int> gaps;
    gaps.insert(X);

    // Process each traffic light addition
    for (int i = 0; i < N; i++) {
        int pos = positions[i];

        // Find neighbors
        auto it = lights.upper_bound(pos);
        int right = *it;
        int left = *prev(it);

        // Remove the current gap
        gaps.erase(gaps.find(right - left));

        // Add new gaps
        gaps.insert(pos - left);
        gaps.insert(right - pos);

        // Add the new light position
        lights.insert(pos);

        // Output the largest gap
        cout << *gaps.rbegin() << (i == N - 1 ? "" : " ");
    }

    cout << endl;
    return 0;
}

