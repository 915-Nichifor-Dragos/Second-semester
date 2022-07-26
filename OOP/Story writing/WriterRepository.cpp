#include "WriterRepository.h"

#include <fstream>

void WriterRepository::read()
{
	ifstream in(this->filename);

	if (!in.is_open())
		return;

	Writer id;

	while (in >> id)
	{
		this->elements.push_back(id);
	}

	in.close();
}
