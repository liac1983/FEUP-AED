#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Directions for 8-connected neighbors (diagonais, horizontais e verticais)
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
// Função DFS para explorar uma região conectada no grid
int dfs(vector<string>& grid, vector<vector<bool>>& visited, int x, int y, int rows, int cols) {
    visited[x][y] = true; // Marca a célula atual como visitada
    int size = 1;// Inicia o tamanho do componente conectado com 1 (a célula atual)

    // Explore all 8-connected neighbors
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k];// calcula a nova posição 
        int ny = y + dy[k];
        // Verifica os limites do grid e se o vizinho é parte de um micróbio (`#`) e ainda não foi visitado
        // Check boundaries and if the cell is unvisited and part of a microbe
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny] && grid[nx][ny] == '#') {
            size += dfs(grid, visited, nx, ny, rows, cols); // Realiza DFS recursivo no vizinho
        }
    }

    return size; // Retorna o tamanho total da região conectada
}

int main() {
    int N; // Número de casos de teste
    cin >> N;

    for (int t = 0; t < N; t++) {
        int R, C; // Dimensões do grid (linhas e colunas)
        cin >> R >> C;
        // Lê o grid para representar o ambiente
        vector<string> grid(R);
        for (int i = 0; i < R; i++) {
            cin >> grid[i]; // Cada linha contém a configuração do grid
        }
        // Inicializa a matriz de visitados
        vector<vector<bool>> visited(R, vector<bool>(C, false));

        int numMicrobes = 0;
        int largestMicrobe = 0;

        // Traverse the grid
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                // Verifica se a célula é parte de um micróbio (`#`) e ainda não foi visitada
                if (grid[i][j] == '#' && !visited[i][j]) {
                    // Start a new DFS for this connected component
                    numMicrobes++;
                    int size = dfs(grid, visited, i, j, R, C);
                    largestMicrobe = max(largestMicrobe, size);
                }
            }
        }
        // Exibe o número total de micróbios e o tamanho do maior micróbio
        cout << numMicrobes << " " << largestMicrobe << endl;
    }

    return 0;
}


