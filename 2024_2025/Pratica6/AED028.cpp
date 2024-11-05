#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Process {
    string name;
    int remainingTime;
};

int main() {
    int T;
    cin >> T;

    int N;
    cin >> N;

    queue<Process> processQueue;

    for (int i = 0; i < N; ++i) {
        Process p;
        cin >> p.name >> p.remainingTime;
        processQueue.push(p);
    }

    int currentTime = 0;
    int iterations = 0;
    while (!processQueue.empty()) {
        Process p = processQueue.front();
        processQueue.pop();

        if (p.remainingTime <= T) {
            currentTime += p.remainingTime;
            iterations++;
            cout << p.name << " " << currentTime << " " << iterations << endl;
        } else {
            currentTime += T;
            iterations++;
            p.remainingTime -= T;
            processQueue.push(p);
        }
    }

    return 0;
}

