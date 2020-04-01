/*
 * Name: Victoria Burgess
 * File: Graph.h
 * Course: CS216-004
 * Project: Project 3
 * Purpose: Declaration of Graph class, which is a template class
 *          This class represents an undirected Graph (no weight on each edge)
 *          using adjacent map representation
 *          It contains one private data memeber: adjMap
 *          which represents the mapping from a Vertex, say u (key) to a set of vertices (value) which directly connect to u 
 *
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
 
using namespace std;
 
const int NOPATH = -1;
const int INVALID_VERTEX = -2;

template<class T>
class Graph
{
   public:
    // default constructor
    Graph();
    
    // to check if an edge exists between v and w
    bool hasEdge(T v, T w) const;  
    
    // to add an edge beween v and w to the graph
    void addEdge(T v, T w);

    // Apply BFS traversal to find the shortest path from the given source s to destination t
    // return the distnace from s to t
    // if there is no path from s to t, return -1
    // store the shortest path distance from the given source s  to vertex w in distance map<w, distance>
    // store which next vertex to go through on the shortest path to the given source s in go_through map<w, v>. 
    // Here a pair <w, v> in go_through map represents on the shortest path from w to the given source s, it needs to take the path: w-->v...-->s  
    int BFS(T s, T t, map<T, int>& distance, map<T, T>& go_through) const;
   
   private:    
    //represent the mapping from a Vertex, say u (key) to a set of vertices (value) which directly connect to u 
    map<T, set<T> > adjMap;  
};

#endif   /* GRAPH_H */
#include "Graph.cpp"
