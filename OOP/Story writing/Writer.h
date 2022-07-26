#pragma once

#include <string>

using namespace std;

class Writer {

private:
	string name;
	string expertise;

public:

	Writer(string name="", string expertise="") : name(name), expertise(expertise) {};
	~Writer() = default;

	friend istream& operator>>(istream& is, Writer& wr);

	string getName() { return this->name; };
	string getExpertise() { return this->expertise; };

};