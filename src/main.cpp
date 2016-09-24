#include <iostream>
#include <iomanip>
#include "parser.h"
#include "user.h"
#include "movie.h"
#include <map>
#include <utility>
#include <iterator>
#include "stdlib.h"
#include <math.h>
#include <cmath>

using namespace std;

//Function to convert the numbers of the genres to the strings
string getGenreName(vector<vector<string> > genres, string id)
{
	//result = unknown (1st genre)
	string result = genres[0][0];
	for(int k = 0; k < genres.size(); k++)
	{
		//if the id from the genre is equal to id passed by the function
		if(genres[k][1] == id)
		{
			//save the new genre string
			result = genres[k][0];
			break;
		}
	}
	return result;
}

// Function to create user objects
vector<User> createUsers(vector<vector<string> > usersInfos)
								{
	vector<User> users;
	for(unsigned int i = 0; i < usersInfos.size(); i++)
	{
		//creation of user object
		User usr = User(usersInfos[i][0],
				usersInfos[i][1],
				usersInfos[i][2],
				usersInfos[i][3],
				usersInfos[i][4]);

		//add to users vector
		users.push_back(usr);
	}

	return users;
								}

// Function to create movie objects
vector<Movie> createMovies(vector<vector<string> > moviesInfo, vector<vector<string> > genres)
								{
	vector<Movie> movies;

	for(unsigned int i = 0; i < moviesInfo.size(); i++)
	{
		vector<string> movGenres;
		for(unsigned int j = 0; j < moviesInfo[i].size(); j++)
		{
			//Because of the way that I structured the parser (I saved the positions of the 1 from 0 to 18),
			//I only need to convert the numbers to real genres after the position 4 of the vector.
			//Before we have movie information like movie id(0)|movie title(1)|release date(2)|video release date(3)|imdbURL(4)|genres...
			if(j>4)
				movGenres.push_back(getGenreName(genres, moviesInfo[i][j]));
		}

		//creation of movie object
		Movie mov = Movie(moviesInfo[i][0],
				moviesInfo[i][1],
				moviesInfo[i][2],
				moviesInfo[i][3],
				moviesInfo[i][4],
				movGenres);

		//add to movies vector
		movies.push_back(mov);
	}
	return movies;
								}

//function that calculates mean
float calculateMean(vector<int> vec)
{
	int sum = 0, n=0;
	for(int i = 1; i < vec.size(); i++)
	{
		sum += vec[i];
		if(vec[i]>0)
			n++;
	}
	return sum/n;
}


//Algorithm that calculates distance with mdc
float ratingDistance(vector<int> userRatings, vector<vector<int> > knownUserRating, int i)
{
	vector<int> userMovies = knownUserRating[i];
	float yMean = calculateMean(userMovies);
	float xMean = calculateMean(userRatings);

	float numer = 0;
	float corr = 0;
	float sumX = 0, sumY = 0;

	for(int i = 1; i < userMovies.size(); i++)
		for(int j = 1; j < userRatings.size(); j++)
		{
			if(userMovies[i]>0 && userRatings[j]>0 && i==j)
			{
				numer += abs(userRatings[j]-userMovies[i]);
			}
		}
	return numer;
}

//Algorithm that calculates correlation
double ratingDistance2(vector<int> userRatings, vector<vector<int> > knownUserRating, int k)
{
	vector<int> userMovies = knownUserRating[k];
	double yMean = calculateMean(userMovies);
	double xMean = calculateMean(userRatings);

	double numer = 0;
	double corr = 0;
	double sumX = 0, sumY = 0;

	for(int i = 1; i < userMovies.size(); i++)
		for(int j = 1; j < userRatings.size(); j++)
		{
			if(userMovies[i]>0 && userRatings[j]>0 && i==j)
			{

				numer += abs((userMovies[i]-yMean)*(userRatings[j]-xMean));
				sumX += pow (userMovies[i]-yMean,2);
				sumY += pow (userRatings[j]-xMean,2);
			}
		}

	corr = numer/sqrt(sumX*sumY);
	return corr;
}





int main() {

	parser ps = parser();

	typedef int movieID;
	typedef pair<int,int> userRating;
	typedef pair<movieID, userRating> Value;
	//"matrix" of know user ratings per movie; movieId -> [userId, rating]
	typedef multimap<movieID, userRating> MoviesToUserRating;
	typedef MoviesToUserRating::iterator it;
	MoviesToUserRating table;

	//create objects
	vector<User> users = createUsers(ps.loadUsers());
	vector<Movie> movies = createMovies(ps.loadMovies(), ps.loadGenres());
	vector<vector<string> > ratingsInfo = ps.loadRatings();

	for(unsigned int i = 0; i < ratingsInfo.size(); i++)
	{
		table.insert(Value(strtol(ratingsInfo[i][0].c_str(),nullptr,10),userRating(strtol(ratingsInfo[i][1].c_str(),nullptr,10),
				strtol(ratingsInfo[i][2].c_str(),nullptr,10))));
	}

	//COLLABORATIVE FILTERING ALGORITHM
	cout << "**********************************************************" << endl;
	cout << "*           MDC BASIC COLLABORATIVE FILTERING            *" << endl;
	cout << "**********************************************************" << endl;
	cout << "  - Please insert an available userID: ";
	int userID;
	cin >> userID;

	//vector with ratings of user input
	vector<int> userRatings;

	userRatings.push_back(userID);
	for(int i = 0; i<movies.size(); i++)
	{
		userRatings.push_back(0);
	}

	for(it i = table.begin(); i!= table.end(); i++)
	{
		if(i->first == userID)
			userRatings[i->second.first] = i->second.second;
	}

	//creating of the matrix with know user ratings per movie
	vector<vector<int> > knownUserRating;

	for(unsigned int i = 0; i<users.size()+1; i++)
	{
		vector<int> info;

		for(unsigned int j = 0; j < movies.size()+1; j++)
		{

			if(i==0 && j==0)
			{
				info.push_back(-1);
			}
			else if(i==0 && j>0){

				info.push_back(movies[j-1].getMovieId());
			}
			else if(j==0)
			{
				info.push_back(users[i-1].getID());
			}
			else if(j>0)
			{
				info.push_back(0);
			}
		}
		if(i>0)
		{
			pair<std::multimap<movieID, userRating>::iterator,
			std::multimap<movieID, userRating>::iterator> r = table.equal_range(i);
			for (std::multimap<movieID, userRating>::iterator it = r.first;
					it != r.second; ++it) {
				info[it->second.first] = it->second.second;
			}

		}
		knownUserRating.push_back(info);
	}



	//calculated using mdc
	float bestDist = ratingDistance(userRatings, knownUserRating, 1);
	int bestIndex = 0;
	float dist = 0;

	//calculate using mdc
	for(int i = 1; i < users.size(); i++)
	{
		dist=ratingDistance(userRatings, knownUserRating, users[i].getID());
		if(dist<bestDist && userID != users[i].getID())
		{
			bestDist = dist;
			bestIndex = users[i].getID();
		}
	}


	//result of mdc (list of unseen movies and predictions)
	cout << "*****************************************************************" <<  endl;
	cout << "LIST OF UNSEEN MOVIES AND PREDICTION BASED ON THE LOWER DISTANCE:" <<  endl;
	cout << "*****************************************************************" <<  endl;
	for(int i = 1; i < knownUserRating[bestIndex].size(); i++)
	{
		if(knownUserRating[bestIndex][i] !=0 && userRatings[i] == 0)
			cout << movies[i].getTitle() << "  " << knownUserRating[bestIndex][i] << endl;
	}

	cout << endl << endl << endl;

	cout << "**********************************************************" << endl;
	cout << "* These are the user unseen movies. What movie would you *" << endl;
	cout << "* like to predict? (Insert a number)                     *" << endl;
	cout << "**********************************************************" << endl;


	vector <Movie> unseenMovies;
	for(int j = 1; j < userRatings.size(); j++)
	{
		if(userRatings[j] == 0)
		{
			cout << movies[j-1].getMovieId() << " " << movies[j-1].getTitle() << endl;
			unseenMovies.push_back(movies[j-1]);
		}
	}

	cout << "What number do you want to choose? ";
	int movieNum = 0;
	cin >> movieNum;


	//Second algorithm, using correlation to calculate prediction
	double bestDist2 = ratingDistance2(userRatings, knownUserRating, 1);
	int bestIndex2 = 0;
	float dist2 = 0;

	for(int i = 1; i < users.size(); i++)
	{
		dist2=ratingDistance2(userRatings, knownUserRating, users[i].getID());
		if(dist2<bestDist2 && userID != users[i].getID())
		{
			bestDist2 = dist2;
			bestIndex2 = users[i].getID();
		}
	}

	float sum = 0;
	float count = 0;

	//calculate prediction p=(sum of ratings of all people that rated the movie*correlation)/number of people who rated movie
	for(int i = 1; i<knownUserRating.size(); i++)
	{
		if(knownUserRating[i][movieNum] !=0)
		{
			sum += knownUserRating[i][movieNum];
			count++;
		}

	}

	cout << "PREDICTION FOR THE MOVIE YOU CHOSE: " << (sum*bestDist2)/count << endl;



	return 0;
}





