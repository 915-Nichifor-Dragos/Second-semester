#pragma once
#include <vector>
#include "Event.h"
#include <iostream>

using namespace std;

class Repository{

protected:

	vector<Event> data;

public:
	
	// repository constructor
	Repository(){};

	// repository destructor
	virtual ~Repository(){};

	// returns the size of the repository
	int getSizeRepository() const;

	// returns the element on position 'index' from the repository
	Event getElement(int index);

	// adds an element to the repository
	void addElement(const Event& element);

	// removes an element from the repository
	void removeElement(string elementTitle, DateTime elementDateTime);

	// updates an element 
	void updateElement(string elementTitle, string description, DateTime elementDateTime, int number, string link);

	// returns the list of events
	const vector<Event> &getList() const;

	// writes to a file (function body is empty for memory repository)
	virtual void write() {};

	// reads from a file (function body is empty for memory repository)
	virtual void read() {};

	// opens a file containting the data in memory (memory repository does not hold data in any file)
	virtual void open() { cout << "Memory repository can not be opened using a file.\n\n"; };
};

void testRepository();