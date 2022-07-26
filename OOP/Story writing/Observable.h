#include <vector>
#include <string>

using namespace std;

class Observer
{

public:

	virtual void update() = 0;
	virtual ~Observer() {};

};

class Observable {

private:

	vector <Observer*> observers;

public:

	void addObserver(Observer* obs) { this->observers.push_back(obs); };
	void notify()
	{
		for (auto element : this->observers)
			element->update();
	}

};