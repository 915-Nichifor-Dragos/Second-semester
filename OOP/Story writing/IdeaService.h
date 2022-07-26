#pragma once

#include "Observable.h"
#include "IdeaRepository.h"

class IdeaService : public Observable {

private:

	IdeaRepository& repo;

public:

	IdeaService(IdeaRepository& repo) : repo(repo) {};
	~IdeaService() = default;

	IdeaRepository& getRepo() { return this->repo; };

	vector<Idea> getList() { return this->repo.getList(); };

	void addElement(Idea id) { this->repo.addElement(id); };
	void updateElement(int value) { this->repo.updateElement(value); };
	void updateDescriptionIdeea(Idea id, string str) {return this->repo.updateDescriptionIdeea(id, str); };
	void sortRepo() { repo.sort(); };
};