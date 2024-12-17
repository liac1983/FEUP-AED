#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int main() {
    int N; // numero de eventos
    cin >> N;

    // Define a priority queue of pairs: <price, name> where price is used as the priority
    // preços em ordem decrescente
    priority_queue<pair<int, string>> pq;

    for (int i = 0; i < N; i++) {
        string command;
        cin >> command; // comando "OFFER" ou "SALE"

        if (command == "OFFER") {
            string name; // leia o nome e o preço do lance
            int price;
            cin >> name >> price;
            pq.push({price, name}); // Push the offer into the priority queue
        } 
        else if (command == "SALE") { // vendemos ao maior lance (topo da fila)
            // Sell the card to the highest bidder (top of the priority queue)
            pair<int, string> highestBidder = pq.top(); // // Recupera o maior lance (topo da fila)
            pq.pop(); // Remove the highest bidder from the queue
            cout << highestBidder.first << " " << highestBidder.second << endl;
            // Imprime o preço e o nome do maior lance
        }
    }

    return 0;
}

