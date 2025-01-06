#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int countBits(int n) {
    int count = 0;
    while(n) {
        count += n & 1;
        n >>= 1;
    }

    return count;
}


bool customComparator(int x, int y) {
    int countX = countBits(x);
    int countY = countBits(y);

    if (countX != countY) {
        return countX > countY;
    }

    return x < y;
}


int main() {
    int n;
    cin >> n;

    vector<int> numbers(n);

    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    sort(numbers.begin(), numbers.end(), customComparator);

    for (int i = 0; i < n; i++) {
        cout << numbers[i] << endl;
    }

    return 0;
}

