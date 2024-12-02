#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Process {
    string name;
    int remainingTime;
};

int main() {
    // Lê o tempo máximo que cada processo pode executar por iteração
    int T;
    cin >> T;
    // Lê o número total de processos
    int N;
    cin >> N;
    // Fila para armazenar os processos (estratégia FIFO - First In, First Out)
    queue<Process> processQueue;
    // Lê os processos e adiciona-os à fila
    for (int i = 0; i < N; ++i) {
        Process p; // Cria um novo processo
        cin >> p.name >> p.remainingTime; // Lê o nome e o tempo restante do processo
        processQueue.push(p); // Adiciona o processo à fila
    }

    int currentTime = 0; // Tempo atual (simulado no sistema)
    int iterations = 0; // Contador de quantas vezes um processo foi atendido
    // Enquanto houver processos na fila
    while (!processQueue.empty()) {
        // Remove o próximo processo da fila
        Process p = processQueue.front();
        processQueue.pop();
        // Caso o processo possa ser concluído no quantum T
        if (p.remainingTime <= T) {
            currentTime += p.remainingTime; // Incrementa o tempo atual pelo tempo restante do processo
            iterations++;
            cout << p.name << " " << currentTime << " " << iterations << endl;
        } else {
            // Caso o processo não possa ser concluído no quantum T
            currentTime += T; // Incrementa o tempo atual pelo quantum T
            iterations++;
            p.remainingTime -= T; // Reduz o tempo restante do processo
            processQueue.push(p); // Reinsere o processo na fila para continuar sua execução
        }
    }

    return 0;
}

