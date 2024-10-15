#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to count the number of 1 bits in the binary representation of an integer
int countBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1; // Increment count if the least significant bit is 1
        n >>= 1;        // Right shift n by 1 bit to check the next bit
    }
    return count;
}

// Custom comparator to sort based on the number of 1 bits (descending),
// and by value (ascending) if the number of 1 bits is the same
bool customComparator(int x, int y) {
    int countX = countBits(x);
    int countY = countBits(y);

    // Primary criterion: sort by the number of 1 bits (descending)
    if (countX != countY) {
        return countX > countY; // More 1's should come first
    }

    // Secondary criterion: sort by value (ascending)
    return x < y;
}

int main() {
    int n;
    cin >> n; // Read the number of integers

    vector<int> numbers(n);
    
    // Read the integers
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    // Sort the numbers using the custom comparator
    sort(numbers.begin(), numbers.end(), customComparator);

    // Output the sorted numbers
    for (int i = 0; i < n; i++) {
        cout << numbers[i] << endl;
    }

    return 0;
}
