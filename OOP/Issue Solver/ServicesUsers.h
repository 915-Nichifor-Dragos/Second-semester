#pragma once

#include "RepositoryUsers.h"

class ServicesUsers {

private:

	RepositoryUsers repo;

public:

	ServicesUsers(RepositoryUsers repo) : repo(repo) {};
	~ServicesUsers() = default;

	vector<User> getList() { return this->repo.getList(); };

};