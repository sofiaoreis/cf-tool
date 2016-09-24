#include "parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex>


using namespace std;

//constructor of the parser object
parser::parser() {
	this->usersDirectory = "data/u.user";
	this->itemsDirectory = "data/u.item";
	this->dataDirectory = "data/u1.base";
	this->genreDirectory = "data/u.genre";
}

//function to load genres from the file and to treat the information
//returns a bidimensional vector with all the genres, and each genre with the necessary properties
vector<vector<string> > parser::loadGenres()
{
	string str;
	ifstream file(this->genreDirectory);
	vector<vector<string> > genres;
	if(file.is_open()){

			while (getline(file, str)) {
				genres.push_back(splitLine(str, '|'));
			}
		}
	file.close();
	return genres;
}

//function to load movies from the file and to treat the information
//returns a bidimensional vector with all the movies, and each movie with the necessary properties
vector<vector<string> > parser::loadMovies()
{
	string str;
	ifstream file(this->itemsDirectory);
	vector<vector<string> > movies;
	if(file.is_open()){
			while (getline(file, str)) {
				movies.push_back(getMovieInfo(str));
			}
		}
	file.close();
	return movies;
}

//function to load users from the file and to treat the information
//returns a bidimensional vector with all the users, and each user with the necessary properties
vector<vector<string> > parser::loadUsers(){

	string str;
	ifstream file(this->usersDirectory);
	vector<vector<string> > allUsers;

	if(file.is_open()){

		while (getline(file, str)) {
			allUsers.push_back(getUserInfo(str));
		}
	}

	file.close();
	return allUsers;
}

//function to load ratings from the file and to treat the information
//returns a bidimensional vector with all the ratings, and each rating with the necessary properties
vector<vector<string> > parser::loadRatings(){

	string str;
	ifstream file(this->dataDirectory);
	vector<vector<string> > allRatings;

	if(file.is_open()){

		while (getline(file, str)) {
			allRatings.push_back(getRatingInfo(str));
		}
	}

	file.close();
	return allRatings;
}

//the u.genre, u.info and u.item have the properties separated by a |, so this is the function to separate every line of the document in smaller strings
vector<string> parser::splitLine(const string &s, char character) {

	stringstream ss(s);
    string item;
    vector<string> result;
    while (getline(ss, item, character)) {
    	result.push_back(item);
    }
    return result;
}

//Function to get movie information
vector<string> parser::getMovieInfo(string str)
{
	vector<string> nMovieInfo;
	nMovieInfo = splitLine(str, '|');
	vector<string> fMovieInfo;
	int genreN = 0;

	//adding movie id and title to the new vector
	fMovieInfo.push_back(nMovieInfo[0]);
	fMovieInfo.push_back(nMovieInfo[1]);

	for(unsigned int i = 0; i < nMovieInfo.size(); i++)
	{
		if(i == 1)
		{
			string date = nMovieInfo[2];
			//adding the year has a separate property
			fMovieInfo.push_back(nMovieInfo[i].substr(nMovieInfo[i].size()-5, 4));
			//adding the release date that is in the previous position
			fMovieInfo.push_back(date);
			//erasing the (year) from the title section
			fMovieInfo[i].erase (fMovieInfo[i].end()-6, fMovieInfo[i].end());
		}
		else if(i == 4)
		{
			//adding imdb url
			fMovieInfo.push_back(nMovieInfo[i]);
		}
		else if(i > 4 && nMovieInfo[i] == "1")
		{
			//when a genre is 1 the function adds do the final movie vector the number of the genre
			fMovieInfo.push_back(to_string(genreN));
		}
		else if(i > 4)
		{
			//to calculate the number of the genre
			genreN++;
		}
	}
	return fMovieInfo;
}

//Function to get user information
vector<string> parser::getUserInfo(string str)
{
	vector<string> nUserInfo;
	nUserInfo = splitLine(str, '|');
	return nUserInfo;
}

//Function to get rating information
vector<string> parser::getRatingInfo(string str)
{
	//the file from ratings is separated by spaces, the next code was to divide in smaller strings and ignore the spaces
	stringstream ss(str);
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> nRatingInfo(begin, end);
	ostringstream buf;
	copy(nRatingInfo.begin(), nRatingInfo.end(), ostream_iterator<string>(buf, "\n"));
	string content(buf.str());

	return nRatingInfo;
}
