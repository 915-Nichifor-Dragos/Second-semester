#pragma once

#include "Observable.h"
#include "User.h"

class RepositoryUsers : public Observable {

private:
	vector <User> users;
	string filename;

public:

	RepositoryUsers(string filename) : filename(filename) { this->read(); };
	~RepositoryUsers() = default;
	vector<User> getList() { return this->users; };
	void read();

};