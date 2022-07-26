#pragma once

#include "Repository.h"
#include "Observable.h"

class Service : public Observalbe {

private:
	Repository repo;

public:
	Service(Repository repo) : repo(repo) {};

	vector<Student>& getStudents() { return this->repo.getStudents(); }
	vector<Teacher>& getTeachers() { return this->repo.getTeachers(); }

	void updateStudent(string id, string th) { this->repo.updateStudent(id, th); };
	void updateEmailTitle(string id, string newEmail, string newTitle) { this->repo.updateEmailTitle(id, newEmail, newTitle); }

	void write() { this->repo.write(); };

};