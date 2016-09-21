#include "parser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;


parser::parser() {
	this->usersDirectory = "data/u.user";
	this->itemsDirectory = "data/u.item";
	this->dataDirectory = "data/u.data";
}

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

vector<string> parser::splitLine(const string &s, char character) {

	stringstream ss(s);
    string item;
    vector<string> result;
    while (getline(ss, item, character)) {
    	result.push_back(item);
    }
    return result;
}

vector<string> parser::getUserInfo(string userStr)
{
	vector<string> nUserInfo;
	nUserInfo = splitLine(userStr, '|');

	return nUserInfo;
}

vector<user> parser::getUsers()
{
	return users;
}

void parser::setUsers(const vector<user>& users) {
		this->users = users;
}
