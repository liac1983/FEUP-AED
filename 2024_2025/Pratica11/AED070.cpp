#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <sstream>

using namespace std;

struct Language {
    string name;
    unordered_set<string> dictionary;
    int count = 0;
};

void processText(const string &text, vector<Language> &languages) {
    string word;
    for (size_t i = 0; i < text.size(); ++i) {
        // Extract words from the text
        if (isalpha(text[i])) {
            word += tolower(text[i]);
        } else if (!word.empty()) {
            // Check the extracted word against each language's dictionary
            for (auto &lang : languages) {
                if (lang.dictionary.count(word)) {
                    lang.count++;
                }
            }
            word.clear();
        }
    }

    // Check the last word if text ends without a delimiter
    if (!word.empty()) {
        for (auto &lang : languages) {
            if (lang.dictionary.count(word)) {
                lang.count++;
            }
        }
    }
}

int main() {
    int N;
    cin >> N;
    vector<Language> languages(N);

    // Read languages and their dictionaries
    for (int i = 0; i < N; ++i) {
        cin >> languages[i].name;
        int W;
        cin >> W;
        for (int j = 0; j < W; ++j) {
            string word;
            cin >> word;
            languages[i].dictionary.insert(word);
        }
    }

    // Read the text to analyze
    string text;
    cin.ignore(); // Consume the newline after the last integer
    getline(cin, text);

    // Process the text to count words for each language
    processText(text, languages);

    // Output the results
    for (const auto &lang : languages) {
        cout << lang.name << ": " << lang.count << endl;
    }

    return 0;
}

