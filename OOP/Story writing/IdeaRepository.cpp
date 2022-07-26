#include "IdeaRepository.h"

#include <fstream>
#include <algorithm>

void IdeaRepository::read()
{
	ifstream in(this->filename);

	if (!in.is_open())
		return;

	Idea id;
	
	while (in >> id)
	{
		this->elements.push_back(id);
	}

	in.close();
}

void IdeaRepository::updateDescriptionIdeea(Idea id, string str)
{
	for (int i = 0 ; i < this->elements.size() ; i++)
	{
		if (elements[i].getDescription() == id.getDescription())
			elements[i].setDescription(str);
	}
}

void IdeaRepository::sort()
{
	std::sort(this->elements.begin(), this->elements.end(), [](Idea i1, Idea i2) {return i1.getAct() < i2.getAct(); });
}
