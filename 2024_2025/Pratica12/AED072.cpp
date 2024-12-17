#include <iostream>
#include <vector>
#include <string>

// Function to determine heap type for a given array
std::string checkHeap(const std::vector<int>& arr) {
    bool isMaxHeap = true; //Flag para verificar se é maxHeap minHep
    bool isMinHeap = true;
    int n = arr.size(); // tamanho do array
    // Iterra por todos os nós que possuem filhos
    for (int i = 1; i <= n / 2; i++) {
        int left = 2 * i; // indice do filho da esquerda e da direita
        int right = 2 * i + 1;

        // Check left child
        if (left <= n) {
            if (arr[i - 1] < arr[left - 1]) isMaxHeap = false; // Não é max 
            if (arr[i - 1] > arr[left - 1]) isMinHeap = false; // não é min
        }

        // Check right child
        if (right <= n) {
            if (arr[i - 1] < arr[right - 1]) isMaxHeap = false;
            if (arr[i - 1] > arr[right - 1]) isMinHeap = false;
        }
    }
    // Retornar o tipo de heap baseado nas flags
    if (isMaxHeap && isMinHeap) return "max or min heap"; // caso em que todos os elementos são iguais
    if (isMaxHeap) return "max heap"; 
    if (isMinHeap) return "min heap";
    return "none";
}

int main() {
    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        int L;
        std::cin >> L;
        std::vector<int> arr(L);
        for (int j = 0; j < L; j++) {
            std::cin >> arr[j];
        }
        std::cout << checkHeap(arr) << std::endl;
    }

    return 0;
}

