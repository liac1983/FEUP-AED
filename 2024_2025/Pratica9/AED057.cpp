#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
int R, C;

// Function to get the unique ID of a cell part
int getId(int x, int y, int part) {
    return (x * C + y) * 4 + part;
}

// DFS to traverse the implicit graph and find cycles
int dfs(int x, int y, int part, vector<vector<vector<bool>>>& visited, const vector<string>& grid) {
    visited[x][y][part] = true;
    int size = 1;

    // Determine connections within the current cell
    int neighbors[4];
    if (grid[x][y] == '/') {
        neighbors[0] = 3;
        neighbors[1] = 2;
        neighbors[2] = 1;
        neighbors[3] = 0;
    } else { // grid[x][y] == '\\'
        neighbors[0] = 1;
        neighbors[1] = 0;
        neighbors[2] = 3;
        neighbors[3] = 2;
    }

    // Explore neighbors
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];

        // Stay within bounds
        if (nx >= 0 && nx < R && ny >= 0 && ny < C) {
            int nPart = neighbors[i];
            if (!visited[nx][ny][nPart]) {
                size += dfs(nx, ny, nPart, visited, grid);
            }
        }
    }

    return size;
}

int main() {
    cin >> R >> C;
    vector<string> grid(R);
    for (int i = 0; i < R; i++) {
        cin >> grid[i];
    }

    // Visited array for each part of the grid
    vector<vector<vector<bool>>> visited(R, vector<vector<bool>>(C, vector<bool>(4, false)));

    int numCycles = 0, largestCycle = 0;

    // Traverse the grid
    for (int x = 0; x < R; x++) {
        for (int y = 0; y < C; y++) {
            for (int part = 0; part < 4; part++) {
                if (!visited[x][y][part]) {
                    // New connected component
                    int size = dfs(x, y, part, visited, grid);
                    if (size > 1) { // Only count cycles
                        numCycles++;
                        largestCycle = max(largestCycle, size);
                    }
                }
            }
        }
    }

    // Output results
    if (numCycles == 0) {
        cout << "no cycles" << endl;
    } else {
        cout << numCycles << " " << largestCycle << endl;
    }

    return 0;
}
