#pragma once

#include <fstream>
#include <vector>

#include "Astronomer.h"
#include "Star.h"
#include <algorithm>

class Repository {

private:
	string starFile;
	string astronomerFile;
	vector<Star> stars;
	vector<Astronomer> astronomers;

public:
	
	Repository(string starFile = "", string astronomerFile = "") : starFile(starFile), astronomerFile(astronomerFile) { this->read(); this->srt(); }

	vector<Star> getStars() { return this->stars; }
	vector<Astronomer> getAstronomers() { return this->astronomers; }

	void addStar(Star star) { this->stars.push_back(star); this->srt(); }
	void updateStar(string oldName, string name, int RA, int Dec, int diameter);

	void read();
	void srt() { std::sort(this->stars.begin(), this->stars.end(), [](Star s1, Star s2) { return s1.getConstelation() < s2.getConstelation(); }); }
	void write();
};