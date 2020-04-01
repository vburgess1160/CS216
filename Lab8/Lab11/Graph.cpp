/*
 * File: Graph.cpp
 * Course: CS216-00x
 * Project: Lab 11
 * Purpose: Implementation of Graph class         
 */

#include "Graph.h"
#include <queue>
#include <regex>

using namespace std;

Graph::Graph() {

	//do nothing

}

bool Graph::hasEdge(char v, char w) {
	//check if w is in set of v
	set<char> vset = adjMap[v];
	for (auto i = vset.begin(); i != vset.end(); i++)
		if (*i == w)
			return true;
	return false;
	
}

void Graph::addEdge(char v, char w) {
	//add w to v's set
	adjMap[v].insert(w);

	//add v to w's set
	adjMap[w].insert(v);
}

int Graph::BFS(char s, char t, map<char, int>& distance, map<char, char>& go_through) {
	// set distance to -1 for each vertex in map	
	for (auto i = adjMap.begin(); i != adjMap.end(); i++ ) { 
		distance[i->first] = NOPATH;
	}
	// create empty queue to store char
	queue <char> Q;
	
	// initialize distance, go_through, queue, and current to source char
	distance[s] = 0;
	go_through[s] = s;
	Q.push(s);
	char current = s;

	// while Q (set of char to check) is not empty and curren isnt destination char
	while (!Q.empty() && current != t) {
		current = Q.front();
		Q.pop();
	
		map<char, set<char>>::iterator x = adjMap.find(current); // pointer that points to current vertex in adjMap
		set <char> currSet = x->second; //set of adj vertices to current	
		
		// for each vertext adjacent to current
		for (auto i = currSet.begin(); i != currSet.end(); i++) {
			if (distance.find(*i)->second == -1) {
				distance[*i] = distance[current] + 1;
				go_through[*i] = current;
				Q.push(*i);
			}
		}	
	}

	return distance[t];
	
}

