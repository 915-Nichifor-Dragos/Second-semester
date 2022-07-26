#pragma once
#include "FileRepository.h"

class FileRepositoryHTML : public FileRepository {

protected:
	string outputfile;

public:


	// constructor of the HTML file repository
	FileRepositoryHTML(string filename, string outputfile) : FileRepository(filename), outputfile(outputfile) { this->write(); };

	// destructor of the HTML file repository
	~FileRepositoryHTML();

	// externally opens the HTML file
	void open();

	// writes the user list in the HTML file and in the database
	void write() override;

private:

	string convertToHTMLFile();

	string convertToHTMLFileExtra();

};