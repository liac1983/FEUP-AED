#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void findMostFrequentMotifs(int K, const string& S) {
    unordered_map<string, int> motifFrequency; // Map to store frequencies of motifs
    int maxFrequency = 0; // Track the maximum frequency

    // Traverse the DNA string and count frequencies of motifs of size K
    for (size_t i = 0; i <= S.size() - K; ++i) {
        string motif = S.substr(i, K); // Extract motif of size K
        motifFrequency[motif]++;
        maxFrequency = max(maxFrequency, motifFrequency[motif]); // Update max frequency
    }

    // Collect motifs with the maximum frequency
    vector<string> mostFrequentMotifs;
    for (const auto& entry : motifFrequency) {
        if (entry.second == maxFrequency) {
            mostFrequentMotifs.push_back(entry.first);
        }
    }

    // Output the results
    cout << maxFrequency << endl;
    if (mostFrequentMotifs.size() == 1) {
        cout << mostFrequentMotifs[0] << endl;
    } else {
        cout << mostFrequentMotifs.size() << endl;
    }
}

int main() {
    int K;
    string S;

    // Input: motif length K and DNA string S
    cin >> K >> S;

    // Find and output the most frequent motifs
    findMostFrequentMotifs(K, S);

    return 0;
}

