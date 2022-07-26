#include "Repository.h"

#include <fstream>

void Repository::updateStudent(string id, string th)
{
	for (int i = 0; i < this->students.size(); i++)
	{
		if (this->students[i].getId() == id)
		{
			this->students[i].setCoordinator(th);
			return;
		}
	}
}

void Repository::updateEmailTitle(string id, string newEmail, string newTitle)
{
	for (int i = 0; i < this->students.size(); i++)
	{
		if (this->students[i].getId() == id)
		{
			this->students[i].setEmail(newEmail);
			this->students[i].setTitle(newTitle);
			return;
		}
	}
}

void Repository::read()
{
	fstream inT(this->filenameTeachers);

	if (!inT.is_open())
		return;

	Teacher th;
	while (inT >> th)
	{
		this->teachers.push_back(th);
	}

	inT.close();

	// ===========================================

	fstream inS(this->filenameStudents);

	if (!inS.is_open())
		return;

	Student st;
	while (inS >> st)
	{
		this->students.push_back(st);
	}

	inS.close();

}

void Repository::write()
{
	ofstream out(this->filenameStudents);

	if (!out.is_open())
		return;

	for (auto element : this->students)
	{
		out << element;
	}

	out.close();
}
