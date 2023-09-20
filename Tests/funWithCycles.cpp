#include "funWithCycles.h"

//=============================================================================
// Exercise 1: Palindromes
//=============================================================================
// TODO
bool FunWithCycles::palindrome(const std::string & s) {
    unsigned length = s.size();
    for (unsigned i = 0; i < length/2; i++)
        if (s[i] != s[length-i-1])
            return false;
    return true;
}


//=============================================================================
// Exercise 2: Palindrome Sentences
//=============================================================================
// TODO
bool FunWithCycles::palindromeSentence(const std::string & s) {
    // Preprocess the input string
    std::string processedString;
    for (char c : s) {
        if (std::isalpha(c)) {  // Check if it's an alphabetic character
            processedString += std::tolower(c); // Convert to lowercase and append
        }
    }

    // Check if the processed string is a palindrome
    return palindrome(processedString);
}


//=============================================================================
// Exercise 3: Interesting Numbers
//=============================================================================
// TODO
int FunWithCycles::nextInterestingNumber(int n, int sum) {
    // Function to find the smallest number greater than n
    // whose sum of digits is exactly sum

    while (true) {
        n++;  // Increment n to check the next number
        if (digitSum(n) == sum) {
            return n;  // If the digit sum matches the desired sum, return the number
        }
    }
}

// This auxiliary function should return the sum of the digits of n
// TODO
int FunWithCycles::digitSum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;  // Add the last digit to the sum
        n /= 10;       // Remove the last digit
    }
    return sum;
}


//=============================================================================
// Exercise 4: Winter is coming
//=============================================================================
// TODO
int FunWithCycles::winter(const vector<int> & v) {
    if (v.empty()) {
        return 0;  // If the vector is empty, there are no temperature drops.
    }

    int maxSequenceLength = 1;  // Initialize with at least 1 (single day).
    int currentSequenceLength = 1;  // Initialize with 1 for the first day.

    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] < v[i - 1]) {  // Check if the temperature is falling.
            currentSequenceLength++;  // Increment the current sequence length.
        } else {
            currentSequenceLength = 1;  // Reset the sequence length if temperature rises.
        }

        // Update the maximum sequence length found so far.
        if (currentSequenceLength > maxSequenceLength) {
            maxSequenceLength = currentSequenceLength;
        }
    }

    return maxSequenceLength-1;
}


//=============================================================================
// Exercise 5: Playing with vectors
//=============================================================================

// a) count
// TODO
int FunWithCycles::count(const vector<int> & v, int n) {
    int count = 0;  // Initialize a counter to zero.

    // Iterate through the vector and count occurrences of n.
    for (const int &element : v) {
        if (element == n) {
            count++;  // Increment the count when n is found.
        }
    }

    return count;
}

// b) hasDuplicates
// TODO
bool FunWithCycles::hasDuplicates(const vector<int> & v) {
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (v[i] == v[j]) {
                // Found a duplicate element.
                return true;
            }
        }
    }

    // If no duplicates were found, return false.
    return false;
}

// c) removeDuplicates
// TODO
void FunWithCycles::removeDuplicates(vector<int> & v) {
    if (v.empty()) {
        return;  // No duplicates to remove from an empty vector.
    }

    size_t newSize = 1;  // New size of the vector after removing duplicates.

    for (size_t i = 1; i < v.size(); ++i) {
        bool isDuplicate = false;

        // Check if the current element is a duplicate of any previous elements.
        for (size_t j = 0; j < newSize; ++j) {
            if (v[i] == v[j]) {
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            // If it's not a duplicate, copy it to the new part of the vector.
            v[newSize] = v[i];
            newSize++;
        }
    }

    // Resize the vector to the new size to remove duplicates.
    v.resize(newSize);
}

// d) merge
// TODO
vector<int> FunWithCycles::merge(const vector<int> & v1, const vector<int> & v2) {
    vector<int> ans; // The merged result vector;
    size_t i = 0;  // Index for v1.
    size_t j = 0;  // Index for v2.

    // Merge elements from v1 and v2 into ans while maintaining the sorted order.
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] < v2[j]) {
            ans.push_back(v1[i]);
            i++;
        } else {
            ans.push_back(v2[j]);
            j++;
        }
    }

    // Append any remaining elements from v1 and v2 (if any).
    while (i < v1.size()) {
        ans.push_back(v1[i]);
        i++;
    }

    while (j < v2.size()) {
        ans.push_back(v2[j]);
        j++;
    }

    return ans;
}


//=============================================================================
// Exercise 6: Playing with prime numbers
//=============================================================================

// a) isPrime
// TODO
bool FunWithCycles::isPrime(int n) {
    if (n <= 1) {
        return false; // Numbers less than or equal to 1 are not prime.
    }

    // Check for divisibility from 2 to the square root of n.
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false; // Found a divisor, not prime.
        }
    }

    return true; // If no divisors found, it's prime.
}

// b) factorize
// TODO
vector<int> FunWithCycles::factorize(int n) {
    vector<int> ans;

    // Divide n by 2 until it's no longer even
    while (n % 2 == 0) {
        ans.push_back(2);
        n /= 2;
    }

    // Divide n by odd prime numbers starting from 3
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            ans.push_back(i);
            n /= i;
        }
    }

    // If n is still greater than 1, it's a prime factor
    if (n > 1) {
        ans.push_back(n);
    }

    return ans;
}

// c) listPrimes
// TODO
vector<int> FunWithCycles::listPrimes(int n) {
    // Initialize a boolean array to mark numbers as prime or not.
    vector<bool> isPrime(n + 1, true);

    // Mark 0 and 1 as not prime.
    isPrime[0] = isPrime[1] = false;

    // Start from the first prime number (2).
    for (int p = 2; p * p <= n; ++p) {
        // If p is marked as prime, mark its multiples as not prime.
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }

    // Create a vector to store the prime numbers.
    vector<int> ans;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            ans.push_back(i);
        }
    }

    return ans;
}
