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
	vector<user> users;

public:
	parser();
	vector<vector<string> > loadUsers();
	vector<string> getUserInfo(string userStr);
	vector<string> splitLine(const string &s, char character);
	vector<user> getUsers();
	void setUsers(const vector<user>& users);


};

#endif /* PARSER_H_ */
