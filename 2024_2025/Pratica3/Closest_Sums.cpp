#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> // For abs()

using namespace std;

// Function to find the closest sum to the query and handle multiple closest sums
pair<int, int> findClosestSums(const vector<int>& sums, int query) {
    // Use binary search to find the position where query would fit
    auto it = lower_bound(sums.begin(), sums.end(), query);

    int closest1 = sums[0]; // First closest sum
    int closest2 = -1;      // Second closest sum, initialized to an invalid value

    // Check the sum at the lower bound position
    if (it != sums.end()) {
        closest1 = *it; // Candidate 1: the element at the lower bound
    }

    // Check the previous sum (it - 1) if it exists
    if (it != sums.begin()) {
        int prev_sum = *(it - 1); // Candidate 2: the element just before lower bound
        if (abs(query - prev_sum) < abs(query - closest1)) {
            closest1 = prev_sum;
        } else if (abs(query - prev_sum) == abs(query - closest1)) {
            // If both are equally close, store both values
            closest2 = closest1;
            closest1 = prev_sum;
        }
    }

    return make_pair(closest1, closest2);
}

int main() {
    int N;
    // Reading the number of elements in the set
    cin >> N;
    vector<int> S(N);

    // Reading the set of numbers
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }

    // Vector to store all pairwise sums
    vector<int> sums;

    // Generating all pairwise sums
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            sums.push_back(S[i] + S[j]);
        }
    }

    // Sorting the sums
    sort(sums.begin(), sums.end());

    int Q;
    // Reading the number of queries
    cin >> Q;
    vector<int> queries(Q);

    // Reading the queries
    for (int i = 0; i < Q; i++) {
        cin >> queries[i];
    }

    // Answer each query
    for (int i = 0; i < Q; i++) {
        int query = queries[i];
        auto result = findClosestSums(sums, query);

        // Output the results
        if (result.second == -1) {
            // If there is only one closest sum
            cout << result.first << endl;
        } else {
            // If there are two equally close sums
            cout << result.first << " " << result.second << endl;
        }
    }

    return 0;
}
