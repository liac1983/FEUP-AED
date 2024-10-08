#include <iostream>
#include <vector>

using namespace std;

// Binary search function to find the key in the vector
int binary_search(const vector<int> &v, int key) {
    int low = 0;
    int high = (int)v.size() - 1;

    while (low <= high) {
        int middle = low + (high - low) / 2; // Calculate middle index

        if (key < v[middle]) {
            high = middle - 1;  // Search in the left half
        } else if (key > v[middle]) {
            low = middle + 1;   // Search in the right half
        } else {
            return middle;       // Key found, return the index
        }
    }

    return -1;  // Key not found
}

int main() {
    int N, Q;
    
    // Reading the number of elements in the sequence
    cin >> N;
    vector<int> sequence(N);
    
    // Reading the sequence of numbers
    for (int i = 0; i < N; i++) {
        cin >> sequence[i];
    }
    
    // Reading the number of queries
    cin >> Q;
    
    // Processing each query
    for (int i = 0; i < Q; i++) {
        int query;
        cin >> query;
        
        // Perform binary search and print the result
        int result = binary_search(sequence, query);
        cout << result << endl;
    }

    return 0;
}
