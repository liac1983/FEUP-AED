#include <iostream>
#include <vector>

using namespace std;

// Função de merge sort modificada para contar inversões
long long mergeAndCount(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    // Copiar dados para os subarrays temporários
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    long long invCount = 0;

    // Merge das duas metades e contar inversões
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            // Todos os elementos restantes em L[i...n1-1] são maiores que R[j]
            invCount += (n1 - i);
        }
        k++;
    }

    // Copiar os elementos restantes, se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    return invCount;
}

long long mergeSortAndCount(vector<int>& arr, int left, int right) {
    long long invCount = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        invCount += mergeSortAndCount(arr, left, mid);
        invCount += mergeSortAndCount(arr, mid + 1, right);

        invCount += mergeAndCount(arr, left, mid, right);
    }
    return invCount;
}

int main() {
    int N;
    cin >> N;

    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    // Chamar a função de merge sort e contar inversões
    long long result = mergeSortAndCount(arr, 0, N - 1);

    // Imprimir o número de inversões
    cout << result << endl;

    return 0;
}
