/*
 * Name: Victoria Burgess
 * File: WordLadder.cpp
 * Project: Project 3
 * Purpose: Define WordLadder class
 */

#include "WordLadder.h"


WordLadder::WordLadder() {
}

WordLadder::WordLadder(const vector<string>& words) {
	//for each word in vector words
	for (int i = 0; i < words.size(); i++) 
		insertWord(words[i]);
}

void WordLadder::insertWord(string newWord) {
	//stores length of newWord
	int length = newWord.length();
	//if length not in map, then create new mapping
	//else add newWord to corresponding map point
	if (wordsByLength.find(length) == wordsByLength.end()) {
		vector<string> newVector;
		newVector.push_back(newWord);
		wordsByLength[length] = newVector;
	}
	else
		wordsByLength.find(length)->second.push_back(newWord);
}

// return a graph from the group of words with the same lengths = length
// there is an edge between two words if two words are only different in a single letter
Graph<string> WordLadder::WordsGraph(int length) const {
	Graph<string> wordsGraph; //graph to be returned
	map<string, vector<string>> buckets; //map of buckets of similar words
	vector<string> words = wordsByLength.at(length); //vector of words of same length
	
	//first loop: every word
	for (int i = 0; i < words.size(); i++) {
		//second: every letter (replace each letter with ?) then insert into a map of buckets
		for (int j = 0; j < words[i].length(); j++) {
			string replaced = words[i];
			replaced.at(j) = '?';

			if (buckets.find(replaced) == buckets.end()) {
				vector<string> newVect;
				newVect.push_back(words[i]);
				buckets[replaced] = newVect;
			}
			else
				buckets.find(replaced)->second.push_back(words[i]);
		}
	}

	//add edges between all words in a bucket
	//first: every element in map
	for (auto i = buckets.begin(); i != buckets.end(); i++) {
		//second: every word in bucket except last
		vector<string> bucketWords = i->second;
		for (int j = 0; j < bucketWords.size(); j++)
			//third: every other word in bucket except last
			for (int k = j+1; k < bucketWords.size(); k++) {
				if (bucketWords[j] != bucketWords[k])
					wordsGraph.addEdge(bucketWords[j], bucketWords[k]);
			}
	}

	return wordsGraph;
}

// return a vector of words
// which represents a word ladder from word1 to word2
// any two adjacent words along the ladder differ in only one character	
vector<string> WordLadder::getLadder(string word1, string word2) const {
	vector<string> ladder;

	if (word1.length() != word2.length())
	{
		cout << "The two words must be the same length!" << endl;
		return ladder;
	}
	else if (word1 == word2)
	{
		cout << "The two words must be different!" << endl;
		return ladder;
	}
	else
       	{
		Graph<string> newGraph = WordsGraph(word1.length());
		map<string, int> distance;
		map<string, string> go_through;

		int dist = newGraph.BFS(word1, word2, distance, go_through);
		//check if words can connect
		if (dist == NOPATH || dist == INVALID_VERTEX)
			return ladder;
		else
		{
			string nextWord = word2;
			ladder.push_back(word2);
			while (go_through[nextWord] != word1)
			{
				ladder.push_back(go_through[nextWord]);
				nextWord = go_through[nextWord];
			}
			ladder.push_back(word1);
	
		}
	}


	return ladder;
}

