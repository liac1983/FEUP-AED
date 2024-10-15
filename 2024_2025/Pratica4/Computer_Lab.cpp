#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max_students_in_lab(int N, vector<pair<int, int>> &times) {
    vector<pair<int, int>> events;

    // Passo 1: Criar eventos de chegada e partida para cada estudante
    for (int i = 0; i < N; ++i) {
        int Ai = times[i].first;
        int Li = times[i].second;
        events.push_back({Ai, 1});  // Evento de chegada (+1)
        events.push_back({Li, -1}); // Evento de partida (-1)
    }

    // Passo 2: Ordenar os eventos por tempo. Em caso de empate, chegada vem antes da partida
    sort(events.begin(), events.end());

    // Passo 3: Atravessar os eventos e contar o número máximo de alunos no laboratório
    int max_students = 0;
    int current_students = 0;

    for (const auto &event : events) {
        current_students += event.second;
        if (current_students > max_students) {
            max_students = current_students;
        }
    }

    return max_students;
}

int main() {
    int N;
    cin >> N;

    vector<pair<int, int>> times(N);
    for (int i = 0; i < N; ++i) {
        cin >> times[i].first >> times[i].second;
    }

    cout << max_students_in_lab(N, times) << endl;

    return 0;
}
