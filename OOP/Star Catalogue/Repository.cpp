#include "Repository.h"

void Repository::updateStar(string oldName, string name, int RA, int Dec, int diameter)
{
	for (int i = 0; i < this->stars.size(); i++)
	{
		if (this->stars[i].getName() == oldName)
		{
			this->stars[i].setName(name);
			this->stars[i].setDiameter(diameter);
			this->stars[i].setDec(Dec);
			this->stars[i].setRA(RA);
		}
	}
}

void Repository::read()
{
	ifstream inS(this->starFile);

	if (!inS.is_open())
		return;

	Star st;
	while (inS >> st)
	{
		this->stars.push_back(st);
	}

	inS.close();

	ifstream inA(this->astronomerFile);

	if (!inA.is_open())
		return;

	Astronomer as;
	while (inA >> as)
	{
		this->astronomers.push_back(as);
	}

	inA.close();

}

void Repository::write()
{
	ofstream out(this->starFile);

	if (!out.is_open())
		return;

	std::sort(this->stars.begin(), this->stars.end(), [](Star s1, Star s2) {if (s1.getConstelation() == s2.getConstelation()) return s1.getDiameter() < s2.getDiameter(); return s1.getConstelation() < s2.getConstelation(); });

	for (auto element : this->stars)
		out << element << "\n";

	out.close();
}
