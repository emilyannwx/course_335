// Emily Ann Willix.
#include <fstream>
#include <iostream>
#include <string>

// Uncomment when you implemented linear probing & double hashing
#include "linear_probing.h"
#include "double_hashing.h"
#include "quadratic_probing.h"

using namespace std;


// You can add more functions here
vector<std::string> LoadWords(const std::string &filename) {
    vector<std::string> words;
    ifstream file(filename);
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    return words;
}

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
			      const string &words_filename,
			      const string &query_filename) {
    hash_table.MakeEmpty();
    //..Insert your own code
    //loads words from input
    vector<string> input_words = LoadWords(words_filename);
    vector<string> query_words = LoadWords(query_filename);

    int num_elements = 0;
    int collisions_count = 0;

    //insert
    for (const auto &word : input_words) {
        if (hash_table.Insert(word)) {
            num_elements++;
            collisions_count += hash_table.GetProbeCount(word) - 1 ; // first probe isnt a collision
        }
    }

    double load_factor = static_cast<double>(num_elements) / hash_table.GetTableSize();
    double average_collisions = static_cast<double>(collisions_count) / num_elements;

    // output part a
    cout << "Total number of elements (N): " << num_elements << std::endl;
    cout << "Size of the table (T): " << hash_table.GetTableSize() << std::endl;
    cout << "Load factor (N/T): " << load_factor << std::endl;
    cout << "Total number of collisions (C): " << collisions_count << std::endl;
    cout << "Average number of collisions (C/N): " << average_collisions << std::endl;

    for (const auto &word : query_words) {
        int probe_count = hash_table.GetProbeCount(word) ;
        if (hash_table.Contains(word)) {
            cout << word << " Found " << probe_count << endl;
        } else {
            cout << word << " Not_Found " << probe_count << endl;
        }
    }


 

}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list) {
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 90;
    if (argument_count == 5) {
	const string rvalue(argument_list[4]);
	R = stoi(rvalue);
    }

    if (param_flag == "linear") {
      // Uncomment below when you have implemented linear probing.
      HashTableLinear<string> linear_probing_table;
      TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
    } else if (param_flag == "quadratic") {
	HashTable<string> quadratic_probing_table;
	TestFunctionForHashTable(quadratic_probing_table, words_filename,
				 query_filename);
    } else if (param_flag == "double") {
	cout << "r_value: " << R << endl;
        // Uncomment below when you have implemented double hashing.
	HashTableDouble<string> double_probing_table(101,R);
	TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
    } else {
	cout << "Unknown tree type " << param_flag
	     << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv) {
    if (argc != 4 and argc != 5) {
	cout << "Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag>" << endl;
	cout << "or Usage: " << argv[0]
	     << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
	return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
