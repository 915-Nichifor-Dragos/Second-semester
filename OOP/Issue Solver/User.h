#pragma once

#include <string>

using namespace std;

class User {

private:
	string name;
	string type; // programmer or tester

public:

	User(string name = "", string type = "") : name(name), type(type) {};
	~User() = default;

	friend istream& operator>>(istream& is, User& u);

	string getName() { return this->name; };
	string getType() { return this->type; };

};