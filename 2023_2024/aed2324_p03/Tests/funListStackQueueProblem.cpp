#include "funListStackQueueProblem.h"
#include "cell.h"

FunListStackQueueProblem::FunListStackQueueProblem() {}


//=============================================================================
// Exercise 1: Remove Higher
//=============================================================================
// TODO
list<int> FunListStackQueueProblem::removeHigher(list<int> &values, int x) {
    list<int> l1;

    // Iterate through the 'values' list
    auto it = values.begin();
    while (it != values.end()) {
        if (*it > x) {
            // If the current element is greater than x, remove it from 'values' and add it to 'l1'
            l1.push_back(*it);
            it = values.erase(it); // Erase the current element from 'values' and move the iterator
        } else {
            ++it; // Move to the next element in 'values'
        }
    }
    return l1;
}


//=============================================================================
// Exercise 2: Overlapping Intervals
//=============================================================================
//TODO

bool compareIntervals(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    // Compare based on the starting point of intervals
    return a.first < b.first;
}

list<pair<int,int>> FunListStackQueueProblem::overlappingIntervals(list<pair<int,int>> values) {
    list<pair<int,int>> res;

    // Sort the intervals based on their starting points
    values.sort(compareIntervals);

    // Initialize variables to keep track of the current interval
    int current_start = values.front().first;
    int current_end = values.front().second;

    // Iterate through the sorted intervals
    for (const auto& interval : values) {
        if (interval.first <= current_end) {
            // Overlapping interval found, extend the current interval
            current_end = std::max(current_end, interval.second);
        } else {
            // No overlap with the current interval, add it to the result
            res.push_back(std::make_pair(current_start, current_end));
            // Update current interval to the new one
            current_start = interval.first;
            current_end = interval.second;
        }
    }

    // Add the last merged interval to the result
    res.push_back(std::make_pair(current_start, current_end));
    return res;
}


//=============================================================================
// Exercise 4: Binary Numbers
//=============================================================================
// TODO
vector<string> FunListStackQueueProblem::binaryNumbers(int n) {
    vector<string> res;
    queue<string> q;

    // Start with 1
    q.push("1");

    // Generate binary numbers from 1 to n
    while (n--) {
        string current = q.front();
        q.pop();

        res.push_back(current); // Add the current binary number to the result

        // Append '0' and '1' to the current number to generate the next numbers
        q.push(current + "0");
        q.push(current + "1");
    }
    return res;
}


//=============================================================================
// Exercise 5: Calculate Span
//=============================================================================
//TODO
vector<int> FunListStackQueueProblem::calculateSpan(vector<int> prices) {
    vector<int> res;
    stack<int> s; // Stack to store indices of prices

    // Loop through each day's price
    for (int i = 0; i < prices.size(); ++i) {
        // Pop elements from the stack while the price at the top is less than or equal to prices[i]
        while (!s.empty() && prices[s.top()] <= prices[i]) {
            s.pop();
        }

        // Calculate the span for the current day
        if (s.empty()) {
            // If the stack is empty, there is no previous day with a higher price
            res.push_back(i + 1);
        } else {
            // Otherwise, the span is the difference between the current day and the previous day with a higher price
            res.push_back(i - s.top());
        }

        // Push the current day's index onto the stack
        s.push(i);
    }
    return res;
}


//=============================================================================
// Exercise 7: Knight Jumps
//=============================================================================
//TODO
int FunListStackQueueProblem::knightJumps(int initialPosx, int initialPosy, int targetPosx, int targetPosy, int n) {
    return -1;
}
