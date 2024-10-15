#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;


string sortPhrase(const string &s) {
    string result;
    for (char c : s ){
        if (!isspace(c)) {
            result += tolower(c);
        }
    }

    sort(result.begin(), result.end());

    return result;
}

int main() {

    cout << sortPhrase("seat") << endl;
    cout << sortPhrase("logarithm") << endl;
    cout << sortPhrase("I am Lord Voldemort") << endl;

    return 0;
}
