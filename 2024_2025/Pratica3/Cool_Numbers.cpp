#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Função para calcular a soma dos dígitos de um número representado como string
int digitSum(const string& num) {
    int sum = 0;
    for (char c : num) {
        sum += c - '0';
    }
    return sum;
}

// Função para incrementar os dígitos eficientemente
void increment(string& num) {
    int n = num.size();
    for (int i = n - 1; i >= 0; --i) {
        if (num[i] == '9') {
            num[i] = '0';  // "Carrega" o dígito, levando-o para 0
        } else {
            num[i]++;  // Incrementa o dígito
            return;
        }
    }
    // Se todos os dígitos forem "carregados", adicione um '1' no início
    num = "1" + num;
}

// Função para encontrar o menor número maior que N com soma de dígitos igual a K
long long findCoolNumber(long long N, int K) {
    string current = to_string(N + 1);  // Começa do próximo número após N

    // Continua até encontrar o número com soma de dígitos igual a K
    while (digitSum(current) != K) {
        increment(current);  // Incrementa eficientemente o número
    }

    return stoll(current);  // Converte de volta para long long e retorna
}

int main() {
    int T;
    cin >> T;

    vector<long long> results(T);

    // Processar cada caso de teste
    for (int i = 0; i < T; i++) {
        long long Ni;
        int Ki;
        cin >> Ni >> Ki;
        
        results[i] = findCoolNumber(Ni, Ki);
    }

    // Mostrar os resultados para cada caso de teste
    for (long long result : results) {
        cout << result << endl;
    }

    return 0;
}
