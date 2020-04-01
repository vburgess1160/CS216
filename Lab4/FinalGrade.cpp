/* 
 * File:   FinalGrade.cpp
 * Course: CS216
 * Project: Lab 4
 * Purpose: provide the implementation of the member functions of the class named FinalGrade
 *
 * Author: Victoria Burgess
 *
 */
#include <iostream>
#include "FinalGrade.h"

// default constructor
FinalGrade::FinalGrade()
{
    // give initial value to be 0
    score = 0;
}

// constructor: give the initial value to the private data member score 
// to pass-in parameter in_score
FinalGrade::FinalGrade(double in_score)
{
    if (in_score < MIN_SCORE || in_score > MAX_SCORE)
        score = 0;
    else
        score = in_score;
}

// set the private data member: score
// to pass-in parameter in_score
void FinalGrade::setScore(double in_score)
{
    if (in_score < MIN_SCORE || in_score > MAX_SCORE)
        score = 0;
    else
        score = in_score;
}

// return the value of the data member: score
double FinalGrade::getScore() const
{
    return score;
}

    // return the corresponding letter grade from score
    // based on the grading policy in CS216 syllabus
char FinalGrade::decideLetterGrade() const
{
    // your code starts here...
    char letter;

    if (score >= 90)
	    letter = 'A';
    else if (score >= 80)
	    letter = 'B';
    else if (score >= 70)
	    letter = 'C';
    else if (score >= 60)
	    letter = 'D';
    else
	    letter = 'E';

    return letter;

}

// print the score and letter grade in the format: (for example)
// Score: 88        Letter Grade: B
void FinalGrade::print() const
{
    cout << "Score: " << score << "\t\tLetter Grade: " << this->decideLetterGrade() << endl;
}

