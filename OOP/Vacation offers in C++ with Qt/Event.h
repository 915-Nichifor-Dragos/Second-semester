#pragma once

#include <assert.h>
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <string>
#include "Validators.h"
#include "Exceptions.h"
#include <vector>
#include "Utilities.h"

using namespace std;

namespace date {

	class DateTime {

	private:

		string date;
		string time;

	public:

		// constructor
		DateTime(string Date = "", string Time = "");

		// returns the current date
		string getDate();

		// returns the current time
		string getTime();

		// operator ==
		bool operator==(DateTime a);

	};
}


class Event {

private:

	string title;
	string description;
	date::DateTime date;
	int numberOfPeople;
	string link;

public:

	// constructor
	Event(string Title = "", string Description = "", date::DateTime Date = date::DateTime(), int NumberOfPeople = 0, string Link = "");

	// returns the current title
	string getTitle() const;

	// returns the current description
	string getDescription() const;

	// returns the current date
	date::DateTime getEventDate() const;

	// returns the current number of people
	int getNumberOfPeople() const;

	// returns the current link
	string getLink() const;

	// set a new description
	void setDescription(const string& description);

	// set a new number of people
	void setNumberOfPeople(int number);

	// set a new link
	void setLink(const string& link);

	// operator ==
	bool operator==(Event a);

	void open();

	// read event from file
	friend istream& operator>>(istream& is, Event& ev);

	// write event to file
	friend ostream& operator<<(ostream& os, const Event& ev);
};

void testEventDate();