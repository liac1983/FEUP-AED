#include "funWithSearch.h"


//=============================================================================
// Exercise 1: Elementary Search
//=============================================================================
// Subexercise 1.1: Linear Search
//=============================================================================
// TODO
int FunWithSearch::searchLinear(const vector<int> &v, int key) {
    for (unsigned i = 0; i < v.size(); i++) {
        if (v[i] == key) {
            return i; // Key found at index i
        }
    }
    return -1; // Key not found
}

//=============================================================================
// Subexercise 1.2: Binary Search
//=============================================================================
// TODO
int FunWithSearch::searchBinary(const vector<int> & v, int key) {
    int low = 0;
    int high = static_cast<int>(v.size()) - 1;

    while (low <= high) {
        int middle = low + (high - low) / 2;

        if (key < v[middle]) {
            high = middle - 1;
        } else if (key > v[middle]) {
            low = middle + 1;
        } else {
            return middle; // Key found at index middle
        }
    }

    return -1; // Key not found
}

//=============================================================================
// Exercise 2: Facing Sun
//=============================================================================
// TODO
int FunWithSearch::facingSun(const vector<int> & values) {
    int count = 0;          // Initialize the count of buildings that see the sunrise.
    int maxHeight = 0;      // Initialize the maximum height seen.

    for (int height : values) {
        if (height > maxHeight) {
            // If the current building is taller than the previous maximum, it can see the sunrise.
            maxHeight = height;
            count++;
        }
    }

    return count;
}


//=============================================================================
// Exercise 3: Square Root
//=============================================================================
// TODO
int FunWithSearch::squareR(int num) {
    if (num <= 1) {
        return num;
    }

    int low = 1;
    int high = num;
    int result = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int square = mid * mid;

        if (square == num) {
            return mid;  // Found the exact square root.
        } else if (square < num) {
            low = mid + 1;
            result = mid;  // Update the result to the current integer part.
        } else {
            high = mid - 1;
        }
    }

    return result;  // Return the largest integer less than or equal to the square root.
}


//=============================================================================
// Exercise 5: MinPages (extra)
//=============================================================================
// TODO

static bool isValidDistribution(const std::vector<int>& values, int numSt, int maxPages) {
    int students = 1;
    int pagesAllocated = 0;

    for (int value : values) {
        if (pagesAllocated + value > maxPages) {
            students++;
            pagesAllocated = value;
            if (students > numSt) {
                return false;
            }
        } else {
            pagesAllocated += value;
        }
    }

    return true;
}
int FunWithSearch::minPages(const vector<int> & values, int numSt) {
    if (numSt <= 0 || values.empty()) {
        return -1;  // Invalid input.
    }

    int totalPages = 0;
    for (int value : values) {
        totalPages += value;
    }

    int low = *std::max_element(values.begin(), values.end());
    int high = totalPages;

    int result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isValidDistribution(values, numSt, mid)) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return result;
}
