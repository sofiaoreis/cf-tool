#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include "user.h"

using namespace std;

class parser {
	string usersDirectory;
	string itemsDirectory;
	string dataDirectory;
	string genreDirectory;

public:
	//constructor of the parser object
	parser();

	//function to load users from the file and to treat the information
	//returns a bidimensional vector with all the users, and each user with the necessary properties
	vector<vector<string> > loadUsers();

	//function to load genres from the file and to treat the information
	//returns a bidimensional vector with all the genres, and each genre with the necessary properties
	vector<vector<string> > loadGenres();

	//function to load movies from the file and to treat the information
	//returns a bidimensional vector with all the movies, and each movie with the necessary properties
	vector<vector<string> > loadMovies();

	//function to load ratings from the file and to treat the information
	//returns a bidimensional vector with all the ratings, and each rating with the necessary properties
	vector<vector<string> > loadRatings();

	//Function to get user information
	vector<string> getUserInfo(string str);

	//Function to get movie information
	vector<string> getMovieInfo(string str);

	//Function to get rating information
	vector<string> getRatingInfo(string str);

	//the u.genre, u.info and u.item have the properties separated by a |, so this is the function to separate every line of the document in smaller strings
	vector<string> splitLine(const string &s, char character);
};

#endif /* PARSER_H_ */
