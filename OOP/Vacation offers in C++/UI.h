#pragma once
#include "Services.h"

class UI {

private:

	Services services;

public:

	// user interface constructor
	UI(Services services): services(services) {};

	// adds a new element to the database
	void addElement(string title, string description, DateTime date, int numberOfPeople, string link);

	// removes an element from the database
	void removeElement(string elementTitle, DateTime elementDateTime);

	// updates an element from the databse
	void updateElement(string elementTitle, string description, DateTime elementDateTime, int number, string link);

	// prints the administrator menu
	void printElementsAdministrator();

	// checks if the administrator command is valid
	bool checkCommandValidityAdministrator(int command);

	// prints the menu of operations for the administrator
	void printMenuAdministrator();

	// starts the program as administrator
	void startUiAdministrator();

	// prints the events for the user
	void printEvents();

	// prints the menu for the user
	void printMenuUser();

	// checks if the user command is valid
	bool checkCommandValidityUser(int command);

	// prints the events the user wants to go to
	void printEventThatUserAttendsTo();

	// starts the program as user
	void startUiUser();

};