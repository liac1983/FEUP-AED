#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Estrutura para armazenar as informações do time
struct Team {
    string name;
    int wins;
    int draws;
    int losses;
    int goals_scored;
    int goals_against;
    int points;
    int goal_average;

    // Função para calcular pontos e saldo de gols
    void calculate() {
        points = wins * 3 + draws;
        goal_average = goals_scored - goals_against;
    }
};

// Comparador personalizado
bool customComparator(const Team &a, const Team &b) {
    // Critério 1: Pontos (decrescente)
    if (a.points != b.points) {
        return a.points > b.points;
    }
    // Critério 2: Saldo de gols (decrescente)
    if (a.goal_average != b.goal_average) {
        return a.goal_average > b.goal_average;
    }
    // Critério 3: Nome (crescente)
    return a.name < b.name;
}

int main() {
    int N;
    cin >> N;

    vector<Team> teams(N);

    // Ler as informações de cada time
    for (int i = 0; i < N; ++i) {
        cin >> teams[i].name >> teams[i].wins >> teams[i].draws >> teams[i].losses
            >> teams[i].goals_scored >> teams[i].goals_against;
        // Calcular pontos e saldo de gols para o time atual
        teams[i].calculate();
    }

    // Ordenar os times com base no comparador personalizado
    sort(teams.begin(), teams.end(), customComparator);

    // Imprimir o resultado
    for (const auto &team : teams) {
        cout << team.name << " " << team.points << " " << team.goal_average << endl;
    }

    return 0;
}
