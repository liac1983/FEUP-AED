#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

vector<int> findWinningTickets(int N, int K, int W) {
    deque<int> tickets;
    for (int i = 1; i <= N; ++i) {
        tickets.push_back(i);
    }

    vector<int> winners;
    int index = 0;

    while ((int)tickets.size() > W) {
        index = (index + K - 1) % tickets.size();
        tickets.erase(tickets.begin() + index);
    }

    winners.assign(tickets.begin(), tickets.end());
    sort(winners.begin(), winners.end());

    return winners;
}

int main() {
    int N, K, W;
    cin >> N >> K >> W;

    vector<int> winners = findWinningTickets(N, K, W);

    for (int ticket : winners) {
        cout << ticket << endl;
    }

    return 0;
}


