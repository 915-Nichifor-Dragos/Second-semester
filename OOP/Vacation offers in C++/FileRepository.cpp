#include "FileRepository.h"
#include "Event.h"

using namespace std;

void FileRepository::read()
{
	try {
		ifstream file(this->filename);

		if (!file.is_open())
			throw FileException("The file '" + this->filename + "' could not be opened!\n\n");

		Event ev;
		while (file >> ev)
		{
			this->data.push_back(ev);
		}

		file.close();
	}
	catch (FileException& e)
	{
		cout << e.what();
	}
}

void FileRepository::write()
{
	ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");

	for (auto s : this->data)
	{
		file << s;
	}

	file.close();
}

FileRepository::~FileRepository()
{
	this->write();
}
