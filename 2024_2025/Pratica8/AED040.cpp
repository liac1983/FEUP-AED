/*#include <iostream>
#include <set>

using namespace std;

int main() {
    int C, B;
    cin >> C;

    set<int> collection;
    for (int i = 0; i < C; i++) {
        int sticker;
        cin >> sticker;
        collection.insert(sticker);
    }

    cin >> B;
    set<int> newStickers;
    for (int i = 0; i < B; i++) {
        int sticker;
        cin >> sticker;
        if (collection.find(sticker) == collection.end()) {
            newStickers.insert(sticker);
        }
    }

    // Output the number of new stickers
    cout << newStickers.size() << endl;

    // If there are new stickers, print them
    if (!newStickers.empty()) {
        for (auto sticker : newStickers) {
            cout << sticker << " ";
        }
        cout << endl;
    }

    return 0;
}*/

#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    int C, B;

    // Input number of stickers in the collection
    cin >> C;
    set<int> collection;
    for (int i = 0; i < C; i++) {
        int sticker;
        cin >> sticker;
        collection.insert(sticker);  // Add to set, removes duplicates
    }

    // Input number of stickers in the bag
    cin >> B;
    set<int> new_stickers;
    for (int i = 0; i < B; i++) {
        int sticker;
        cin >> sticker;

        // Check if the sticker is new
        if (collection.find(sticker) == collection.end()) {
            new_stickers.insert(sticker);
        }
    }

    // Output the count of new stickers
    cout << new_stickers.size() << endl;

    // Output the new stickers in sorted order, if any
    if (!new_stickers.empty()) {
        for (auto sticker : new_stickers) {
            cout << sticker << " ";
        }
        cout << endl;
    }

    return 0;
}
