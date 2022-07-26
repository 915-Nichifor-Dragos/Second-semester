#pragma once
#include "Idea.h"

#include <vector>

class IdeaRepository {

private:
	string filename;
	vector<Idea> elements;

public:

	IdeaRepository(string filename) : filename(filename) { this->read(); };
	~IdeaRepository() = default;

	void read();

	vector<Idea>& getList() { return this->elements; };

	// adds a new idea to the Repository by appening it in the 'elements' vector
	void addElement(Idea id) { this->elements.push_back(id); this->sort(); };

	// updates the status of the idea on the position 'value' to "Accepted"
	void updateElement(int value) { this->elements[value].setStatus("Accepted"); };

	void updateDescriptionIdeea(Idea id, string str);
	void sort();
};