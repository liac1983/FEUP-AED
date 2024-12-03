#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Estrutura para representar o estado do tabuleiro e a sequência de movimentos
struct State {
    vector<int> board;
    string moves;

    State(vector<int> b, string m = "") : board(move(b)), moves(move(m)) {}

    // Transformação A: troca as linhas superior e inferior
    State transformA() const {
        vector<int> newBoard = board;
        swap_ranges(newBoard.begin(), newBoard.begin() + 4, newBoard.begin() + 4);
        return State(newBoard, moves + "A");
    }

    // Transformação B: desloca os elementos circularmente para a direita
    State transformB() const {
        vector<int> newBoard = {board[3], board[0], board[1], board[2], board[7], board[4], board[5], board[6]};
        return State(newBoard, moves + "B");
    }

    // Transformação C: roda os 4 quadrados centrais no sentido horário
    State transformC() const {
        vector<int> newBoard = board;
        newBoard[1] = board[6];
        newBoard[2] = board[1];
        newBoard[5] = board[2];
        newBoard[6] = board[5];
        return State(newBoard, moves + "C");
    }
};

int main() {
    // Leitura da configuração alvo
    vector<int> target(8);
    for (int &val : target) cin >> val;

    // Configuração inicial
    vector<int> initial = {1, 2, 3, 4, 5, 6, 7, 8};

    // Configuração para BFS
    queue<State> q;
    map<vector<int>, string> visited;

    q.push(State(initial));
    visited[initial] = "";

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        // Verifica se atingiu a configuração alvo
        if (current.board == target) {
            cout << current.moves.size() << endl; // Número mínimo de movimentos
            cout << current.moves << endl;       // Sequência de movimentos
            return 0;
        }

        // Aplica as transformações e insere novos estados na fila
        for (const auto &nextState : {current.transformA(), current.transformB(), current.transformC()}) {
            // Se o estado ainda não foi visitado ou encontramos uma sequência menor lexicograficamente
            if (!visited.count(nextState.board) || nextState.moves < visited[nextState.board]) {
                visited[nextState.board] = nextState.moves;
                q.push(nextState);
            }
        }
    }

    return 0;
}
