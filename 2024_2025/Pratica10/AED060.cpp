#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>

using namespace std;

// Directions for moving in the grid (up, down, left, right)
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

// Function to perform BFS and find the shortest path to the treasure
int findShortestPath(vector<string> &maze, int R, int C, pair<int, int> start, pair<int, int> target) {
    // Distance matrix to store the number of steps to each cell
    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int, int>> q;

    // Start BFS from the player's position
    q.push(start);
    dist[start.first][start.second] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // If we reach the treasure, return the distance
        if (x == target.first && y == target.second) {
            return dist[x][y];
        }

        // Explore all 4 possible moves
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Check bounds and whether the cell is traversable and unvisited
            if (nx >= 0 && nx < R && ny >= 0 && ny < C && maze[nx][ny] != '#' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return -1; // Should not reach here as path is guaranteed
}

int main() {
    int N;
    cin >> N;

    while (N--) {
        int R, C;
        cin >> R >> C;
        vector<string> maze(R);

        pair<int, int> start, target;

        // Read the maze and locate the player (P) and the treasure (T)
        for (int i = 0; i < R; ++i) {
            cin >> maze[i];
            for (int j = 0; j < C; ++j) {
                if (maze[i][j] == 'P') {
                    start = {i, j};
                } else if (maze[i][j] == 'T') {
                    target = {i, j};
                }
            }
        }

        // Perform BFS to find the shortest path to the treasure
        cout << findShortestPath(maze, R, C, start, target) << endl;
    }

    return 0;
}

