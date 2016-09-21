/*
 * user.h
 *
 *  Created on: 20/09/2016
 *      Author: Fifaz
 */

#ifndef USER_H_
#define USER_H_

#include <string>

using namespace std;

class user {

	string id;
	string age;
	string gender;
	string occupation;
	string zipcode;

public:
	user(string id, string age, string gender, string occupation, string zipcode);
	string getID()
	{
		return this->id;
	}


};

#endif /* USER_H_ */
