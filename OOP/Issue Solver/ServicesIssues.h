#pragma once

#include "RepositoryIssues.h"

class ServicesIssues : public Observable {

private:

	RepositoryIssues repo;

public:

	ServicesIssues(RepositoryIssues repo) : repo(repo) {};
	~ServicesIssues() = default;

	void addElement(Issue i) { return this->repo.addElement(i); };
	void removeElement(int index) { return this->repo.removeElement(index); };
	void updateStatus(int index, string name) { return this->repo.updateStatus(index, name); };
	void write() { this->repo.write(); };

	vector<Issue> getList() { return this->repo.getList(); };

};
