#pragma once

#include "Post.h"
#include "User.h"
#include "Topic.h"

using namespace std;

class Repository {

private:
	string userFile, postFile, topicFile;

	vector<Post> posts;
	vector<User> users;
	vector<Topic> topics;

public:

	Repository(string userFile, string postFile, string topicFile) : userFile(userFile), postFile(postFile), topicFile(topicFile) { this->read(); };

	vector<Post> getPosts() { return this->posts; }
	vector<User> getUsers() { return this->users; }
	vector<Topic> getTopics() { return this->topics; }

	void read();
	void write();

	void addUserTopic(string topic, string user);
	void addPost(string user, string text, string date, string time);
	void updatePost(string id, string text);
};