#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;


unsigned int Game::numberOfWords(string phrase) {
  if ( phrase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = phrase.find(' ');
  while (pos != string::npos) {
    phrase = phrase.substr(pos+1);
    pos = phrase.find(' ');
    n++;
  }
  return n;
}

Game::Game() {
	this->kids.clear();
}

Game::Game(list<Kid>& l2) {
	this->kids = l2;
}

void Game::addKid(const Kid k1) {
 	kids.push_back(k1);
}

list<Kid> Game::getKids() const {
	return this->kids;
}

void Game::setKids(const list<Kid>& l1) {
    this->kids = l1;
}

//=============================================================================
// Exercise 6: Pim Pam Pum
//=============================================================================
// Subexercise 6.1: Loose Game
//=============================================================================
// TODO
Kid Game::loseGame(string phrase) {
    list<Kid>::iterator currentKid = kids.begin();
    list<Kid>::iterator nextKid;

    // Check if there are kids to play the game with
    if (kids.empty()) {
        cout << "No kids to play the game with." << endl;
        return Kid(); // Return an empty Kid object to indicate no winner/loser
    }

    unsigned int numWords = numberOfWords(phrase);
    unsigned int wordCount = 0;

    while (kids.size() > 1) {
        nextKid = currentKid;
        ++nextKid;

        // Wrap around to the beginning of the list if we reach the end
        if (nextKid == kids.end()) {
            nextKid = kids.begin();
        }

        // Increment the word count
        ++wordCount;

        // Check if the last word in the phrase is reached
        if (wordCount == numWords) {
            // The child pointed to gets out of the game
            currentKid = kids.erase(currentKid);

            // Reset the word count
            wordCount = 0;
        } else {
            ++currentKid;
        }

        // Wrap around to the beginning of the list if needed
        if (currentKid == kids.end()) {
            currentKid = kids.begin();
        }
    }

    // Return the remaining child who loses the game
    return *kids.begin();
}


//=============================================================================
// Subexercise 6.2: Rearrange
//=============================================================================
// TODO
list<Kid> Game::rearrange() {
    list<Kid> res;
    queue<Kid> girlsQueue; // Queue to store girls
    queue<Kid> boysQueue;  // Queue to store boys

    // Separate girls and boys into their respective queues
    for (const Kid& kid : kids) {
        if (kid.getSex() == 'F') {
            girlsQueue.push(kid);
        } else {
            boysQueue.push(kid);
        }
    }

    // Ensure there's at least one girl in the beginning
    if (!girlsQueue.empty()) {
        res.push_back(girlsQueue.front());
        girlsQueue.pop();
    } else if (!boysQueue.empty()) {
        res.push_back(boysQueue.front());
        boysQueue.pop();
    }

    // Rearrange children using the specified pattern
    while (!girlsQueue.empty() || !boysQueue.empty()) {
        int numGirls = girlsQueue.size();
        int numBoys = boysQueue.size();

        // Distribute boys among girls
        while (numBoys > 0 && numGirls > 0) {
            res.push_back(girlsQueue.front());
            girlsQueue.pop();
            res.push_back(boysQueue.front());
            boysQueue.pop();
            numGirls--;
            numBoys--;
        }

        // Distribute remaining girls
        while (numGirls > 0) {
            res.push_back(girlsQueue.front());
            girlsQueue.pop();
            numGirls--;
        }

        // Distribute remaining boys
        while (numBoys > 0) {
            res.push_back(boysQueue.front());
            boysQueue.pop();
            numBoys--;
        }
    }

    // Return the rearranged list
    return res;
}


//=============================================================================
// Subexercise 6.3: Shuffle
//=============================================================================
// TODO
list<Kid> Game::shuffle() const {
    list<Kid> newList;
    return newList;
}
