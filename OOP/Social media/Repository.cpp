#include "Repository.h"

#include <fstream>

void Repository::read()
{
	ifstream inU(this->userFile);
	if (!inU.is_open())
		return;
	User u;
	while (inU >> u)
	{
		this->users.push_back(u);
	}
	inU.close();



	ifstream inP(this->postFile);
	if (!inP.is_open())
		return;
	Post p;
	while (inP >> p)
	{
		this->posts.push_back(p);
	}
	inP.close();



	ifstream inT(this->topicFile);
	if (!inT.is_open())
		return;
	Topic t;
	while (inT >> t)
	{
		this->topics.push_back(t);
	}
	inT.close();
}

void Repository::write()
{
	ofstream outP(this->postFile);
	for (auto element : this->posts)
		outP << element << "\n";
	outP.close();

	ofstream outT(this->topicFile);
	for (auto element : this->topics)
		outT << element << "\n";
	outT.close();
}

void Repository::addUserTopic(string topic, string user)
{
	for (int i = 0; i < this->topics.size(); i++)
	{
		if (this->topics[i].getTopic() == topic)
		{
			this->topics[i].update(user);
			return;
		}
	}
}

void Repository::addPost(string user, string text, string date, string time)
{
	string id = to_string(stoi(this->posts[posts.size() - 1].getId()) + 1);
	Post pst(id, text, date, time, user);
	this->posts.push_back(pst);
}

void Repository::updatePost(string id, string text)
{
	for (int i = 0; i < this->posts.size(); i++)
	{
		if (posts[i].getId() == id)
		{
			posts[i].setText(text);
			return;
		}
	}
}
