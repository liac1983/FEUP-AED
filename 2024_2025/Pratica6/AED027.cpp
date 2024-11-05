#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// Struct to store matching pairs
struct Match {
    string type;
    int openPos;
    int closePos;
};

int main() {
    // Input the expression
    string expression;
    getline(cin, expression);

    stack<pair<char, int>> st;  // Stack to store open symbols with their positions
    vector<Match> matches;      // Vector to store successful matches

    bool hasBraces = false;     // Flag to check if there are any braces/brackets/parentheses
    bool badlyMatched = false;  // Flag to track if there's a mismatch

    for (int i = 0; i < expression.length(); ++i) {
        char ch = expression[i];

        // Check if it's an opening symbol
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push({ch, i});
            hasBraces = true;

        // Check if it's a closing symbol
        } else if (ch == ')' || ch == ']' || ch == '}') {
            hasBraces = true;

            // Check if stack is empty or top doesn't match
            if (st.empty()) {
                badlyMatched = true;
                break;
            }

            // Pop the top of the stack and check for a match
            char openSymbol = st.top().first;
            int openPos = st.top().second;
            st.pop();

            // Determine if the opening and closing symbols match
            if ((ch == ')' && openSymbol == '(') ||
                (ch == ']' && openSymbol == '[') ||
                (ch == '}' && openSymbol == '{')) {
                string pairType = string(1, openSymbol) + string(1, ch);
                matches.push_back({pairType, openPos, i});
            } else {
                badlyMatched = true;
                break;
            }
        }
    }

    // If the stack is not empty, there are unmatched opening symbols
    if (!st.empty()) {
        badlyMatched = true;
    }

    // Output results
    if (badlyMatched) {
        cout << "badly matched pairs" << endl;
    } else if (!hasBraces) {
        cout << "no brides and grooms to marry" << endl;
    } else {
        for (const auto& match : matches) {
            cout << match.type << " " << match.openPos << " " << match.closePos << endl;
        }
    }

    return 0;
}


