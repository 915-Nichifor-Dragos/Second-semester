#include "UI.h"
#include <iostream>
#include <cstring>
#include <Windows.h>
#include "Validators.h"
#include "Exceptions.h"
#include <algorithm>
#include "Event.h"

using namespace std;


void UI::addElement(string title, string description, DateTime date, int numberOfPeople, string link)
{
	this->services.addElement(Event{ title, description, date, numberOfPeople, link }, "admin");
}

void UI::removeElement(string elementTitle, DateTime elementDateTime)
{
	this->services.removeElement(elementTitle, elementDateTime, "admin");
}

void UI::updateElement(string elementTitle, string description, DateTime elementDateTime, int number, string link)
{
	this->services.updateElement(elementTitle, description, elementDateTime, number, link, "admin");
}

void UI::printElementsAdministrator()
{
	if (this->services.getSize() == 0)
		cout << "There are no current events!\n";
	int i = 0;
	for (auto ev : this->services.getDatabaseList())
	{
		DateTime date = ev.getEventDate();
		cout << "[] Event no." << i + 1 << " " << "Title: " << ev.getTitle() << " | " << "Description: " << ev.getDescription() << " | ";
		cout << "Date and time: " << date.getDate() << ", " << date.getTime() << endl;

		cout << "   Number of people: " << ev.getNumberOfPeople() << " | " << "Link: " << ev.getLink() << "\n";
		i++;
	}
	cout << "\n";
}

bool UI::checkCommandValidityAdministrator(int command)
{
	if (command != 1 and command != 2 and command != 3 and command != 4 and command != 5)
		throw commandException("Please enter a valid command!\n\n");
	return true;
}

void UI::printMenuAdministrator()
{
	cout << "1) Add a new event\n";
	cout << "2) Remove an event\n";
	cout << "3) Update an event\n";
	cout << "4) Print all the events\n";
	cout << "5) Back to menu\n";
}

void UI::startUiAdministrator()
{
	while (true)
	{
		try {

			this->printMenuAdministrator();
			cout << "\nPlease enter your command: ";
			int command;
			cin >> command;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
				throw commandException("\nPlease enter a valid command!\n\n");
			}
			cout << "\n";
			if (checkCommandValidityAdministrator(command) == true)
			{
				cin.ignore();
				if (command == 1)
				{
					int numberOfPeople;
					string title, description, link, hour, date;

					cout << "Please enter the title of the event: ";
					getline(cin, title);

					cout << "Please enter the description of the event: ";
					getline(cin, description);

					cout << "Please enter the date in which the event will be hold: ";
					getline(cin, date);
					inputValidator::checkDate(date);
					cout << "Please enter the hour at which the event will be hold: ";
					getline(cin, hour);
					inputValidator::checkHour(hour);
					DateTime dateTime = DateTime(date, hour);

					cout << "Please enter the number of people that will be present at the event: ";
					cin >> numberOfPeople;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore();
						throw inputException("\nThe number of people must be an integer!");
					}

					cin.ignore();
					cout << "Please enter the link of the event: ";
					getline(cin, link);

					this->addElement(title, description, dateTime, numberOfPeople, link);
						cout << "\nSuccesfuly added new event!\n\n";
				}

				if (command == 2)
				{
					string title, date, hour;

					cout << "Please enter the title of the event: ";
					getline(cin, title);

					cout << "Please enter the date in which the event will be hold (yyyy/mm/dd): ";
					getline(cin, date);
					inputValidator::checkDate(date);
					cout << "Please enter the hour at which the event will be hold (hh/mm): ";
					getline(cin, hour);
					inputValidator::checkHour(hour);

					DateTime dateTime = DateTime(date, hour);

					removeElement(title, dateTime);
					
					cout << "\nSuccesfuly removed the event!\n\n";

					try {
						this->services.removeElement(title, dateTime, "user");
					}
					catch(updateRemoveException& e)
					{

					}
				}

				if (command == 3)
				{
					int numberOfPeople;
					string title, description, link, hour, date;

					cout << "Please enter the title of the event: ";
					getline(cin, title);

					cout << "Please enter the date in which the event will be hold (yyyy/mm/dd): ";
					getline(cin, date);
					inputValidator::checkDate(date);
					cout << "Please enter the new hour at which the event will be hold (hh:mm): ";
					getline(cin, hour);
					inputValidator::checkHour(hour);
					DateTime dateTime = DateTime(date, hour);

					cout << "Please enter the new description of the event (-1 if you do not want to change it): ";
					getline(cin, description);

					cout << "Please enter the new number of people that will be present at the event (-1 if you do not want to change it): ";
					cin >> numberOfPeople;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore();
						throw inputException("\nPlease enter a valid command!\n\n");
					}

					cin.ignore();
					cout << "Please enter the new link of the event (-1 if you do not want to change it): ";
					getline(cin, link);

					updateElement(title, description, dateTime, numberOfPeople, link);
					
					try {
						this->services.updateElement(title, description, dateTime, numberOfPeople, link, "user");
					}
					catch (updateRemoveException& e)
					{

					}
					cout << "\nSuccesfuly updated new event!\n\n";
				}

				if (command == 4)
				{
					this->printElementsAdministrator();
				}

				if (command == 5)
				{
					cout << "Returning to main menu...\n\n";
					break;
				}

			}
		}
		catch (commandException& e)
		{
			cout << e.what();
		}
		catch (inputException& e)
		{
			cout << e.what();
		}
		catch (addException& e)
		{
			cout << e.what();
		}
		catch (updateRemoveException& e)
		{
			cout << e.what();
		}
	}
}


// ===============================================================================================================


void UI::printMenuUser()
{
	cout << "1) Show events for a month.\n";
	cout << "2) Print all the events you liked.\n";
	cout << "3) Delete an event from your list.\n";
	cout << "4) See your as a CSV or HTML file.\n";
	cout << "5) Back to menu.\n";
}

bool UI::checkCommandValidityUser(int command)
{
	if (command == 1 or command == 2 or command == 3 or command == 4)
		return true;
	throw commandException("\nPlease enter a valid command!\n\n");
}

void UI::printEvents()
{
	int month;
	cout << "See the events for a given month.\n";
	cout << "The given month is (integer from 1 to 12). If you want to see all the events press 0: ";
	cin >> month;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		throw inputException("\nThe month must be an integer!");
	}

	cout << endl;
	vector<Event> v;
	vector<Event> database = this->services.getDatabaseList();

	if (month == 0)
	{
		for (auto ev : database)
			v.push_back(ev);
	}
	else
	{
		if (month < 1 or month > 12)
			throw inputException("\nThe month must be an integer between 1 and 12!");

		copy_if(database.begin(), database.end(), back_inserter(v), [&](const Event ev) { return this->services.checkMonthEqual(ev.getEventDate().getDate(), month); });

	}

	sort(v.begin(), v.end(), [](const Event ev1, const Event ev2) { return ev1.getEventDate().getDate() < ev2.getEventDate().getDate(); });

	int i = 0;
	while (true and !v.empty())
	{
		Event event = v[i];
		DateTime date = event.getEventDate();

		cout << "[] Title: " << event.getTitle() << " | " << "Description: " << event.getDescription() << " | ";
		cout << "Date and time: " << date.getDate() << ", " << date.getTime() << " | " << "People going: " << event.getNumberOfPeople() << endl;
		cout << "We recommend the following event! Would you like to participate?\n1) Yes\n2) No " << "\n";

		ShellExecuteA(NULL, NULL, "chrome.exe", event.getLink().c_str(), NULL, SW_SHOWMAXIMIZED);

		int result;
		cout << "Your command: ";
		cin >> result;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			throw inputException("\nThe month must be an integer!\n\n");
		}

		if (result == 1)
		{
			try {
				services.addElement(event, "user");

				v.erase(v.begin() + i);
				this->services.updateElement(event.getTitle(), event.getDescription(), event.getEventDate(), event.getNumberOfPeople() + 1, event.getLink(), "admin");
				this->services.updateElement(event.getTitle(), event.getDescription(), event.getEventDate(), event.getNumberOfPeople() + 1, event.getLink(), "user");
				cout << "Succesfully added to favorited events.\n\n";
			}
			catch (addException &e)
			{
				v.erase(v.begin() + i);
				cout << e.what();
			}
		}
		else
		{
			cout << "We hope that you will like the other events.\n\n";
			i++;
		}

		cout << "Would you like to continue?\n1) Next\n2) Stop\n\n";
		int res;
		cout << "Your choice: ";
		cin >> res;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			throw inputException("\nThe month must be an integer!\n\n");
		}
		cout << endl;
		if (res == 1)
		{
			if (i == v.size())
				i = 0;
		}
		if (res == 2)
		{
			cout << "Returning to user menu.\n\n";
			return;
		}
	}
	cout << "There are no more events for you!\n\n";
}

void UI::printEventThatUserAttendsTo()
{
	if (this->services.getUserListSize() == 0)
		cout << "You do not have any favorited events!\n";

	for (auto ev: this->services.getUserList())
	{
		DateTime date = ev.getEventDate();
		cout << "[] Title: " << ev.getTitle() << " | " << "Description: " << ev.getDescription() << " | ";
		cout << "Date and time: " << date.getDate() << ", " << date.getTime() << endl << "   Number of people: " << ev.getNumberOfPeople();
		cout << "\n";

	}
	cout << "\n";
}

void UI::startUiUser()
{
	while (true)
	{
		try
		{
			this->printMenuUser();
			int command;
			cout << "\nPlease enter your command: ";
			cin >> command;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
				throw commandException("\nPlease enter a valid command!\n\n");
			}
			cout << "\n";

			if (command == 5)
			{
				cout << "Returning to main menu...\n\n";
				break;
			}

			if (checkCommandValidityUser(command) == true)
			{
				if (command == 1)
				{
					printEvents();
				}
				if (command == 2)
				{
					this->printEventThatUserAttendsTo();
				}
				if (command == 3)
				{
					cin.ignore();
					string title, date, hour;

					cout << "Please enter the title of the event: ";
					getline(cin, title);
					cout << "Please enter the date in which the event will be hold (yyyy/mm/dd): ";
					getline(cin, date);
					inputValidator::checkDate(date);
					cout << "Please enter the hour at which the event will be hold (hh/mm): ";
					getline(cin, hour);
					inputValidator::checkHour(hour);

					DateTime dateTime = DateTime(date, hour);

					this->services.removeElement(title, dateTime, "user");
					cout << "\nSuccesfuly removed the event!\n\n";
				}
				if (command == 4)
				{
					this->services.open();
				}
			}
		}
		catch (commandException& e)
		{
			cout << e.what();
		}
		catch (inputException& e)
		{
			cout << e.what();
		}
		catch (addException& e)
		{
			cout << e.what();
		}
		catch (updateRemoveException& e)
		{
			cout << e.what();
		}
	}
}