#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    // Map to store statistics for each movie
    map<string, pair<int, int>> movieStats;

    // Read reviews
    for (int i = 0; i < N; i++) {
        string movieName;
        int score;
        cin >> movieName >> score;

        // Update statistics
        movieStats[movieName].first++;                // Total reviews
        if (score >= 5) {
            movieStats[movieName].second++;           // Positive reviews
        }
    }

    // Statistics to calculate
    int numMovies = movieStats.size();
    int maxReviews = 0;
    int moviesWithMaxReviews = 0;
    int morePositiveMovies = 0;

    // Analyze map
    for (const auto &entry : movieStats) {
        const auto &[movie, stats] = entry;
        int totalReviews = stats.first;
        int positiveReviews = stats.second;

        // Update maximum reviews stats
        if (totalReviews > maxReviews) {
            maxReviews = totalReviews;
            moviesWithMaxReviews = 1;
        } else if (totalReviews == maxReviews) {
            moviesWithMaxReviews++;
        }

        // Check for more positive reviews
        if (positiveReviews > totalReviews / 2) {
            morePositiveMovies++;
        }
    }

    // Output results
    cout << numMovies << endl;
    cout << maxReviews << " " << moviesWithMaxReviews << endl;
    cout << morePositiveMovies << endl;

    return 0;
}


