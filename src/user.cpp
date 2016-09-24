#include <string>
#include "user.h"
#include "stdlib.h"

using namespace std;

//constructor of the user object
User::User(string id, string age, string gender, string occupation, string zipcode) {
	this->id = strtol(id.c_str(),nullptr,10);
	this->age = age;
	this->gender = gender;
	this->occupation = occupation;
	this->zipcode = zipcode;
}


