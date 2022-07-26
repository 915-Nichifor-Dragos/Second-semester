#pragma once
#include <string>

using namespace std;


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


class Event {

private:

	string title;
	string description;
	DateTime date;
	int numberOfPeople;
	string link;

public:

	// constructor
	Event(string Title = "", string Description = "", DateTime Date = DateTime(), int NumberOfPeople = 0, string Link = "");

	// returns the current title
	string getTitle() const;

	// returns the current description
	string getDescription() const;

	// returns the current date
	DateTime getEventDate() const;

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

	// read event from file
	friend istream& operator>>(istream& is, Event& ev);

	// write event to file
	friend ostream& operator<<(ostream& os, const Event& ev);
};

void testEventDate();