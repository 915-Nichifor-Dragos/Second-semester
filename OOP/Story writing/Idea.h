#pragma once

#include <string>

using namespace std;

class Idea {

private:
	string description;
	string status;
	string creator;
	int act;

public:

	Idea(string description="", string status="", string creator="", int act=0) : description(description), status(status), creator(creator), act(act) {};
	~Idea() = default;

	friend istream& operator>>(istream& is, Idea& id);

	string getDescription() { return this->description; };
	string getStatus() { return this->status; };
	string getCreator() { return this->creator; };
	int getAct() { return this->act; };

	void setDescription(string description) { this->description = description; };
	void setStatus(string status) { this->status = status; };
	void setCreator(string creator) { this->creator = creator; };
	void setAct(int act) { this->act = act; };

};