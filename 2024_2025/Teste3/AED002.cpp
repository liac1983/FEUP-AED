#include <istream>
#include <vector>
#include <algorithm>

using namespace std;

int maxSum(const vector<int> &v) {
    int n = v.size();
    int maxSoFar = v[0];
    int maxEndingHere = v[0];
    for (int i = 1; i < n; i++) { // iterar pela sequencia a partir da segunda posição
        maxEndingHere = max(v[i], maxEndingHere + v[i]); // verificamos se é mehlor contnuar a subsequência atual ou começar uma nova
        maxSoFar = max(maxSoFar, maxEndingHere); // atualizar a soma maxima
    }
    return maxSoFar;
}

int main() {
    int N;
    cin >> N;
    vector<int> sequence(N);
    for (int i = 0; i < N; i++) {
        cin >> sequence[i];
    }
    cout << maxSum(sequence) << endl;
    return 0;
}