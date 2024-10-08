#include <iostream>
#include <vector>

using namespace std;

// Function to find the lower bound using binary search
int lowerBound(const vector<int>& v, int key) {
    int low = 0;
    int high = (int)v.size() - 1;
    int result = -1;  // If no valid result is found, return -1

    while (low <= high) {
        int middle = low + (high - low) / 2;

        if (v[middle] >= key) {
            result = middle;  // This could be the answer, but we need to check left side
            high = middle - 1; // Continue searching in the left part
        } else {
            low = middle + 1;  // Move to the right part
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
        int query;
        cin >> query;
        
        // Perform lower bound binary search and print the result
        int result = lowerBound(sequence, query);
        cout << result << endl;
    }

    return 0;
}
