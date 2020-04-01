/* 
 * File:   Gradebook.h
 * Course: CS216
 * Project: Lab 5 (as second part of Project 1)
 * Purpose: provide the declaration of the class named Gradebook
 *         
 *
 */

#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include <vector>
#include "FinalGrade.h"

using namespace std;

class Gradebook
{
    public:
        // default constructor
        Gradebook();   

        // return the size of the  current vector: scores,
        // which represents current gradebook
        int getSize() const;

        // insert a FinalGrade object, newFG, 
        // into the end of the current gradebook
        void insert(FinalGrade newFG);

        // return a FinalGrade object, 
        // which holds the maximum score in the current gradebook
        FinalGrade getMax() const;

        // return a FinalGrade object, 
        // which holds the minimum score in the current gradebook
        FinalGrade getMin() const;

        // return the average score among all scores in the current gradebook
        double getAverage() const;

        // For each FinalGrade object in the current gradebook, 
        // its score will be increased by the given value 
        // If the score reaches MAX_SCORE, it does not go beyond
        void incrementScore(double value);

        // print the FinalGrade objects in the current gradebook
        void print() const;

        // other member functions if you need...

    private:
        vector<FinalGrade> scores;
};

#endif /* GRADEBOOK_H */

