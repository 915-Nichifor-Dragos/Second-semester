#include "RepositoryUsers.h"

#include <fstream>

void RepositoryUsers::read()
{
	ifstream in(this->filename);
	if (!in.is_open())
		return;

	User issue;
	while (in >> issue)
	{
		this->users.push_back(issue);
	}

	in.close();
}
