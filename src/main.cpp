//============================================================================
// Name        : main.cpp
// Author      : Sofia Reis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include "parser.h"
#include "user.h"

using namespace std;

void createUsers(vector<vector<string> > usersInfos)
{
		vector<user> allUsers;

		for(unsigned int i = 0; i < usersInfos.size(); i++)
		{
			user usr = user(usersInfos[i][0],
					usersInfos[i][1],
					usersInfos[i][2],
					usersInfos[i][3],
					usersInfos[i][4]);

			allUsers.push_back(usr);
		}

		cout << allUsers.size();
}

int main() {
	parser ps = parser();
	vector<vector<string> > usersInfos = ps.loadUsers();
	createUsers(usersInfos);





	return 0;
}


