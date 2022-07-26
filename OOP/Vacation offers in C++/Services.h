#pragma once
#include "Repository.h"

class Services {

private:

	Repository* database;
	Repository* userList;

public:

	// services constructor
	Services(Repository *dataBase, Repository *userList): database(dataBase), userList(userList) {};

	// adds a new element to the list specified in 'to' parameter
	void addElement(Event ev, string to);

	// removes an element from the list specified in 'to' parameter
	void removeElement(string elementTitle, DateTime elementDateTime, string to);

	// updates an element from the list specified in 'to' parameter
	void updateElement(string elementTitle, string description, DateTime elementDateTime, int number, string link, string to);

	// returns the element on position 'index' in the administrator database
	Event getElement(int index);

	// returns the size of the administrator database
	int getSize();

	// returns the element on position 'index' in the user database
	Event getElementUser(int index);

	// returns the size of the user database
	int getUserListSize();

	// checks if a date's month is the one given as parameter
	bool checkMonthEqual(string date, int month);

	// returns the list of events for administrator
	const std::vector<Event> &getDatabaseList() const;

	// returns the list of events for user
	const std::vector<Event> &getUserList() const;

	void open();
};

void testServices();