#include <iostream>
#include "funWithGraphs.h"

using namespace std;

int main() {
    string m[] = {
        "###############",
        "#..##...####..#",
        "#..###.#.###..#",
        "############..#",
        "####...###....#",
        "#..##...#######"
    };

    cout << FunWithGraphs::countLakes(6, 15, m) << endl; // Esperado: 5
    return 0;
}
