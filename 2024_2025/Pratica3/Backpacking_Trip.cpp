#include <iostream>
#include <vector>
#include <numeric> // For accumulate
#include <algorithm>

using namespace std;

// Function to check if it's possible to partition the distances into k days
// such that the maximum distance walked in a day is ≤ x.
bool isPossible(const vector<int>& distances, int x, int k) {
    int partition_count = 1;  // Start with one partition
    int current_sum = 0;      // Sum of the current partition

    for (int i = 0; i < distances.size(); i++) {
        if (distances[i] > x) {
            return false; // If a single distance exceeds x, it's impossible
        }

        if (current_sum + distances[i] > x) {
            // Start a new partition if adding the current distance exceeds x
            partition_count++;
            current_sum = distances[i];
        } else {
            // Otherwise, add the distance to the current partition
            current_sum += distances[i];
        }

        if (partition_count > k) {
            return false; // If more partitions than k are required, return false
        }
    }

    return true; // It's possible to partition within k days with max distance ≤ x
}

// Function to perform binary search for the minimum possible maximum partition sum
int findMinimumMaxDistance(const vector<int>& distances, int k) {
    int low = *max_element(distances.begin(), distances.end()); // Largest single distance
    int high = accumulate(distances.begin(), distances.end(), 0); // Sum of all distances

    while (low < high) {
        int mid = low + (high - low) / 2;

        if (isPossible(distances, mid, k)) {
            high = mid; // Try a smaller max sum
        } else {
            low = mid + 1; // Increase the max sum
        }
    }

    return low; // The smallest possible value of the largest partition sum
}

int main() {
    int N;
    // Reading the number of distances
    cin >> N;
    vector<int> distances(N);

    // Reading the distances
    for (int i = 0; i < N; i++) {
        cin >> distances[i];
    }

    int Q;
    // Reading the number of queries
    cin >> Q;

    // Processing each query
    for (int i = 0; i < Q; i++) {
        int K;
        cin >> K;

        // Perform binary search to find the optimal cost for K days
        int result = findMinimumMaxDistance(distances, K);
        cout << result << endl;
    }

    return 0;
}
