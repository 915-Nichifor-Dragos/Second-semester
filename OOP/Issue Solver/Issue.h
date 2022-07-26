#pragma once

#include <string>

using namespace std;

class Issue {

private:

	string description;
	string status;
	string reporter;
	string solver;

public:

	Issue(string description = "", string status = "open", string reporter = "", string solver = "") : description(description), solver(solver), reporter(reporter), status(status) {};
	~Issue() = default;

	string getDescription() { return this->description; };
	string getStatus() { return this->status; };
	string getReporter() { return this->reporter; };
	string getSolver() { return this->solver; };

	void setStatus(string what) { this->status = what; };
	void setSolver(string name) { this->solver = name; };

	friend istream& operator>>(istream& is, Issue& issue);

	friend ostream& operator <<(ostream& os, Issue& issue);

};