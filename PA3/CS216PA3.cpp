/*
 * Name: Victoria Burgess
 * File: main
 * Project: Project 3
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include "Graph.h"
#include "WordLadder.h"

using namespace std;

const int ARGUMENTS = 2;   // define the required command line arguments

int main(int argc, char* argv[])
{
    // Check whether the number of command line arguments match the required one 
    if (argc != ARGUMENTS)
    {
        cout << "Warning: need exactly " << ARGUMENTS-1 << " command line argument(s)." << endl;
        cout << "Usage: " << argv[0] << " inputfile_name" << endl;
        return 1;
    }

    ifstream in_file;
    in_file.open(argv[1]);
    // Check whether the input file can be open successfully or not
    if (!in_file.good())
    {
        cout << "Warning: cannot open file named " << argv[1] << "!" << endl;
        return 2;
    }

    //read in data from .txt
    vector<string> words;
    while (!in_file.eof())
    {
        string line;
        getline(in_file, line);
	words.push_back(line);
    }
    // close the input file
    in_file.close();

//------------------------------------------------------------------------
    
    WordLadder cs216_wordLadder(words);
    string word1, word2;

    while (true)
    {
        cout << endl << endl;
        cout << "Welcome to CS216 Word Ladder!" << endl;
        cout << "Please give me two English words, and I will convert the first into the second by modifying one letter at a time." << endl;
       cout << "Please type the FIRST word (or hit Enter to quit): " << endl;
	    getline(cin, word1);
        if (word1 == "")
            break;    
        cout << "Please type the SECOND word (or hit Enter to quit): " << endl;
	    getline(cin, word2);
        if (word2 == "")
            break;

        // convert both word1 and word2 to all lower-case letters
        transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
        transform(word2.begin(), word2.end(), word2.begin(), ::tolower);

	//generate ladder
        vector<string> ladder = cs216_wordLadder.getLadder(word1, word2);

	// Display the ladder distance from word1 to word2
        // Display the shortest path on the word ladder from word1 to word2
        // the ladder distance is defined as the number of vertices(word) on the shortest path from one vertex to another
        // the ladder distance of the same vertex to itself is 1-word

	if (ladder.size() == 0)
		cout << "There is no ladder from [" << word1 << "] to [" << word2 << "]" <<  endl;
	else if ( ladder.size() > 1)
        {
            cout << "The ladder from " << word1 << " to " << word2 << " is " << ladder.size() << "-word long." << endl;
            cout << "A ladder from [" << word1 << "] to [" << word2 << "]:" << endl;
            cout << ladder[ladder.size()-1];
            for (int i=ladder.size()-2; i >= 0; i--)
            {
                cout << " ---> " << ladder[i];
            }
            cout << endl;
        }
    }

    cout << "Thank you for using this program, bye..." << endl;
    return 0;


}
