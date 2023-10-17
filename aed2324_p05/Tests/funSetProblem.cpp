#include "funSetProblem.h"

FunSetProblem::FunSetProblem() {}


//=============================================================================
// Exercise 2: FunSetProblem
//=============================================================================
// TODO
pair<int, int> FunSetProblem::pairSum(const vector<int> &values, int sum) {
    // Crie uma árvore de busca binária para armazenar os valores
    set<int> valueSet;

    for (int value : values) {
        // Calcule a diferença entre o valor desejado e o valor atual
        int difference = sum - value;

        // Verifique se a diferença já está na árvore (ou seja, fazendo um par)
        if (valueSet.find(difference) != valueSet.end()) {
            return make_pair(difference, value);
        }

        // Adicione o valor atual à árvore
        valueSet.insert(value);
    }

    // Nenhum par encontrado
    return make_pair(0, 0);
}

