#pragma once

#include <string>

using namespace std;

class Student {

private:
	string id;
	string name;
	string email;
	int year;
	string title;
	string coordinator;

public:
	Student(string id = "", string name = "", string email = "", int year = -1, string title = "No title", string coordinator = "") : id(id), name(name), email(email), year(year), title(title), coordinator(coordinator) {};
	string getId() { return this->id; }
	string getName() { return this->name; }
	string getEmail() { return this->email; }
	int getYear() { return this->year; }
	string getTitle() { return this->title; }
	string getCoordinator() { return this->coordinator; }

	void setCoordinator(string coordinator) { this->coordinator = coordinator; };
	void setTitle(string title) { this->title = title; };
	void setEmail(string email) { this->email = email; };

	friend istream& operator>>(istream& is, Student& st);
	friend ostream& operator<<(ostream& os, Student st);
};