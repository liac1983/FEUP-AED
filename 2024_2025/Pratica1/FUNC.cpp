#include <iostream>
#include <vector>
using namespace std;

// Function to implement FUNC as described
pair<int, int> FUNC(const vector<int>& x, int n, vector<int>& v, int p) {
    // Initialize frequency array v
    for (int k = 0; k <= p; ++k) {
        v[k] = 0;
    }
    
    // Initialize s to the first element of x, and set its frequency to 1
    int s = x[0];
    v[s] = 1;
    int t = 1; // Only one element initially, so t = 1

    // Process the rest of the array
    for (int k = 1; k < n; ++k) {
        v[x[k]]++; // Increment frequency of x[k]

        // If x[k] is more frequent or it's the same element as the current s
        if (s == x[k] || v[x[k]] > v[s]) {
            s = x[k]; // Update s to the more frequent element
            t = 1; // Reset t since we found a new most frequent element
        } 
        // If there's a tie in frequency, increment t
        else if (v[x[k]] == v[s]) {
            t++;
        }
    }

    // Return the most frequent element s and how many elements have that frequency t
    return {s, t};
}

int main() {
    // Example input
    vector<int> x = {1, 3, 3, 2, 1, 3, 2, 2}; // Input array
    int n = x.size(); // Length of the array
    int p = 3; // Maximum value in the array (p + 1 should cover all possible values)
    
    // Initialize frequency array v of size p + 1 (since values range from 1 to p)
    vector<int> v(p + 1, 0);

    // Call FUNC to get the most frequent element and the count of elements with same frequency
    pair<int, int> result = FUNC(x, n, v, p);

    // Output the result
    cout << "Most frequent element: " << result.first << endl;
    cout << "Number of elements with same frequency: " << result.second << endl;

    return 0;
}

/* pair<int, int> FUNC(const vector<int>& x, int n, vector<int>& v, int p)
{
    for (int k = 0; k <= p; ++k) {
        v[k] = 0;
    }
    int s = x[0];
    v[s] = 1;
    int t = 1;

    for (int k = 1; k < n; ++k) {
        v[x[k]]++;
        if (s == x[k] || v[x[k]] > v[s]) {
            s = x[k];
            t = 1;
        }
        else if (v[x[k]] == v[s]) {
            t++;
        }
    }
    return {s,t};
} */

