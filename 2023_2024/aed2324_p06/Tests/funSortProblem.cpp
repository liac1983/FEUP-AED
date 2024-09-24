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
    return mergeSort(v, 0, v.size() - 1);
}

unsigned FunSortProblem::mergeAndCountInversions(std::vector<int>& v, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    // Create temporary vectors to hold the two halves
    std::vector<int> left(n1);
    std::vector<int> right(n2);

    // Copy data to temporary vectors left[] and right[]
    for (int i = 0; i < n1; i++)
        left[i] = v[low + i];
    for (int j = 0; j < n2; j++)
        right[j] = v[mid + 1 + j];

    // Merge the two halves back into the original vector v
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = low; // Initial index of merged subarray
    unsigned inversionCount = 0;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            v[k] = left[i];
            i++;
        } else {
            v[k] = right[j];
            // Count inversions during merge
            inversionCount += (mid - i + 1);
            j++;
        }
        k++;
    }

    // Copy the remaining elements of left[], if there are any
    while (i < n1) {
        v[k] = left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of right[], if there are any
    while (j < n2) {
        v[k] = right[j];
        j++;
        k++;
    }

    return inversionCount;
}

unsigned FunSortProblem::mergeSort(std::vector<int>& v, int low, int high) {
    unsigned inversionCount = 0;

    if (low < high) {
        // Same as (low + high) / 2, but avoids overflow
        int mid = low + (high - low) / 2;

        // Recursive calls to sort the two halves and count inversions
        inversionCount += mergeSort(v, low, mid);
        inversionCount += mergeSort(v, mid + 1, high);

        // Merge the sorted halves and count inversions
        inversionCount += mergeAndCountInversions(v, low, mid, high);
    }

    return inversionCount;
}


//=============================================================================
// Exercise 7: Nuts and Bolts (extra)
//=============================================================================
// TODO
void FunSortProblem::nutsBolts(vector<Piece> &nuts, vector<Piece> &bolts) {
}
