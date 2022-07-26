#pragma once

#include <string>

using namespace std;

class User {

private:
	string name;

public:

	User(string name="") : name(name) {};

	string getName() { return this->name; }

	friend istream& operator>>(istream& is, User& us);

};