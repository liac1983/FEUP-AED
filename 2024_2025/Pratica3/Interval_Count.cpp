#include <iostream>
#include <vector>

using namespace std;

// Function to find the lower bound (first element >= key)
int lowerBound(const vector<int>& v, int key) {
    int low = 0;
    int high = (int)v.size() - 1;
    int result = (int)v.size();  // Set result to size of the vector initially

    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (v[middle] >= key) {
            result = middle;    // Update result and search in the left half
            high = middle - 1;
        } else {
            low = middle + 1;   // Search in the right half
        }
    }

    return result;
}

// Function to find the upper bound (first element > key)
int upperBound(const vector<int>& v, int key) {
    int low = 0;
    int high = (int)v.size() - 1;
    int result = (int)v.size();  // Set result to size of the vector initially

    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (v[middle] > key) {
            result = middle;    // Update result and search in the left half
            high = middle - 1;
        } else {
            low = middle + 1;   // Search in the right half
        }
    }

    return result;
}

int main() {
    int N, Q;

    // Reading the size of the sequence
    cin >> N;
    vector<int> sequence(N);

    // Reading the sorted sequence
    for (int i = 0; i < N; i++) {
        cin >> sequence[i];
    }

    // Reading the number of queries
    cin >> Q;

    // Processing each query
    for (int i = 0; i < Q; i++) {
        int A, B;
        cin >> A >> B;

        // Find the first element >= A and the first element > B
        int lower = lowerBound(sequence, A);
        int upper = upperBound(sequence, B);

        // The number of elements in the range [A, B]
        int count = upper - lower;

        cout << count << endl;
    }

    return 0;
}
