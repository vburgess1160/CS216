/*
 * Course: CS216-004
 * Project: Project 2 main.cpp
 * Purpose: it reads data from an input file which passes as command line argument
 *          then stores in an object of IMDB class (to represent imdb database)
 *          it then allowes user to choose
 *          option1: user enters two movies then choose between three options:
 *          	A) print all actors C) print common actors O) print uncommon actors
 *          option2: search for all co-actors of an user-entered actor
 * Author: Victoria Burgess
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <map>
#include <sstream>
#include "imdb.h"

using namespace std;

void analyzeMovies(const IMDB& imdb); //defined after main
void analyzeCoActors(const IMDB& imdb); //defined after main

int main(int argc, char* argv[])
{
    // Check whether the number of command line arguments is exactly one 
    if (argc != 2)
    {
        cout << "Warning: need exactly one command line argument." << endl;
        cout << "Usage: " << argv[0] << " inputfile_name" << endl;
        return 1;
    }
    
    // Open input file
    ifstream in_file;
    in_file.open(argv[1]);

    // Check whether the input file can be opened successfully or not
    if (!in_file.good())
    {
        cout << "Warning: cannot open file named " << argv[1] << "!" << endl;
        return 2;
    }

    // Read data from the input file (movie_actors.txt)
    // each line of the input file: actorName; movie1, movie2, ...
    // create a pair <actorName,  set of movieTitles actor was in>
    // insert to IMDB object
    IMDB cs216_imdb;

    while (!in_file.eof())
    {
        string line;
        getline(in_file, line);
        string actorName, movieTitle;
        // check if the text line is not empty
        if (line.length() != 0)
        {
            istringstream iss(line);
            getline(iss, movieTitle,';'); //extracts string until ; called movieTitle

            // Extract extra white space
            iss>>ws;

            // Create a new set of actors  associated with movieTitle
            set<string> actors;

            while (getline(iss, actorName, ',')) //extracts string until , called actorName
            {
                actors.insert(actorName);
                // extract white space 
                iss>>ws;
            }
            // insert the pair to IMDB object: cs216_imdb
            cs216_imdb.insert_a_movie(movieTitle, actors);
        }
    }

    // close the input file
    in_file.close();

/* --------------- CHOOSE OPTION --------------------------------------------------------------------------------------*/
 
    int option;
    while (true)
    {
        cout << endl <<  "This application stores information about Actors and their Movies, please choose your option (Enter Q or q to quit):" << endl;
        cout << "1. Actors in Movies" << endl;
        cout << "2. Actors and co-actors" << endl;
        cin >> option;
        cin.ignore(256, '\n');

	// if cin a string instead of int
        if (cin.fail())
        {
            string input_to_check;
            cin.clear();
            getline(cin, input_to_check);

            if (input_to_check == "Q" || input_to_check == "q") //quit program
                break;
            else
            {
                cout << "Invalid option!" << endl;
                continue;
            }
        }
	
	// if cin is an int
        switch (option)
        {
            case 1: analyzeMovies(cs216_imdb); //OPTION 1
                    break;
            case 2: analyzeCoActors(cs216_imdb); //OPTION 2
                    break;
            default:
                    cout << "Invalid option!" << endl;
        }
    }
    cout << "Thank you for using my program, bye..." << endl;
    return 0;
}

/* ---------------------- OPTION 1 ---------------------------------------------------------------*/
// this function asks the user to input two movie titles
// then finds the matched two movies from the map
// and displays all the actors in either of the two movies
// if no matched movie then display "Invalid movie title" and do nothing
// note that using const call by reference is for efficiency purpose:
//           no copy of IMDB object is made and the argument has been protected
void analyzeMovies(const IMDB& imdb)
{
    // Ask the user to input two movie titles to search for
    string movie1, movie2;
    cout << "Please input the first movie title: ";
    getline(cin,movie1);
    cout << "Please input the second movie title: ";
    getline(cin,movie2);

    // Check if both movie1 and movie1 can be matched with movies in the map
    // If either one is not, quit the program
    // Otherwise display options for A) print all C) print common or O) print uncommon
    string matchedMovie1, matchedMovie2;
    matchedMovie1 = imdb.matchExistingMovie(movie1);
    matchedMovie2 = imdb.matchExistingMovie(movie2);
	
    //if movies match then display a,c,o menu
    if ((matchedMovie1.length() > 0) && (matchedMovie2.length() > 0))
    {
        cout << "Your input matches the following two movies: " <<endl;
        cout << matchedMovie1 << endl;
        cout << matchedMovie2 << endl;
        cout << "Both movies are in the database, please continue..." << endl <<  endl;	
	cout << "Please input your menu option (enter Q or q to quit)" << endl;
	cout << "A -- to print all actors" << endl;
	cout << "C -- to print common actors in both movies" << endl;
	cout << "O -- to print actors in only one of the movies" << endl;
	
	//read in a,c,o option and create sets of actors
	string optionStr;
	getline(cin, optionStr);
	set<string> actors_in_movie1 = imdb.find_actors_in_a_movie(matchedMovie1);
	set<string> actors_in_movie2 = imdb.find_actors_in_a_movie(matchedMovie2);

	while (optionStr != "Q" && optionStr != "q") {

		if (optionStr == "A" || optionStr == "a") {
			set<string> all;   // to store the all of actors_in_movie1 and actors_in_movie2
        		all = actors_in_movie1; //stores every actor in movie1 into all	
			for (auto i = actors_in_movie2.begin(); i != actors_in_movie2.end(); i++) //inserts actors from movie2 into all
				all.insert(*i);		
			// Display all the actors in either one movie
        		cout << "All of the actors in both movies:" << endl;
			for (auto i = all.begin(); i != all.end(); i++)
				cout << *i << endl;
		}

		else if (optionStr == "C" || optionStr == "c") {
			set<string> common; //stores common actors
			for (auto i = actors_in_movie1.begin(); i != actors_in_movie1.end(); i++) //matches actors from set1 to set2
				if (actors_in_movie2.count(*i) != 0)
					common.insert(*i);
			cout << "Common actors in both sets:" << endl;
			for (auto i = common.begin(); i != common.end(); i++)
				cout << *i << endl;
		}

		else if (optionStr == "O" || optionStr == "o") {
			set<string> different; //stores not common actors
			for (auto i = actors_in_movie1.begin(); i != actors_in_movie1.end(); i++) //checks matches from set1 to set2
				if (actors_in_movie2.count(*i) == 0)
					different.insert(*i);
			for (auto i = actors_in_movie2.begin(); i != actors_in_movie2.end(); i++) //checks matches from set2 to set1
				if (actors_in_movie1.count(*i) == 0)
					different.insert(*i);
			
			cout << "Actors in only one movie:" << endl;
			for (auto i = different.begin(); i != different.end(); i++)
				cout << *i << endl;			
		}

		else
			cout << "Invalid option!" << endl;
		
		cout << endl << "Please input your menu option (enter Q or q to quit)" << endl;
		cout << "A -- to print all actors in both movies" << endl;
		cout << "C -- to print common actors in both movies" << endl;
		cout << "O -- to print actors in one but not both movies" << endl;
		getline(cin, optionStr);

	} //end while
    }
    //movies don't match database
    else {
        cout << "Invalid movie title." << endl;
	return;
    }
}
/* --------------------------------------- OPTION 2 -------------------------------------------------------------------------------*/
// The function asks the user to type an actor's name
// then check if the user-input name is valid(it is valid if it is in the database stored in the passing in object
// if it is valid, display in each movie which this actor is in, the co-actors who appeared in the same movie
void analyzeCoActors(const IMDB& imdb)
{
    string actor_name;
    cout << "Finding the co-actors of the actor by typing his/her name: ";
    getline(cin, actor_name);
    if (!imdb.isExistingActor(actor_name))
    {
        cout << "The actor name you entered is not in the database." << endl;
        return;
    }   

    set<string> movies_of_actor = imdb.find_movies_for_an_actor(actor_name);
    set<string> actors_in_a_movie;

    for (auto i = movies_of_actor.begin(); i != movies_of_actor.end(); i++)
    {
        cout << "The co-actors of " << actor_name << " in the movie \"" << *i << "\" are: " << endl;
        // Display all the co-actors in one movie
        actors_in_a_movie = imdb.find_actors_in_a_movie(*i);
        for (auto j = actors_in_a_movie.begin(); j != actors_in_a_movie.end(); j++)
        {
		if (*j != actor_name)
                	cout << *j << endl;
        }    
        cout << "***********************************" << endl;
    }
} 
