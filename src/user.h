#ifndef USER_H_
#define USER_H_

#include <string>

using namespace std;

class User {

	unsigned int id;
	string age;
	string gender;
	string occupation;
	string zipcode;

public:
	//constructor of the user object
	User(string id, string age, string gender, string occupation, string zipcode);

	//method to get id from User
	int getID()
	{
		return this->id;
	}


};

#endif /* USER_H_ */
