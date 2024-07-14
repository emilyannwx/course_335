// Emily Ann Willix.
// spell_check.cc: A simple spell checker.

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;

// You can add more functions here.
// makes corrections to words not in dictionary 
vector<pair<string, char>> CorrectMisspelledWords(const string& word, const HashTableDouble<string>& dictionary) {
  vector<pair<string, char>> corrections;

  // case a: Adding one character in any possible position (including space)
  for (size_t i = 0; i <= word.length(); ++i) {
    for (char c = 'a'; c <= 'z'; ++c) {
      string corrected_word = word.substr(0, i) + c + word.substr(i);
      if (dictionary.Contains(corrected_word)) {
        corrections.push_back({corrected_word, 'A'});
      }
    }
  }

  // case b: Removing one character from the word
  for (size_t i = 0; i < word.length(); ++i) {
    string corrected_word = word.substr(0, i) + word.substr(i + 1);
    if (dictionary.Contains(corrected_word)) {
      corrections.push_back({corrected_word, 'B'});
    }
  }

  // case c: Swapping adjacent characters in the word
  for (size_t i = 0; i < word.length() - 1; ++i) {
    string corrected_word = word;
    swap(corrected_word[i], corrected_word[i + 1]);
    if (dictionary.Contains(corrected_word)) {
      corrections.push_back({corrected_word,'C'});
    }
  }

  return corrections;
}


//Creates and fills double hashing hash table with all words from
//dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file) {
  HashTableDouble<string> dictionary_hash;
  ifstream in(dictionary_file);
  if (!in) {
    cerr << "Unable to open file " << dictionary_file << endl;
    return dictionary_hash;
  }

  string word;
  while (in >> word) {
    dictionary_hash.Insert(word);
  }
  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string>& dictionary, const string &document_file) {
  ifstream in(document_file);
  if (!in) {
    cerr << "Unable to open file " << document_file << endl;
    return;
  }

  string word;
  while (in >> word) {
    // remove punctuation and convert to lowercase
    word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    if (dictionary.Contains(word)) {
      cout << word << " is CORRECT." << endl;
    } else {
      cout << word << " is INCORRECT." << endl;
      vector<pair<string, char>> suggestions = CorrectMisspelledWords(word, dictionary);
      for (const auto& suggestion : suggestions) {
        cout << "** " << word << " -> " << suggestion.first<< " ** case " << suggestion.second << endl;
      }
   
    }
  }
}




// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char** argument_list) {
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
    SpellChecker(dictionary, document_filename);

    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }
  
  testSpellingWrapper(argc, argv);
  
  return 0;
}
