#ifndef MOVIE_H_
#define MOVIE_H_

#include <string>
#include <vector>

using namespace std;

class Movie {
	unsigned int id;
	string title;
	string relDate;
	string videoRelDate;
	string imdbURL;
	vector<string> genres;
public:
	//constructor of a movie object
	Movie(string id, string title, string relDate, string videoRelDate, string imdbURL, vector<string> genres);

	//method get movie id
	int getMovieId()
	{
		return id;
	}

	string getTitle()
		{
			return title;
		}
};

#endif /* MOVIE_H_ */
