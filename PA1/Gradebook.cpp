 /* 
 * File:   Gradebook.cpp
 * Course: CS216
 * Project: Lab 5 (as second part of Project 1)
 * Purpose: provide the implementation of the member functions of Gradebook class
 *
 * Author: Victoria Burgess
 *
 */
#include <iostream>
#include "Gradebook.h"

// default constructor
Gradebook::Gradebook()
{
	
}

// return the size of the current vector: scores, 
// which represents current gradebook
int Gradebook::getSize() const
{
	return scores.size();
}
    
// insert a FinalGrade object, newFG, 
// into the end of the current gradebook
void Gradebook::insert(FinalGrade newFG)
{
	scores.push_back(newFG);
}

// return a FinalGrade object, 
// which holds the maximum score in the current gradebook
FinalGrade Gradebook::getMax() const
{
	int max = 0;
	for (int i = 0; i < getSize(); i++)
		if (scores[i].getScore() > scores[max].getScore())
			max = i;
	return scores[max];
}

// return a FinalGrade object,
// which holds the minimum score in the current gradebook
FinalGrade Gradebook::getMin() const
{
	int min = 0;
	for (int i = 0; i < getSize(); i++)
		if (scores[i].getScore() < scores[min].getScore())
			min = i;
	return scores[min];
}
    
// return the average score among all scores in the current gradebook
double Gradebook::getAverage() const
{
	double sum = 0;
	for (int i = 0; i < scores.size(); i++)
		sum += scores[i].getScore();
	return sum / scores.size();
}

// For each FinalGrade object in the current gradebook, 
// its score will be increased by the given value 
// If the score reaches MAX_SCORE, it does not go beyond
void Gradebook::incrementScore(double value)
{
	for (int i = 0; i < scores.size(); i++) {
		if (scores[i].getScore() + value < MAX_SCORE)
			scores[i].setScore(scores[i].getScore() + value);
		else
			scores[i].setScore(MAX_SCORE);
	}
}
    
// print the FinalGrade objects in the current gradebook
void Gradebook::print() const
{
	for (int i = 0; i < scores.size(); i++) {
		scores[i].print();
	}	
}


