#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to check if B can be a subsequence of A after removing the first k letters as per permutation P
bool canRemove(int k, const string& A, const string& B, const vector<int>& P) {
    int n = A.size(), m = B.size();
    vector<bool> removed(n, false);  // Array to mark which letters are removed

    // Mark the first k letters as removed based on the permutation P
    for (int i = 0; i < k; ++i) {
        removed[P[i] - 1] = true;  // P[i] is 1-based index, convert to 0-based
    }

    // Two-pointer approach to check if B is a subsequence of the modified A
    int j = 0;  // Pointer for B
    for (int i = 0; i < n; ++i) {
        if (!removed[i] && A[i] == B[j]) {
            j++;
        }
        if (j == m) {
            return true;  // If we matched all of B, return true
        }
    }

    return false;  // If we didn't match all of B, return false
}

int main() {
    string A, B;
    cin >> A >> B;

    int n = A.size();
    vector<int> P(n);

    // Reading the permutation P
    for (int i = 0; i < n; ++i) {
        cin >> P[i];
    }

    // Binary search to find the maximum number of letters Susan can remove
    int low = 0, high = n, answer = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canRemove(mid, A, B, P)) {
            answer = mid;  // If it's possible, try for a larger k
            low = mid + 1;
        } else {
            high = mid - 1;  // If not possible, try for a smaller k
        }
    }

    cout << answer << endl;  // Output the maximum number of letters Susan can remove

    return 0;
}

