#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to factorize n using the provided prime numbers
void prime_factorization(int n, const vector<int>& primes) {
    vector<int> factors; // To store the prime factors

    // Step 1: Try dividing n by each prime number from the list of primes
    for (int prime : primes) {
        // If prime > sqrt(n) and n is still not 1, n is either prime or divisible by a large prime
        if (prime * prime > n) {
            break; // No need to continue beyond sqrt(n)
        }

        // While n is divisible by the prime, divide and store the prime factor
        while (n % prime == 0) {
            factors.push_back(prime);
            n /= prime;
        }
    }

    // Step 2: After trying all primes <= sqrt(n), if n > 1, then n is a prime number or large factor
    if (n > 1) {
        factors.push_back(n);
    }

    // Step 3: Output the factorization
    for (size_t i = 0; i < factors.size(); ++i) {
        if (i > 0) {
            cout << "*";
        }
        cout << factors[i];
    }
    cout << endl;
}

int main() {
    // Example array of primes less than or equal to 1000
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                          73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157,
                          163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241,
                          251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347,
                          349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439,
                          443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547,
                          557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643,
                          647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751,
                          757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859,
                          863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977,
                          983, 991, 997};

    // Test cases
    cout << "Factorization of 124992: ";
    prime_factorization(124992, primes);

    cout << "Factorization of 19: ";
    prime_factorization(19, primes);

    cout << "Factorization of 807200: ";
    prime_factorization(807200, primes);

    return 0;
}

/* void prime_factorization(int n, const vector<int>& primes) {
    vector<int> factors;
    for (int prime : primes) {
        if (prime * prime > n ) {
            break;
        }
        while (n % prime == 0) {
            factors.push_back(prime);

            n /= prime;
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
    for (size_t i = 0; i < factors.size(); ++i) {
        if (i > 0) {
            cout << "*";
        }
        cout << factors[i];
    }
    cout << endl;
} */

