#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

class FunWithGraphs {
public:
    static int countLakes(int rows, int cols, const string m[]);
    static int reduceLakes(int rows, int cols, const string m[], int k);
};

int FunWithGraphs::countLakes(int rows, int cols, const string m[]) {
    // Matriz de visited para marcar células já processadas
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    // Direções para verificar as 8 vizinhanças (horizontal, vertical e diagonal)
    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    // Função para realizar BFS e marcar todas as células conectadas do lago
    auto bfs = [&](int startRow, int startCol) {
        queue<pair<int, int>> q;
        q.push({startRow, startCol});
        visited[startRow][startCol] = true;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            // Verificar todas as direções possíveis
            for (const auto& [dr, dc] : directions) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visited[nr][nc] && m[nr][nc] == '.') {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    };

    int lakeCount = 0;

    // Percorrer todas as células do mapa
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Encontrar uma célula de água não visitada
            if (m[i][j] == '.' && !visited[i][j]) {
                ++lakeCount; // Encontramos um novo lago
                bfs(i, j);   // Processar todas as células do lago
            }
        }
    }

    return lakeCount;
}


int FunWithGraphs::reduceLakes(int rows, int cols, const string m[], int k) {
    // Matriz de visited para marcar células já processadas
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    // Direções para verificar as 8 vizinhanças (horizontal, vertical e diagonal)
    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    // Função para realizar BFS e calcular o tamanho do lago
    auto bfs = [&](int startRow, int startCol) -> int {
        queue<pair<int, int>> q;
        q.push({startRow, startCol});
        visited[startRow][startCol] = true;

        int size = 0;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            size++;

            // Verificar todas as direções possíveis
            for (const auto& [dr, dc] : directions) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !visited[nr][nc] && m[nr][nc] == '.') {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }

        return size; // Retorna o tamanho do lago
    };

    // Descobrir todos os lagos e seus tamanhos
    vector<int> lakeSizes;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (m[i][j] == '.' && !visited[i][j]) {
                lakeSizes.push_back(bfs(i, j));
            }
        }
    }

    // Ordenar os tamanhos dos lagos em ordem crescente
    sort(lakeSizes.begin(), lakeSizes.end());

    // Precisamos reduzir o número de lagos para `k`
    int lakesToRemove = lakeSizes.size() - k;

    // Soma dos menores lagos a serem removidos
    int cellsToConvert = accumulate(lakeSizes.begin(), lakeSizes.begin() + lakesToRemove, 0);

    return cellsToConvert;
}