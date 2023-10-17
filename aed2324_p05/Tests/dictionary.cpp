#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"

using namespace std;

WordMean::WordMean(string w, string m): word(w), meaning(m) {}

string WordMean::getWord() const {
    return word;
}

string WordMean::getMeaning() const {
    return meaning;
}

void WordMean::setMeaning(string m) {
    meaning = m;
}

void WordMean::setWord(string w) {
    word = w;
}

set<WordMean> Dictionary::getWords() const {
	return words;
}

void Dictionary::addWord(WordMean wm)  {
    words.insert(wm);
}


//=============================================================================
// Exercise 1: Dictionary
//=============================================================================
//TODO
bool WordMean::operator< (const WordMean& wm2) const {
     return word<wm2.word;
}

//=============================================================================
// Subexercise 1.1: Create Dictionary
//=============================================================================
//TODO
void Dictionary::readFile(ifstream &f) {
    string w, m;
    while(!f.eof()) {
        getline(f,w);
        getline(f,m);
        WordMean p(w,m);
        words.insert(p);

    }
}


//=============================================================================
// Subexercise 1.2: Print Dictionary
//=============================================================================
//TODO
void Dictionary::print() const {
    for (const WordMean &wm : words) {
        cout << wm.getWord() << endl;
        cout << wm.getMeaning() << endl;
    }
}

//=============================================================================
// Subexercise 1.3: Consult Dictionary
//=============================================================================
//TODO
string Dictionary::consult(string w1, WordMean& previous, WordMean& next) const {
    previous = WordMean("", "");
    next = WordMean("", "");

    // Procura por w1 no dicionário
    set<WordMean>::const_iterator it = words.find(WordMean(w1, ""));
    if (it != words.end()) {
        // Palavra w1 encontrada, obtenha seu significado
        return it->getMeaning();
    } else {
        // A palavra w1 não foi encontrada, procure as palavras antes e depois
        it = words.lower_bound(WordMean(w1, ""));
        if (it != words.begin()) {
            --it;
            previous = *it;
        }
        it = words.upper_bound(WordMean(w1, ""));
        if (it != words.end()) {
            next = *it;
        }

        return "word not found";
    }
}


//=============================================================================
// Subexercise 1.4: Update Dictionary
//=============================================================================
//TODO
bool Dictionary::update(string w1, string m1) {
    WordMean wordToUpdate(w1, m1);

    // Tente encontrar a palavra no dicionário
    set<WordMean>::iterator it = words.find(wordToUpdate);

    if (it != words.end()) {
        // A palavra já existe, remova-a
        words.erase(it);

        // Adicione a nova palavra com o significado atualizado
        words.insert(wordToUpdate);

        return true;
    } else {
        // A palavra não existe, adicione-a ao dicionário
        words.insert(wordToUpdate);
        return false;
    }
}
