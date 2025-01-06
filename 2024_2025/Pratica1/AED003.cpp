#include <iostream>
#include <vector>

using namespace std;

int countValidSections(int N, int K, int T, const vector<int> &depths) {
    int validSections = 0;
    int count = 0;

    for (int i = 0; i < K; i++) {
        if (depths[i] > T) {
            count++;
        }
    }

    if (count >= (K + 1) / 2) {
        validSections++;
    }

    for (int i = K; i < N; i++) {
        if (depths[i - K] >= T) {
            count--;
        }

        if (depths[i] >= T) {
            count++;
        }
        if (count >= (K+1)/2) {
            validSections++;
        }
    }

    return validSections;
}

int main() {
    int N, K, T;
    cin >> N >> K >> T;

    vector<int> depths(N);
    for (int i = 0; i < N; i++) {
        cin >> depths[i];
    }

    cout << countValidSections(N, K, T, depths) << endl;

    return 0;
}

