#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// informações das equipas
struct Team {
    string name;
    int wins;
    int draws;
    int losses;
    int goals_scored;
    int goals_against;
    int points;
    int goal_average;
    // calcula pontos e golos
    void calculate() {
        points = wins * 3 + draws;
        goal_average = goals_scored - goals_against;
    }
};

bool customComparator(const Team &a, const Team & b) {
    if (a.points != b.points) { // pontos decrescentes
        return a.points > b.points;
    }
    if (a.goal_average != b.goal_average) { // golos decrescentes
        return a.goal_average > b.goal_average;
    }
    return a.name < b.name; // nome crescente
}

int main() {
    int N;
    cin >> N;
    vector<Team> teams(N);
    for (int i = 0; i < N; ++i) { // ler as informações de cada team 
        cin >> teams[i].name >> teams[i].wins >> teams[i].draws >> teams[i].losses
            >> teams[i].goals_scored >> teams[i].goals_against;
            teams[i].calculate(); // calcular os pontos e golos de cada equipa
    }
    // ordena as equipas
    sort(teams.begin(), teams.end(), customComparator);
    for (const auto &team : teams) { // imprime os resultados
        cout << team.name << " " << team.points << " " << team.goal_average << endl;
    }
    return 0;
}
