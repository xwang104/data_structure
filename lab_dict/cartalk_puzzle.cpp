/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    /* Your code goes here! */

    ifstream wordsFile(word_list_fname);
    vector<string> words;
    string word;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            words.push_back(word);
        }
    }
    vector<StringTriple> res;
    for (string word : words)
        if (word.length() == 5) {
            string word1 = word.substr(0, 1) + word.substr(2);
            string word2 = word.substr(1);
            if (d.homophones(word, word1) && d.homophones(word, word2)) {
                res.push_back(make_tuple(word, word1, word2));
            }
        }
    return res;

}
