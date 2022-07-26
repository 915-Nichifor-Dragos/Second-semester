#pragma once

#include <string>

using namespace std;

class Star {

private:
	string name;
	string constelation;
	int RA;
	int Dec;
	int diameter;

public:

	Star(string name = "", string constelation = "", int RA = 0, int Dec = 0, int diameter = 0) : name(name), constelation(constelation), RA(RA), Dec(Dec), diameter(diameter) {};

	string getName() { return this->name; }
	string getConstelation() { return this->constelation; }
	int getRA() { return this->RA; }
	int getDec() { return this->Dec; }
	int getDiameter() { return this->diameter; }

	void setName(string name) { this->name = name; }
	void setRA(int RA) { this->RA = RA; }
	void setDec(int Dec) { this->Dec = Dec; }
	void setDiameter(int diameter) { this->diameter = diameter; }

	friend istream& operator>>(istream& is, Star& st);
	friend ostream& operator<<(ostream& os, Star& st);
};