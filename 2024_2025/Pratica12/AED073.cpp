#include <iostream>
#include <vector>
#include <queue>

// Function to calculate minimum cost to connect all ropes
long long minimumCostToConnectRopes(std::vector<int>& ropes) {
    // Min-heap priority queue
    // para armazenar os comprimentos das cordas
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    
    // Insert all rope lengths into the priority queue
    for (int rope : ropes) {
        minHeap.push(rope);
    }

    long long totalCost = 0;

    // While more than one rope remains
    while (minHeap.size() > 1) {
        // Extract the two smallest ropes
        int rope1 = minHeap.top(); minHeap.pop(); // menor 
        int rope2 = minHeap.top(); minHeap.pop(); // segundo menor

        // Calculate the cost of connecting these two ropes
        int cost = rope1 + rope2;
        totalCost += cost; 

        // Insert the new combined rope back into the heap
        minHeap.push(cost);
    }
    // retorna o custo total para conectar todas as cordas
    return totalCost;
}

int main() {
    int N;
    std::cin >> N;

    std::vector<int> ropes(N);
    for (int i = 0; i < N; i++) {
        std::cin >> ropes[i];
    }

    // Calculate and print the minimum cost
    std::cout << minimumCostToConnectRopes(ropes) << std::endl;
    return 0;
}
