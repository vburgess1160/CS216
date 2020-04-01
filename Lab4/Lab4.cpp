/*
 *Course: CS216-00x
 *Project: Lab 4 (As the first part of Project1)
 *Purpose: to implement a Gradebook Report
 *         it allows the user to input students' scores
 *         until the user types "q" or "Q" to quit 
 *         then displays all the valid scores from user input
 *                       and the corresponding letter grades;
 *                       the average score, highest score and lowest score.
 *Author: Victoria Burgess
 */

#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include <string>
#include <vector>
#include "FinalGrade.h"

using namespace std;

double calculateGradebook(const vector<FinalGrade>& gradebook, double& max_score, double& min_score);


int main()
{
	vector<FinalGrade> CS216gradebook;
	double input_score;

	while (true)
	{
	    cout << "Please enter a score for CS216 (type 'Q' or 'q' to quit): " << endl;
		cin >> input_score;
		cin.ignore(256, '\n');

		// check if the user input is invalid
		if (cin.fail())
		{
			string check_input;
			cin.clear();
			cin >> check_input;
            cin.ignore(256, '\n');
			if (check_input == "Q" || check_input == "q")
				break;
			else {
				cout << "Invalid input, please try again..." << endl;
				continue;
			}
		}

		// check if the input score is in the correct range: [0,100]
		if (input_score < 0 || input_score > 100)
		{
			cout << "The score is not in the correct range, please try again..." << endl;
		}
		else  // valid user input, store into gradeList object
        {
            FinalGrade inputFG(input_score);
            CS216gradebook.push_back(inputFG);
        }
	}

    // Check if the gradebook is empty
    // If it is empty, report it then quit the program
    if  (CS216gradebook.size() == 0)
    {
        cout << "The gradebook for CS216 is empty!" << endl;
        return 1;
    }
    
    // if the gradebook is not empty
    // Display each score and corresponding letter grade in the grade    
    // Display the average score, the highest and lowest scores from the gradebook
    cout << endl << endl;
    cout << "The gradebook for CS216:" << endl;
    cout << fixed << setprecision(2);
    for (int i=0; i < CS216gradebook.size(); i++)
    {
        CS216gradebook[i].print();
    }

    double max_score = 0;
    double min_score = 0;
    double average = 0;
    average = calculateGradebook(CS216gradebook, max_score, min_score);
    cout << "The average score is: " << average << endl;
    cout << "The highest score is: " << max_score << endl;
    cout << "The lowest score is: " << min_score << endl;
	return 0;
}

// return the average score from the gradebook
// call by reference: max_score and min_score
// after function calling, max_score stores the highest score in the gradebook
//                         min_score stores the lowest score in the gradebook
double calculateGradebook(const vector<FinalGrade>& gradebook, double& max_score, double& min_score)
{
    // Please provide your implementation of this function
    double sum = 0;
    min_score = gradebook[0].getScore();

    for (int i = 0; i < gradebook.size(); i++) {
	if (gradebook[i].getScore() > max_score)
		max_score = gradebook[i].getScore();
	if (gradebook[i].getScore() < min_score)
		min_score = gradebook[i].getScore();
	sum += gradebook[i].getScore();
    }

    double average = sum / gradebook.size();
    return average;
}

