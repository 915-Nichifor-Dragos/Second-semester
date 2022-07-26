#pragma once
#include "Writer.h"

#include <vector>

class WriterRepository {

private:
	string filename;
	vector<Writer> elements;

public:

	WriterRepository(string filename) : filename(filename) { this->read(); };
	~WriterRepository() = default;

	void read();

	vector<Writer> getList() { return this->elements; };

};