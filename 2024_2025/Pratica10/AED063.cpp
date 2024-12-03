#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;
// Vetores para mover no grid (cima, baixo, esq, dir)
const int dx[] = {-1, 1, 0, 0}; // Directions for moving in the grid (up, down, left, right)
const int dy[] = {0, 0, -1, 1};

int main() {
    // Lê as dimenssões do grid (linhas e colunas)
    int R, C;
    cin >> R >> C;
    // ARmazena o grid como uma matriz de caracteres
    vector<string> grid(R); // Input grid
    // Fila para a BFS (busca em largura)
    // Matriz de distancias da nuvem de cinzas para cada célula 
    // Lista de posições dos aeroportos
    queue<pair<int, int>> q; // Queue for BFS
    vector<vector<int>> dist(R, vector<int>(C, -1)); // Distance from the cloud to each cell
    vector<pair<int, int>> airports; // List of airport positions

    // Read the grid and initialize BFS
    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == '#') {
                // Adiciona as posições das nuvens iniciais à fila 
                q.push({i, j});
                // A distancia de uma nuvem para si mesma é 0
                dist[i][j] = 0; // Clouds have distance 0
            } else if (grid[i][j] == 'A') {
                // Regista as posições dos aeroportos
                airports.push_back({i, j}); // Record airport positions
            }
        }
    }

    // Perform BFS para calcular a menor distancia da nuvem de cinzas para cada celula
    while (!q.empty()) {
        auto [x, y] = q.front(); // Proximo elemento da fila
        q.pop();
        // Tenta visitar as 4 direções 
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d]; // novas coordenadas
            int ny = y + dy[d];

            // Check bounds and if the cell is not yet visited
            if (nx >= 0 && nx < R && ny >= 0 && ny < C && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1; // Aatualiza a distancia
                q.push({nx, ny}); // Adiciona a nova posição à fila
            }
        }
    }

    // Find the minimum and maximum days for ash cloud to cover airports
    int Nmin = INT_MAX, Nmax = 0;
    // Itera sobre todos os aeroportos para calcular os tempos
    for (const auto& [x, y] : airports) {
        if (dist[x][y] != -1) { // Se o aeroporto foi alcançado pelas cinzas
            Nmin = min(Nmin, dist[x][y]); // menor tempo
            Nmax = max(Nmax, dist[x][y]); // maior tempo
        }
    }

    cout << Nmin << " " << Nmax << endl;

    return 0;
}
