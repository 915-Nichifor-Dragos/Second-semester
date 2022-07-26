#pragma once
#include "Event.h"

template <typename T> class Comparator
{
public:
	virtual bool compare(T first, T second) = 0;
};



class ComparatorAscendingByNumberOfPeople : public Comparator<Event>
{
	bool compare(Event first, Event second) override;
};



class ComparatorAscendingByTitle : public Comparator<Event>
{
	bool compare(Event first, Event second) override;
};

void testComparator();