/*
 * File: imdb.cpp
 * Course: CS216-00x
 * Project: Lab8 (as part of Project 2)
 * Purpose: Provide the implementation of the class named IMDB
 *          This class represents a movie-actor database
 */
#include <regex>  // needs c++11 standard
#include "imdb.h"

using namespace std;

// default constructor
IMDB::IMDB()
{
    //do nothing
    //since map class contains a default contructor
    //      which constructs an empty container, with no elements
}

// insert a pair<actorName, the set of movieTitle of this actor>
void IMDB::insert_an_actor(string actorName, set<string> movieTitles)
{
    	/* First update actors_db */   
	auto i = actors_db.find(actorName);
	if (i == actors_db.end())
		actors_db[actorName] = movieTitles; //not found, create new actor and add their movies
	else 
		for (auto j = movieTitles.begin(); j != movieTitles.end(); j++)
			i->second.insert(*j); //found, insert movieTitles to actor's set of movies
	
	/* Second update movies_db */	
	for (auto i = movieTitles.begin(); i != movieTitles.end(); i++)
       	{
		auto x = movies_db.find(*i);
		if (x == movies_db.end())  //movie not found, create new movie and add newActor as its set
	       	{		
			set<string> newActor;
			newActor.insert(actorName);
			movies_db[*i] = newActor;
		}
		else //movie found, insert actor name to movie's set
			x->second.insert(actorName);
	}

	
}

// insert a pair <movieTitle, the set of actor names in this movie>
void IMDB::insert_a_movie(string movieTitle, set<string> actorNames)       
{
       	/* First upgrade movies_db */
	auto i = movies_db.find(movieTitle);
	if (i == movies_db.end())
		movies_db[movieTitle] = actorNames; //not found, create new movie and add set of actors
	else 
		for (auto j = actorNames.begin(); j != actorNames.end(); j++)
			i->second.insert(*j); //found, insert actorNames to movie's set of actors
	
	 /* Second upgrade actors_db */
	for (auto i = actorNames.begin(); i != actorNames.end(); i++) 
	{
		auto x = actors_db.find(*i);
		if (x == actors_db.end()) { //actor not found, create new actor and add newMovie as set
			set<string> newMovie;
			newMovie.insert(movieTitle);
			actors_db[*i] = newMovie;
		}
		else //actor found, insert movieTitle to actor's set
			x->second.insert(movieTitle);
	}

}

// use passing-in parameter, movieTitle, as the pattern to match 
// one existing movie in the map
// return the matched movie title from the map
// otherwise return empty string
string IMDB::matchExistingMovie(string movieTitle) const
{
    string matchedMovie;
    bool found = false;
    // generate the regular expression to match 
    // which contains movieTitle as a substring
    // note that it performs case insensitive matching
    regex reg(movieTitle, regex_constants::icase);
    auto it = movies_db.begin();
    while (!found && it != movies_db.end())
    {
        if (regex_search(it->first, reg))
        {
            found = true;
            matchedMovie = it->first;
        }
        else
            it++;
    }
    return matchedMovie;
}

// check if a movieTitle does exist in the map
// return true if it does; otherwise return false
bool IMDB::isExistingMovie(string movieTitle) const
{
	if (movies_db.find(movieTitle) != movies_db.end())
		return true;
	return false;
}

// check if an actorName does exist in the map
// return true if it does; otherwise return false
bool IMDB::isExistingActor(string actorName) const
{
	if (actors_db.find(actorName) != actors_db.end())
		return true;
	return false;
}

// return a set of movie titles which actorName was in
// if the passing-in parameter: actorName, is not in the map, 
//                   display message andreturn an empty set
set<string> IMDB::find_movies_for_an_actor(string actorName) const
{
	if (isExistingActor(actorName))
		return actors_db.at(actorName);
	else {
		set<string> empty;
		return empty;
	}
}

// return a set of actor names which were all in the movieTitle
// if the passing-in parameter: movieTitle is not in the map, 
//                   display message and return an empty set
set<string> IMDB::find_actors_in_a_movie(string movieTitle) const
{
	if (isExistingMovie(movieTitle))
		return movies_db.at(movieTitle);
	else {
		set<string> empty;
		return empty;
	}
}
