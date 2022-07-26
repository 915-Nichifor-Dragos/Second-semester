#pragma once

#include <string>

using namespace std;

class Astronomer {

private:
	string name;
	string constelation;

public:

	Astronomer(string name = "", string constelation = "") : name(name), constelation(constelation) {};

	string getName() { return this->name; }
	string getConstelation() { return this->constelation; }

	friend istream& operator>>(istream& is, Astronomer& ast);

};