#include <iostream>
#include <cmath>
using namespace std;


long long is_prime(long long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2) return false;
    for (long long i = 3; i <= sqrt(n); i += 2 ){
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++) {
        long long ni;
        cin >> ni;

        if (is_prime(ni)) {
            cout << ni << " is prime" << endl;

        } else {
            cout << ni << " is composite" << endl;
        }
    }

    return 0;
}
