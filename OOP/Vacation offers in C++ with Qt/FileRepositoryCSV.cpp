#include "FileRepositoryCSV.h"
#include <Windows.h>

void FileRepositoryCSV::open()
{
	cout << "CSV file opening...\n\n";
	ShellExecuteA(NULL, NULL, "excel.exe", this->outputfile.c_str(), NULL, SW_SHOWMAXIMIZED);
}

void FileRepositoryCSV::write()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");

	for (auto s : this->data)
	{
		file << s;
	}
	file.close();

	ofstream out(this->outputfile);
	if (!out.is_open())
		throw FileException("The file could not be opened!");

	for (auto s : this->data)
	{
		out << s;
	}
	out.close();
}

FileRepositoryCSV::~FileRepositoryCSV()
{
	this->write();
}
