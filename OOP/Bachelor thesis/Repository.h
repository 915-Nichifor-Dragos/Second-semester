#pragma once

#include "Student.h"
#include "Teacher.h"

#include <vector>

using namespace std;

class Repository {

private:
	vector<Student> students;
	vector<Teacher> teachers;
	string filenameStudents;
	string filenameTeachers;

public:

	Repository(string filenameStudents, string filenameTeachers) : filenameStudents(filenameStudents), filenameTeachers(filenameTeachers) { this->read(); };

	vector<Student>& getStudents() { return this->students; }
	vector<Teacher>& getTeachers() { return this->teachers; }

	void updateStudent(string id, string th);

	void updateEmailTitle(string id, string newEmail, string newTitle);

	void read();
	void write();

};
