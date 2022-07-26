#pragma once

#include "FileRepository.h"

class FileRepositoryCSV : public FileRepository {

protected:
	string outputfile;

public:

	// constructor of the CSV file repository
	FileRepositoryCSV(string filename, string outputfile) : FileRepository(filename), outputfile(outputfile) { this->write(); };

	// destructor of the CSV file repository
	~FileRepositoryCSV();

	// externally opens the CSV file
	void open();

	// writes the user list in the  CSV file and in the database
	void write() override;

};