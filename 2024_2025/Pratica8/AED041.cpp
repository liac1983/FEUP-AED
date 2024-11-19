#include <iostream>
#include <set>

using namespace std;

int main() {
    int A, B;

    // Input Alice's deck
    cin >> A;
    multiset<int> aliceDeck;
    for (int i = 0; i < A; i++) {
        int card;
        cin >> card;
        aliceDeck.insert(card);
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
    while (!aliceDeck.empty() && !bobDeck.empty()) {
        // Get the highest cards
        auto aliceCard = prev(aliceDeck.end());
        auto bobCard = prev(bobDeck.end());

        int A = *aliceCard;
        int B = *bobCard;

        // Remove both cards from the multisets
        aliceDeck.erase(aliceCard);
        bobDeck.erase(bobCard);

        // Determine the winner of the round
        if (A > B) {
            aliceDeck.insert(A - B); // Alice keeps her card with reduced energy
        } else if (A < B) {
            bobDeck.insert(B - A); // Bob keeps his card with reduced energy
        }
        // If A == B, both cards are simply removed
    }

    // Determine and print the result
    if (aliceDeck.empty() && bobDeck.empty()) {
        cout << "Tie" << endl;
        cout << 0 << endl;
    } else if (!aliceDeck.empty()) {
        cout << "Alice wins" << endl;
        cout << aliceDeck.size() << endl;
    } else {
        cout << "Bob wins" << endl;
        cout << bobDeck.size() << endl;
    }

    return 0;
}

