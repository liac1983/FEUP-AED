#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Precompute binomial coefficients
vector<vector<int>> computeBinomialCoefficients(int n) {
    vector<vector<int>> binom(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= n; ++i) {
        binom[i][0] = binom[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
        }
    }
    return binom;
}

// Calculate the index of a given word
int calculateIndex(const string& word, const vector<vector<int>>& binom) {
    int index = 0;
    int length = word.size();

    // Add indices of all words with smaller lengths
    for (int len = 1; len < length; ++len) {
        index += binom[26][len];
    }

    // Add indices within the current length group
    int prev = 0; // Track the previous letter's position
    for (int i = 0; i < length; ++i) {
        int charPos = word[i] - 'a' + 1;
        for (int j = prev + 1; j < charPos; ++j) {
            index += binom[26 - j][length - i - 1];
        }
        prev = charPos;
    }

    return index + 1; // 1-based indexing
}

int main() {
    int N;
    cin >> N;

    vector<string> words(N);
    for (int i = 0; i < N; ++i) {
        cin >> words[i];
    }

    // Precompute binomial coefficients up to 26
    vector<vector<int>> binom = computeBinomialCoefficients(26);

    // Calculate and output indices for each word
    for (const string& word : words) {
        cout << word << " " << calculateIndex(word, binom) << endl;
    }

    return 0;
}

