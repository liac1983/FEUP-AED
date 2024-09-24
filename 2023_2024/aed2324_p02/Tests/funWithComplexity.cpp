#include "funWithComplexity.h"

//=============================================================================
// Exercise 4: Analyzing a river
//=============================================================================
// TODO
int FunWithComplexity::river(const vector<int> & v, int k, int t) {
    int n = v.size();
    int satisfactoryRegions = 0;
    int depthGreaterThanTEndCount = 0;

    for (int i = 0; i < n; ++i) {
        if (v[i] >= t) {
            depthGreaterThanTEndCount++;
        }

        if (i >= k - 1) { // Check if we have a valid window of size k
            int windowSize = i - (i - k + 1) + 1; // Calculate the size of the current window

            if (depthGreaterThanTEndCount * 2 >= windowSize) { // Verificamos se pelo menos metade dos locais na janela atual têm uma profundidade maior ou igual a t
                satisfactoryRegions++;
            }

            // Remove the leftmost element from the window
            if (v[i - k + 1] >= t) {
                depthGreaterThanTEndCount--;
            }
        }
    }

    return satisfactoryRegions;
}

//=============================================================================
// Exercise 5: Spiral of Numbers
//=============================================================================
// TODO
pair<int, int> FunWithComplexity::spiral(int n) {
    /*
    pair<int, int> ans = {0, 0};
    return ans;
     */
    int x = 0, y = 0;
    int dx = 0, dy = -1;
    int steps = 1, step_size = 1;

    for (int i = 2; i <= n; ++i) {
        x += dx;
        y += dy;

        if (steps == step_size) {
            // Change direction
            if (dx == 0) {
                dx = dy;
                dy = 0;
            } else {
                dy = -dx;
                dx = 0;
                step_size += 1;
            }
            steps = 1;
        } else {
            steps += 1;
        }
    }

    return make_pair(-y, x);
/*
    if (n == 1)
        return {0, 0};

    int k = ceil(sqrt(n));
    if (k % 2 == 0)
        k++; // Ensure k is an odd number

    int layer_max = k * k;
    int layer_size = k - 1;
    int offset = layer_max - n;

    int x, y;

    if (offset < layer_size) {
        x = layer_size / 2;
        y = offset - layer_size / 2;
    } else if (offset < 2 * layer_size) {
        x = offset - layer_size / 2;
        y = layer_size / 2;
    } else if (offset < 3 * layer_size) {
        x = layer_size / 2;
        y = layer_size / 2 - (offset - 2 * layer_size);
    } else {
        x = layer_size / 2 - (offset - 3 * layer_size);
        y = layer_size / 2;
    }

    return {x, y};
    */
}


//=============================================================================
// Exercise 7: Squared notebook
//=============================================================================
// TODO
long long FunWithComplexity::gridSum(int a, int b) {
    long long sum = 0;
    for (int i = a; i <= b; i++) {
        int rowStart = i * (i - 1) / 2 + 1; // Starting number of the ith row
        int rowEnd = (i + 1) * i / 2;       // Ending number of the ith row
        for (int j = rowStart; j <= rowEnd; j++) {
            if (j >= a && j <= b) {
                sum += j; // Add numbers within the specified range
            }
        }
    }
    return sum;
}