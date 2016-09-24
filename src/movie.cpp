#include "movie.h"
#include <string>
#include <vector>
#include "stdlib.h"

//constructor of a movie object
Movie::Movie(string id, string title, string relDate, string videoRelDate, string imdbURL, vector<string> genres){
	this->id =  strtol(id.c_str(),nullptr,10);
	this->title = title;
	this->relDate = relDate;
	this->videoRelDate = videoRelDate;
	this->imdbURL = imdbURL;
	this->genres = genres;
}



