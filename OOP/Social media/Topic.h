#pragma once

#include <string>
#include <vector>

#include "User.h"

using namespace std;

class Topic {

private:
	string topic;
	vector<string> users;

public:

	Topic(string topic="", vector<string> users = {}) : topic(topic), users(users) {};

	string getTopic() { return this->topic; }
	vector<string> getUsers() { return this->users; }

	void update(string user) { this->users.push_back(user); }

	friend istream& operator>>(istream& is, Topic& us);
	friend ostream& operator<<(ostream& os, Topic& us);
};