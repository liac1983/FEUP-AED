#include <iostream>
#include <set>

using namespace std;

int main() {
    int A, B; // numero de cartas do baralho da Alice e do Bob

    // Input Alice's deck
    cin >> A;
    // multiset para armazenar as cartas da Alice 
    // permite armazenar multiplas ocorrências do mesmo valor 
    multiset<int> aliceDeck;
    for (int i = 0; i < A; i++) {
        int card;
        cin >> card; // Lê o valor de cada carta
        aliceDeck.insert(card); // Insere a carta no multiset
    }

    // Input Bob's deck
    cin >> B;
    multiset<int> bobDeck;
    for (int i = 0; i < B; i++) {
        int card;
        cin >> card;
        bobDeck.insert(card);
    }

    // Simulate the game
    // O jogo continua enquanto que ambos os baralhos não tiverem vazios
    while (!aliceDeck.empty() && !bobDeck.empty()) {
        // Get the highest cards
        auto aliceCard = prev(aliceDeck.end());
        auto bobCard = prev(bobDeck.end());

        int A = *aliceCard; // valor da carta da Alice
        int B = *bobCard;

        // Remove both cards from the multisets
        aliceDeck.erase(aliceCard);
        bobDeck.erase(bobCard);

        // Determine the winner of the round
        if (A > B) {
            // Alice vence a rodada. Ela matém uma carta com valor reduzido
            aliceDeck.insert(A - B); // Alice keeps her card with reduced energy
        } else if (A < B) {
            // Bob vence ele mantém a carta com valor reduzido
            bobDeck.insert(B - A); // Bob keeps his card with reduced energy
        }
        // If A == B, both cards are simply removed
    }

    // Determine and print the result
    // Se ambos estão vazios é empate
    if (aliceDeck.empty() && bobDeck.empty()) {
        cout << "Tie" << endl;
        cout << 0 << endl;
    // A alice ainda tem cartas por isso vence
    } else if (!aliceDeck.empty()) {
        cout << "Alice wins" << endl;
        cout << aliceDeck.size() << endl;
    } else {
        cout << "Bob wins" << endl;
        cout << bobDeck.size() << endl;
    }

    return 0;
}

