#include <iostream>
using namespace std;

// Function to find the last negative odd number and count the odd numbers
pair<int, int> find_last_negative_odd_and_count() {
    int num;
    int last_negative_odd = 0; // Initialize with 0 if no negative odd numbers
    int odd_count = 0;         // Counter for odd numbers

    // Read integers until we encounter a 0
    while (true) {
        cin >> num;
        if (num == 0) {
            break; // End of sequence
        }

        // Check if the number is odd
        if (num % 2 != 0) {
            odd_count++; // Increment odd number count

            // Check if the number is a negative odd number
            if (num < 0) {
                last_negative_odd = num; // Update the last negative odd number
            }
        }
    }

    // Return the pair (last negative odd number, count of odd numbers)
    return {last_negative_odd, odd_count};
}

int main() {
    cout << "Enter a sequence of integers ending with 0:" << endl;

    // Call the function to get the result
    pair<int, int> result = find_last_negative_odd_and_count();

    // Output the result
    cout << "Last negative odd number: " << result.first << endl;
    cout << "Total odd numbers: " << result.second << endl;

    return 0;
}

/*
pair<int, int> find_last_negatiove_odd_and_count() {
    int num;
    int last_negative_odd = 0;
    int odd_count = 0;

    while (true) {
        cin >> num;
        if (num == 0) {
            break;
        }
        if (num % 2 != 0) {
            odd_count++;
            if (num < 0) {
                last_negative_odd = num;
            }
        }
    }
    return {last_negative_odd, odd_count};
}*/