// AED000 Count42
/* #include <iostream>

using namespace std;

int main() {
    int Q;
    cin >> Q;

    int count42 = 0;

    for (int i = 0; i < Q; i++) {
        int ni;
        cin >> ni;

        if (ni == 42) {
            count42++;
        }
    }

    cout << count42 << endl;
    return 0;

} */

// AED001 Prime Numbers

/* #include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % 1 == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int q;
    cin >> q;

    for (int i = 0;  i < q; i++) {
        int n;
        cin >> n;

        if (isPrime(n)) {
            cout << n << " is prime" << endl;
        } else {
            cout << n << " is composite" << endl;
        }
    }

    return 0;
}
 */

//AED002 Sequence Game
/* #include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxSum(const vector<int> &v) {
    int n = v.size();
    int maxSoFar = v[0];
    int maxEndingHere = v[0];
    
    for (int i = 1; i < n; i++) {
        maxEndingHere = max(v[i], maxEndingHere + v[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);


    }

    return maxSoFar;
}

int main() {
    int N;
    cin >> N;
    vector<int> sequence(N);
    for (int i = 0; i < N; i++) {
        cin >> sequence[i];

    }
    cout << maxSum(sequence) << endl;

    return 0;
} */

// AED003 Saving Pipefish
/* #include <iostream>
#include <vector>

using namespace std;

int countValidSections(int N, int K, int T, const vector<int> &depths) {
    int validSections = 0;
    int count = 0;

    for (int i = 0; i < K; i++) {
        if (depths[i] >= T) {
            count++;
        }
    }

    if (count >= (K+1) /2) {
        validSections++;
    }

    for (int i = K; i < N; i++) {
        if (depths[i - K] >= T) {
            count--;
        }

        if (depths[i] >= T) {
            count++;
        }

        if (count >= (K+1)/2) {
            validSections++;
        }
    }
    return validSections;
}

int main() {
    int N, K, T;

    cin >> N >> K >> T;

    vector<int> depths(N);

    for (int i = 0; i < N; i++) {
        cin >> depths[i];
    }

    cout << countValidSections(N, K, T, depths) << endl;

    return 0;
}
 */

// AED005 Number Searching
/* #include <iostream>
#include <vector>

using namespace std;

int binary_search(const vector<int> &v, int key) {
    int low = 0;
    int high = (int)v.size() -1;

    while (low <= high) {
        int middle = low + (high - low)/2;
        if (key < v[middle]) {
            high = middle - 1;
        } else if (key > v[middle]) {
            low = middle + 1;
        } else {
            return middle;
        }
    }

    return -1;
}

int main() {
    int N, Q;
    cin >> N;
    vector<int> sequence(N);

    for (int i = 0; i < N; i++) {
        cin >> sequence[i];
    }

    cin >> Q;

    for (int i = 0; i < Q; i++) {
        int query;
        cin >> query;

        int result = binary_search(sequence, query);
        cout << result << endl;
    }
    return 0;
}
 */

// AED006 Lower Bound
/* #include <iostream>
#include <vector>

using namespace std;

int lowerBound(const vector<int>& v, int key) {
    int low = 0;
    int high = (int)v.size() -1 ;
    int result = -1;

    while (low <= high) {
        int middle = low + (high - low) / 2;

        if (v[middle] >= key) {
            result = middle;
            high = middle -1;
        } else {
            low = middle + 1;
        }
    } 
    return result;
}

int main() {
    int N, Q;
    cin >> N;

    vector<int> sequence(N);
    for (int i = 0; i < N; i++) {
        cin >> sequence[i];
    }

    cin >> Q;

    for (int i = 0; i < Q; i++) {
        int query;
        cin >> query;

        int result = lowerBound(sequence, query);
        cout << result << endl;
    }

    return 0;
}

 */

// AED007 Interval Count

/* #include <iostream>
#include <vector>

using namespace std;

int lowerBound(const vector<int>& v, int key) {
    int low = 0;
    int high = (int)v.size() - 1;
    int result = (int)v.size();

    while(low <= high) {
        int middle = low + (high - low ) / 2;
        if (v[middle] >= key) {
            result = middle;
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    return result;
}

int upperBound (const vector<int>& v, int key) {
    int low = 0;
    int high = (int)v.size() - 1;
    int result = (int)v.size();

    while(low <= high) {
        int middle = low + (high - low) / 2;
        if (v[middle] > key) {
            result = middle;
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }
    return result;
}

int main() {
    int N, Q;
    cin >> N;
    vector<int> sequence(N);

    for (int i = 0; i < N; i++) {
        cin >> sequence[i];
    }

    cin >> Q;

    for (int i = 0; i< Q; i++) {
        int A, B;
        cin >> A >> B;

        int lower = lowerBound(sequence, A);
        int upper = upperBound(sequence, B);

        int count = upper - lower;

        cout << count << endl;
    }
    return 0;
}
 */

// AED009 Closest Sums
/* #include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

pair<int, int> findClosestSums(const vector<int>& sums, int query) {
    auto it = lower_bound(sums.begin(), sums.end(), query);

    int closest1 = sums[0];
    int closest2 = -1;

    if (it != sums.begin()) {
        int prev_sum = *(it -1);
        if (abs(query - prev_sum) < abs(query - closest1)) {
            closest1 = prev_sum;
        } else if (abs(query - prev_sum) == abs(query - closest1)) {
            closest2 = closest1;
            closest1 = prev_sum;
        }
    }
    return make_pair(closest1, closest2);

}


int main() {
    int N;
    cin >> N;
    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    vector<int> sums;

    for(int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            sums.push_back(S[i] + S[j]);
        }
    }
    sort(sums.begin(), sums.end());

    int Q;
    cin >> Q;

    vector<int> queries(Q);

    for (int i = 0; i < Q; i++) {
        int query = queries[i];
        auto result = findClosestSums(sums,query);

        if (result.second == -1) {
            cout << result.first << endl;
        } else {
            cout<< result.first << " " << result.second << endl;
        }

    }

    return 0;
} */


// AED012 Game Tournament

/* #include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> skill_levels(N);
    for (int i = 0;i < N; i++) {
        cin >> skill_levels[i];
    }

    sort(skill_levels.begin(), skill_levels.end());

    for (int i  = N - 1; i >= N - K; i--) {
        cout << skill_levels[i] << endl;
    }

    return 0;
}


 */

// AED013 Counting the Bits
/* #include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int countBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

bool customComparator(int x, int y) {
    int countX = countBits(x);
    int countY = countBits(y);

    if (countX != countY) {
        return countX > countY;
    }

    return x < y;
}


int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);

    for (int i = 0; i< n; i++) {
        cin >> numbers[i];
    }

    sort(numbers.begin(), numbers.end(), customComparator);

    for (int i = 0; i < n; i++) {
        cout << numbers[i] << endl;

    }
    return 0;

} */

// AED016 Footbal Table
/* #include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Team {
    string name;
    int wins;
    int draws;
    int losses;
    int goals_scored;
    int goals_against;
    int points;
    int goal_average;

    void calculate() {
        points = wins * 3 + draws;
        goal_average = goals_scored - goals_against;
    }
};

bool customComparator(const Team & a, const Team & b) {
    if (a.points != b.points) {
        return a.points > b.points;
    }
    if (a.goal_average != b.goal_average) {
        return a.goal_average > b.goal_average;
    }
    return a.name < b.name;
}

int main() {
    int N;
    cin >> N;

    vector<Team> teams(N);

    for (int i = 0; i < N; ++i) {
        cin >> teams[i].name >> teams[i].wins >> teams[i].draws >> teams[i].losses
            >> teams[i].goals_scored >> teams[i].goals_against;

            teams[i].calculate();
    }
    sort(teams.begin(), teams.end(), customComparator);

    for (const auto &team : teams) {
        cout << team.name << " " << team.points << " " << team.goal_average << endl;

    }

    return 0;
}
 */

// AED015 Anagrams
/* #include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

string sortPhrase(const string &s) {
    string result;
    for (char c : s) {
        if (!isspace(c)) {
            result += tolower(c);
        }
    }

    sort(result.begin(), result.end());

    return result;
}

int main() {

    int N;
    cin >> N;
    cin.ignore();

    unordered_map<string, int> anagramCount;

    for (int i = 0; i < N; ++i) {
        string phrase;
        getline(cin, phrase);
        string sortedPhrase = sortPhrase(phrase);

        anagramCount[sortedPhrase]++;
    }

    int anagramClasses = 0;

    for (const auto &entry : anagramCount) {
        if (entry.second > 1) {
            anagramClasses++;
        }
    }

    cout << anagramClasses << endl;

    return 0;
}
 */

// AED008 Backpacking Trip
/* #include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool isPossible (const vector<int>& distances, int x, int k) {
    int partition_count = 1;
    int current_sum = 0;

    for (int i = 0; i < distances.size(); i++) {
        if (distances[i] > x) {
            return false;
        }
        if (current_sum + distances[i] > x) {
            partition_count++;
            current_sum = distances[i];
        } else {
            current_sum += distances[i];
        }
        if (partition_count > k) {
            return false;
        }
    }

    return true;
}

int findMinimumMaxDistance(const vector<int>& distances, int k) {
    int low = *max_element(distances.begin(), distances.end());
    int high = accumulate(distances.begin(), distances.end(), 0);

    while (low < high) {
        int mid = low + (high - low) / 2;
        if (isPossible(distances, mid, k)) {
            high = mid;
        }
        else {
            low = mid + 1;
        }
    }

    return low;
}


int main() {
    int N;
    cin >> N;

    vector<int> distances(N);

    for (int i = 0; i < N; i++) {
        cin >> distances[i];
    }

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++) {
        int k;
        cin >> k;

        int result = findMinimumMaxDistance(distances, k);
        cout << result << endl;
    }

    return 0;
} */


// AED010 Word Game
/* #include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool canRemove(int k, const string& A, const string& B, const vector<int>& P) {
    int n = A.size(), m = B.size();
    vector<bool> removed(n, false);

    for (int i = 0; i < k; ++i) {
        removed[P[i] - 1]  = true;
    }

    int j = 0;
    for (int i = 0; i < n; ++i) {
        if (!removed[i] && A[i] == B[j]) {
            j++;
        }
        if (j == m) {
            return true;
        }
    }

    return false;
}

int main() {
    string A, B;
    cin >> A >> B;

    int n = A.size();
    vector<int> P(n);

    for (int i = 0; i <n ; ++i) {
        cin >> P[i];


    }

    int low = 0, high = n, answer = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canRemove(mid, A, B, P)) {
            answer = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << answer << endl;

    return 0;
}
 */

// AED017 Chocolate Boxes
/* 
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> chocolates(N);

    for (int i = 0; i < N; ++i) {
        cin >> chocolates[i];
    }

    sort(chocolates.begin(), chocolates.end());

    int minDifference = INT_MAX;

    for (int i = 0; i <= N - K; ++i) {
        int currentDifference = chocolates[i+K-1] - chocolates[i];
        minDifference = min(minDifference, currentDifference);
    }

    cout << minDifference << endl;

    return 0;
}
 */

// AED018 Ferris Wheel
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> weights(N);

    for (int i = 0; i < N; ++i) {
        cin >> weights[i];
    }

    sort(weights.begin(), weights.end());

    int cabins = 0;
    int l = 0;
    int h = N - 1;

    while(l <= h) {
        if (weights[l] + weights[h] <= K) {
            l++;
            h--;
        }
        else {
            h--;
        }
        cabins++;
    }

    cout << cabins << endl;

    return 0;
}

