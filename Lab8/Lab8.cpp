/*
 * Course: CS216-004
 * Project: Lab8 (as part of Project 1)
 * Purpose: it reads data from an input file which passes as command line argument
 *          then stores in an object of IMDB class (to represent imdb database in two map objects)
 *          The input file format:
 *          actorName, movie1, movie2, ..., movieN
 *          it then allowes user to search for all actors in either one of two movies
 *          two movies are from the user-input, then performs case insensitive matching
 *          and match the movie titles from the database
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

void analyzeMovies(const IMDB& imdb);

int main(int argc, char* argv[])
{
    // Check whether the number of command line arguments is exactly one 
    if (argc != 2)
    {
        cout << "Warning: need exactly one command line argument." << endl;
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

    // Read data from the input file, assume "good data" from the input file
    // each line of the input file: actorName, movie1, movie2, ..., movieN
    // read one line at a time then tokenize it:
    // create a pair <actorName, the set of movieTitles which the actor was in>
    //        and insert to IMDB object
    IMDB cs216_imdb;

    while (!in_file.eof())
    {
        string line;
        getline(in_file, line);
        string actorName, movieTitle;
        // check if the text line is not empty then tokenize it
        if (line.length() != 0)
        {
            istringstream iss(line);
            getline(iss, actorName,':');

            // Extract extra white space
            iss>>ws;

            // Create a new set of actors associated with movieTitle
            set<string> movies;

            while (getline(iss, movieTitle, ';'))
            {
                movies.insert(movieTitle);
                // extract white space 
                iss>>ws;
            }
            // insert the pair to IMDB object: cs216_imdb
            cs216_imdb.insert_an_actor(actorName, movies);
        }
    }
    // close the input file
    in_file.close();

    int option;
    while (true)
    {
        cout << endl <<  "This application stores information about Actors and their Movies, please choose your option (Enter Q or q to quit):" << endl;
        cout << "1. Actors in Movies" << endl;
        cout << "2. Actors and co-actors" << endl;
        cin >> option;
        cin.ignore(256, '\n');

        if (cin.fail())
        {
            string input_to_check;
            cin.clear();
            cin >> input_to_check;
            if (input_to_check == "Q" || input_to_check == "q")
                break;
            else
            {
                cout << "Invalid option!" << endl;
                continue;
            }
        }

        switch (option)
        {
            case 1: analyzeMovies(cs216_imdb);
                    break;
            case 2: // leave it do nothing for Lab8
                    // but you need to finish this block for project2
                    break;
            default:
                    cout << "Invalid option!" << endl;
        }
    }
    cout << "Thank you for using my program, bye..." << endl;
    return 0;
}


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
    // Check if both movie1 and movies can be matched with movies in the map
    // If either one is not, quit the program
    // Otherwise display all the actors in either of two movies
    //                   which are actually the union of two sets
    string matchedMovie1, matchedMovie2;
    matchedMovie1 = imdb.matchExistingMovie(movie1);
    matchedMovie2 = imdb.matchExistingMovie(movie2);
    if ((matchedMovie1.length() > 0) && (matchedMovie2.length() > 0))
    {
        cout << "Your input matches the following two movies: " <<endl;
        cout << matchedMovie1 << endl;
        cout << matchedMovie2 << endl;
        cout << "Both movies are in the database, searching actors..." << endl <<  endl;

        set<string> all;   // to store the union of actors_in_movie1 and actors_in_movie2
        all = imdb.find_actors_in_a_movie(matchedMovie1);
        set<string> actors_in_movie2 = imdb.find_actors_in_a_movie(matchedMovie2);
        for (auto i = actors_in_movie2.begin(); i != actors_in_movie2.end(); i++)
            all.insert(*i);
        // Display all the actors in either one movie
        cout << "All the actors in either of the two movies:" << endl;
        for (auto i = all.begin(); i != all.end(); i++)
            cout << *i << endl;
    }
    else
    {
        cout << "Invalid movie title." << endl;
        return;
    }
}

