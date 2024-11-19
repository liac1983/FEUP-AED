#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> events(N);
    for (int i = 0; i < N; i++) {
        cin >> events[i];
    }

    unordered_map<int, int> lastPosition; // To store the last occurrence of each event
    vector<int> result(N); // To store the output

    for (int i = 0; i < N; i++) {
        int event = events[i];

        // Check if the event exists in the map
        if (lastPosition.find(event) != lastPosition.end()) {
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

