#include <iostream>
#include <list>
#include <sstream>
#include <string>

int main() {
    // Step 1: Read the sentence and calculate K
    std::string sentence;
    std::getline(std::cin, sentence);
    std::istringstream sentence_stream(sentence);
    int K = 0;
    std::string word;
    while (sentence_stream >> word) {
        K++; // Counting words to determine the K value
    }

    // Step 2: Read the number of children and their names
    int N;
    std::cin >> N;
    std::cin.ignore(); // Ignore remaining newline from previous input
    std::list<std::string> children;
    for (int i = 0; i < N; ++i) {
        std::string child_name;
        std::getline(std::cin, child_name);
        children.push_back(child_name);
    }

    // Step 3: Simulate the elimination game
    auto it = children.begin(); // Iterator pointing to the current child
    while (children.size() > 1) {
        // Move K-1 steps forward (with wrap-around)
        for (int count = 1; count < K; ++count) {
            ++it;
            if (it == children.end()) {
                it = children.begin(); // Wrap around
            }
        }
        
        // Output the name of the child being removed
        std::cout << *it << std::endl;

        // Erase the K-th child and adjust iterator to the next child
        it = children.erase(it);
        if (it == children.end()) {
            it = children.begin(); // Wrap around if we reach the end
        }
    }

    // Output the last remaining child
    std::cout << *children.begin() << std::endl;
    
    return 0;
}
