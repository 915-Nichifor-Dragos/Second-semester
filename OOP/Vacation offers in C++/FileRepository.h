#pragma once
#include "Repository.h"
#include "Exceptions.h"
#include <fstream>
#include <iostream>

class FileRepository: public Repository {

protected:

	string filename;

public:
	
	// constructor of the file repository
	FileRepository(string filename) : Repository(), filename(filename) { this->read(); };

	// destructor of the file repository
	virtual ~FileRepository();

	// reads from the file in which we store the entities
	void read();

	// writes to the file in which we store the entities
	virtual void write();

	// the function that will open the CSV/HTML file for the child classes of 'FileRepository'
	virtual void open() {};
};