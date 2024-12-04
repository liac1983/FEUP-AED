#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N; // Numero de reviews

    // Map to store statistics for each movie
    // numero de reviews total
    // numero de reviews positivo
    map<string, pair<int, int>> movieStats;

    // Read reviews
    for (int i = 0; i < N; i++) {
        string movieName; // Nome do filme 
        int score; // review
        cin >> movieName >> score;

        // Update statistics
        movieStats[movieName].first++;  // Incrementar o numero total de reviews              // Total reviews
        if (score >= 5) {
            movieStats[movieName].second++;           // Positive reviews
        }
    }

    // Statistics to calculate
    int numMovies = movieStats.size(); // Numero de filmes
    int maxReviews = 0; // maximo de reviews para cada filme
    int moviesWithMaxReviews = 0; // quantidade de filmes com o maximo de reviews
    int morePositiveMovies = 0; // numero de filmes com mais de 50% das reviews positivas

    // Analyze map
    for (const auto &entry : movieStats) {
        const auto &[movie, stats] = entry;
        int totalReviews = stats.first; // total de reveiews 
        int positiveReviews = stats.second; // reviews positivas

        // Update maximum reviews stats
        if (totalReviews > maxReviews) {
            maxReviews = totalReviews; // novo maximo encontrado 
            moviesWithMaxReviews = 1; // Reinicia a contagem de filmes com o novo maximo
        } else if (totalReviews == maxReviews) {
            moviesWithMaxReviews++; // Incrementa se outro filme tem o mesmo numero maximo de reviews
        }

        // Check for more positive reviews
        if (positiveReviews > totalReviews / 2) {
            morePositiveMovies++;
        }
    }

    // Output results
    cout << numMovies << endl;
    cout << maxReviews << " " << moviesWithMaxReviews << endl;
    cout << morePositiveMovies << endl; // numero de filmes com reviews positivas 

    return 0;
}


