#include <string>
#include "user.h"

using namespace std;

user::user(string id, string age, string gender, string occupation, string zipcode) {
	this->id = id;
	this->age = age;
	this->gender = gender;
	this->occupation = occupation;
	this->zipcode = zipcode;
}


