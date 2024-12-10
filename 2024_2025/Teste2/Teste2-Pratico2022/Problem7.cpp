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

    cout << FunWithGraphs::reduceLakes(6, 15, m, 3) << endl; // Esperado: 6
    return 0;
}
