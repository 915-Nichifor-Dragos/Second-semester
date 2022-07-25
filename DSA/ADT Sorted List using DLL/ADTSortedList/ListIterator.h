#pragma once
#include "SortedIteratedList.h"

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIteratedList;
private:
	const SortedIteratedList& list;
	ListIterator(const SortedIteratedList& list);

	SortedIteratedList::Node* currentElement;

public:
	
	// iterator will point to the heap of the list
	void first();

	// iterator will point to the next element of the list
	void next();

	// returns true if the current state of the iterator is valid and false if not
	bool valid() const;

	// returns the value of the element at which the iterator currently points
    TElem getCurrent() const;
};


