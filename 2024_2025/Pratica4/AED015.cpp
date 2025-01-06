#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>


using namespace std;

string sortPhrase(const string &s) {
    string result;

    for (char c : s) {
        if (!isspace(c)) {
            result += tolower(c);
        }

    }

    sort(result.begin(), result.end());

    return result;
}

int main() {
    int N;
    cin >> N;
    cin.ignore();

    unordered_map<string, int> anagramCount;
    for (int i = 0; i < N; ++i) {
        string phrase;
        getline(cin, phrase);
        string sortedPhrase = sortPhrase(phrase);
        anagramCount[sortedPhrase]++;
    }

    int anagramClasses = 0;

    for (const auto &entry : anagramCount) {
        if (entry.second > 1) {
            anagramClasses++;
        }
    }

    cout << anagramClasses << endl;

    return 0;
}

