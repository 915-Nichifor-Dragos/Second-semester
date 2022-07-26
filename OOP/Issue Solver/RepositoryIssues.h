#pragma once

#include "Observable.h"
#include "Issue.h"

class RepositoryIssues : public Observable {

private:
	vector <Issue> issues;
	string filename;

public:

	RepositoryIssues(string filename) : filename(filename) { this->read(); };
	~RepositoryIssues() = default;

	// adds a new Issue in the repository, by appending a new object of type "Issue" in the vector "issues"
	void addElement(Issue i) { this->issues.push_back(i); };

	void removeElement(int index) { this->issues.erase(this->issues.begin() + index); };

	// sets the status of the element found at index 'index' to 'closed' and updates the solver's name to 'name'
	void updateStatus(int index, string name) { this->issues[index].setStatus("closed"); this->issues[index].setSolver(name); };

	vector<Issue> getList() { return this->issues; };
	void read();
	void write();

};