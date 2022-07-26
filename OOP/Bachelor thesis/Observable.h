#pragma once

#include <vector>

using namespace std;

class Observer {

public:
	virtual void update() = 0;
	~Observer() {};

};

class Observalbe {

private:
	vector<Observer*> observers;

public:
	void addObserver(Observer* obs) { this->observers.push_back(obs); };
	void notify()
	{
		for (auto element : this->observers)
		{
			element->update();
		}
	}

};