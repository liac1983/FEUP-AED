#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    map<int, int> frequency; // Map to count occurrences of each number

    // Read the sequence and populate the map
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        frequency[num]++;
    }

    // Calculate the total number of removals
    int removals = 0;
    for (const auto &entry : frequency) {
        int x = entry.first;  // The number
        int f = entry.second; // Frequency of the number

        if (f < x) {
            // If frequency is less than the number, remove all occurrences
            removals += f;
        } else {
            // If frequency is greater, remove excess occurrences
            removals += f - x;
        }
    }

    // Output the total removals
    cout << removals << endl;

    return 0;
}

