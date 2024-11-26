#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Directions for 8-connected neighbors
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int dfs(vector<string>& grid, vector<vector<bool>>& visited, int x, int y, int rows, int cols) {
    visited[x][y] = true;
    int size = 1;

    // Explore all 8-connected neighbors
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];

        // Check boundaries and if the cell is unvisited and part of a microbe
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny] && grid[nx][ny] == '#') {
            size += dfs(grid, visited, nx, ny, rows, cols);
        }
    }

    return size;
}

int main() {
    int N;
    cin >> N;

    for (int t = 0; t < N; t++) {
        int R, C;
        cin >> R >> C;

        vector<string> grid(R);
        for (int i = 0; i < R; i++) {
            cin >> grid[i];
        }

        vector<vector<bool>> visited(R, vector<bool>(C, false));

        int numMicrobes = 0;
        int largestMicrobe = 0;

        // Traverse the grid
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == '#' && !visited[i][j]) {
                    // Start a new DFS for this connected component
                    numMicrobes++;
                    int size = dfs(grid, visited, i, j, R, C);
                    largestMicrobe = max(largestMicrobe, size);
                }
            }
        }

        cout << numMicrobes << " " << largestMicrobe << endl;
    }

    return 0;
}


