#pragma once

#include "Repository.h"

class Service {

private:
	Repository repo;

public:

	Service(Repository repo) : repo(repo) {};

	vector<Star> getStars() { return this->repo.getStars(); }
	vector<Astronomer> getAstronomers() { return this->repo.getAstronomers(); }

	void addStar(Star star) { this->repo.addStar(star); }
	void updateStar(string oldName, string name, int RA, int Dec, int diameter) { this->repo.updateStar(oldName, name, RA, Dec, diameter); }

	void write() { this->repo.write(); }
};