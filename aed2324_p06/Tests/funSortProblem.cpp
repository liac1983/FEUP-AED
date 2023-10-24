#include "funSortProblem.h"

FunSortProblem::FunSortProblem() {}


//=============================================================================
// Exercise 4: Min Difference
//=============================================================================
// TODO
int FunSortProblem::minDifference(const vector<unsigned> &values, unsigned nc) {
    if (nc > values.size()) {
        return -1;
    }

    std::vector<unsigned> sortedValues = values;
    std::sort(sortedValues.begin(), sortedValues.end());

    int minDiff = sortedValues[nc - 1] - sortedValues[0];

    for (unsigned i = 1; i + nc - 1 < values.size(); i++) {
        int diff = sortedValues[i + nc - 1] - sortedValues[i];
        minDiff = std::min(minDiff, diff);
    }

    return minDiff;
}


//=============================================================================
// Exercise 6: Num Inversions (extra)
//=============================================================================
//TODO
unsigned FunSortProblem::numInversions(vector <int> v) {
    return 0;
}


//=============================================================================
// Exercise 7: Nuts and Bolts (extra)
//=============================================================================
// TODO
void FunSortProblem::nutsBolts(vector<Piece> &nuts, vector<Piece> &bolts) {
}
