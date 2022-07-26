#pragma once

#include "WriterRepository.h"

class WriterService {

private:

	WriterRepository repo;

public:

	WriterService(WriterRepository repo) : repo(repo) {};
	~WriterService() = default;

	vector<Writer> getList() { return this->repo.getList(); };

};