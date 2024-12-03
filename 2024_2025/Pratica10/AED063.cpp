#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

const int dx[] = {-1, 1, 0, 0}; // Directions for moving in the grid (up, down, left, right)
const int dy[] = {0, 0, -1, 1};

int main() {
    int R, C;
    cin >> R >> C;

    vector<string> grid(R); // Input grid
    queue<pair<int, int>> q; // Queue for BFS
    vector<vector<int>> dist(R, vector<int>(C, -1)); // Distance from the cloud to each cell
    vector<pair<int, int>> airports; // List of airport positions

    // Read the grid and initialize BFS
    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == '#') {
                q.push({i, j});
                dist[i][j] = 0; // Clouds have distance 0
            } else if (grid[i][j] == 'A') {
                airports.push_back({i, j}); // Record airport positions
            }
        }
    }

    // Perform BFS
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            // Check bounds and if the cell is not yet visited
            if (nx >= 0 && nx < R && ny >= 0 && ny < C && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    // Find the minimum and maximum days for ash cloud to cover airports
    int Nmin = INT_MAX, Nmax = 0;

    for (const auto& [x, y] : airports) {
        if (dist[x][y] != -1) {
            Nmin = min(Nmin, dist[x][y]);
            Nmax = max(Nmax, dist[x][y]);
        }
    }

    cout << Nmin << " " << Nmax << endl;

    return 0;
}
