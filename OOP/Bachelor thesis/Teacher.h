#pragma once

#include <string>

using namespace std;

class Teacher {

private:
	string name;

public:
	Teacher(string name = "") : name(name) {};
	string getName() { return this->name; };

	friend istream& operator>>(istream& is, Teacher& th);

};