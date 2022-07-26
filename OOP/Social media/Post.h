#pragma once

#include <string>

using namespace std;

class Post {

private:
	string id;
	string text;
	string date;
	string time;
	string user;

public:

	Post(string id="", string text="", string date="", string time="", string user="") : id(id), text(text), date(date), time(time), user(user) {};

	string getId() { return this->id; }
	string getText() { return this->text; }
	string getDate() { return this->date; }
	string getTime() { return this->time; }
	string getUser() { return this->user; }

	void setText(string text) { this->text = text; }

	friend istream& operator>>(istream& is, Post& us);
	friend ostream& operator<<(ostream& os, Post& us);

};