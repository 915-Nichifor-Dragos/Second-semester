#pragma once

#include "Repository.h"

class Service: public Observable {

private:
	Repository repo;

public:

	Service(Repository repo) : repo(repo) {};

	vector<Post> getPosts() { return repo.getPosts(); }
	vector<User> getUsers() { return repo.getUsers(); }
	vector<Topic> getTopics() { return repo.getTopics(); }

	void addPost(string user, string text, string date, string time) { this->repo.addPost(user, text, date, time); }
	void updatePost(string id, string text) { this->repo.updatePost(id, text); }
	void addUserTopic(string topic, string user) { this->repo.addUserTopic(topic, user); }
	void write() { repo.write(); }

};