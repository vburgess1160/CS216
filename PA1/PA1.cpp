/*
 *Course: CS216-004
 *Project:  First part of Project1
 *Purpose: to implement a Gradebook Report
 *         it allows the user to input students' scores
 *         until the user types "q" or "Q" to quit 
 *         then displays all the valid scores from user input
 *         and the corresponding letter grades;
 *         the average score, highest score and lowest score.
 *Author: Victoria Burgess
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "FinalGrade.h"
#include "Gradebook.h"

using namespace std;

//------------------------------------------------PART 1 --------------------------------------------------------------------
double calculateGradebook(const vector<FinalGrade>& gradebook, double& max_score, double& min_score);

int main()
{
	vector<FinalGrade> CS216gradebook;
	double input_score;

	while (1==1) //runs until break
	{
	    cout << "Please enter a score for CS216 (type 'Q' or 'q' to quit): " << endl;
	    cin >> input_score;
	    cin.ignore(256, '\n'); //ignore until new line
	    
	    // check if invalid (string/char)
	    if (cin.fail())
	    {
			string check_input; //create string to hold what user typed
			cin.clear(); //ignore cin.fail()
			cin >> check_input; //cin failed input to check_input as string
			cin.ignore(256, '\n');

			if (check_input == "Q" || check_input == "q")
				break;
			else
		       	{
				cout << "Invalid input, please try again..." << endl;
				continue;
			}
	    }

		// check range: [0,100]
		if (input_score < 0 || input_score > 100)
		{
			cout << "The score is not in the correct range, please try again..." << endl;
		}
		else  // valid user input, store into gradebook vector
        	{
           	 FinalGrade input_grade(input_score);
           	 CS216gradebook.push_back(input_grade);
        	}
	}
	
	// check if the gradebook is empty
	 if  (CS216gradebook.size() == 0)
	 {
        	cout << "The gradebook for CS216 is empty!" << endl;
		cout << "Thank you for using the Grade Curve Calculator." << endl;
        	return 1;
   	 }

    //----------------------------------------------------------- PART 2 ------------------------------------------------------------

  
	// create Gradebook object and calculate average
	Gradebook CS216gradebook_orig;

	for (int i = 0; i < CS216gradebook.size(); i++)
       	{
		FinalGrade input_grade(CS216gradebook[i]);
		CS216gradebook_orig.insert(input_grade);

	}
	double average_orig = CS216gradebook_orig.getAverage();
	average_orig = (int)(average_orig * 100 + 0.5);
	average_orig = (double)(average_orig / 100);
	
	double average_exp;

	//repeat asking for expected average and calculating curve until entering q/Q
 	while (1==1)
 	{
		cout << fixed << setprecision(2);
		cout << endl << endl;
		cout << "The original average score is: " << average_orig  << endl;

 		double input_average;
 		cout << "Please enter your expected average score to curve (type 'Q' or 'q' to quit): " << endl;
 		cin >> input_average;

		// check if invalid (string/char)
		if (cin.fail())
		{
			string check_input; //create string to hold what user typed
			cin.clear(); //ignore cin.fail()
			cin >> check_input; //cin failed input to check_input as string
			cin.ignore(256, '\n');

			if (check_input == "Q" || check_input == "q")
			{
				cout << "Thank you for using Grade Curve Calculator." << endl;
				break;
			}
			else
		       	{
				cout << "Invalid input, please try again..." << endl;
				cout << "The original average scores is: " << average_orig << endl;
				continue;
			}

		}	

		// check range: greater than original, < 100
		if (input_average < average_orig || input_average > MAX_SCORE)
			cout << "The expected average is not in the correct range, please try again..." << endl;

		else if(input_average == average_orig)
			cout << "The scores are perfect, no need for grading curve!" << endl;

		else //valid input, perform curve
		{
			average_exp = input_average;

			//print Gradebook
			cout << "The original gradebook for CS216: " << endl;
			CS216gradebook_orig.print();			
	
			cout << "The number of scores is:\t" << CS216gradebook_orig.getSize() << endl;
        		cout << "The maximum score is:\t";
			CS216gradebook_orig.getMax().print();
        		cout << "The minimum score is:\t";
        		CS216gradebook_orig.getMin().print();
        		cout << "The original average score is :\t" << average_orig << endl;

			double diff = average_exp - average_orig;
			Gradebook CS216gradebook_curved = CS216gradebook_orig;
        		CS216gradebook_curved.incrementScore(diff);

			cout << endl << endl;
			cout << "The expected average score is: " << average_exp << endl; 
        		cout << "The curved gradebook for CS216: " << endl;
        		CS216gradebook_curved.print();
        		cout << "The number of scores is:\t" << CS216gradebook_curved.getSize() << endl;
        		cout << "The maximum score is:\t";
			CS216gradebook_curved.getMax().print();
        		cout << "The minimum score is:\t";
        		CS216gradebook_curved.getMin().print();
        		cout << "The actual average score is:\t" << CS216gradebook_curved.getAverage() << endl;
		}

	 }// end while loop


	return 1;	

}//end main


// return the average
// call by reference: max_score and min_score
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


