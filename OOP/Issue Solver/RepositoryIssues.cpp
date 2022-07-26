#include "RepositoryIssues.h"

#include <fstream>

void RepositoryIssues::read()
{
	ifstream in(this->filename);
	if (!in.is_open())
		return;

	Issue issue;
	while (in >> issue)
	{
		this->issues.push_back(issue);
	}

	in.close();
}

void RepositoryIssues::write()
{
	ofstream out(this->filename);

	for (auto element : this->issues)
		out << element << "\n";
}
