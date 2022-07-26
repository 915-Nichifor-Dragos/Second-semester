#include "Services.h"
#include <assert.h>
#include <iostream>
#include "Validators.h"
#include "Exceptions.h"

void Services::addElement(Event ev, string to)
{
	if (to == "admin")
		return this->database->addElement(ev);
	if (to == "user")
		return this->userList->addElement(ev);
}

void Services::removeElement(string elementTitle, DateTime elementDateTime, string to)
{
	if (to == "admin")
		return this->database->removeElement(elementTitle, elementDateTime);
	if (to == "user")
		return this->userList->removeElement(elementTitle, elementDateTime);
}

void Services::updateElement(string elementTitle, string description, DateTime elementDateTime, int number, string link, string to)
{
	if (to == "admin")
		return this->database->updateElement(elementTitle, description, elementDateTime, number, link);
	if (to == "user")
		return this->userList->updateElement(elementTitle, description, elementDateTime, number, link);
}

Event Services::getElement(int index)
{
	return this->database->getElement(index);
}

Event Services::getElementUser(int index)
{
	return this->userList->getElement(index);
}

int Services::getSize()
{
	return this->database->getSizeRepository();
}

int Services::getUserListSize()
{
	return this->userList->getSizeRepository();
}

bool Services::checkMonthEqual(string date, int month)
{
	int dateMonth = 0;
	dateMonth = (date[6] - '0') + (date[5] - '0') * 10;
	if (dateMonth == month)
		return true;
	return false;
}

const std::vector<Event> &Services::getDatabaseList() const
{
	return this->database->getList();
}

const std::vector<Event> &Services::getUserList() const
{
	return this->userList->getList();
}

void Services::open()
{
	this->userList->open();
}



void testServices()
{
	Repository *repoData = new Repository();
	Repository *repoUser = new Repository();
	Services services = Services(repoData, repoUser);

	DateTime date1 = DateTime{ "23:30", "2021/12/12" };
	DateTime date2 = DateTime{ "13:30", "2021/11/30" };

	assert(services.getSize() == 0);
	services.addElement(Event{ "Name1", "Description1", date1, 50, "http.concert1" }, "admin");
	assert(services.getSize() == 1);
	Event event1 = services.getElement(0);
	assert(event1.getTitle() == "Name1");
	services.addElement(Event{ "Name2", "Description2", date2, 75, "http.concert2" }, "admin");
	assert(services.getSize() == 2);
	Event event2 = services.getElement(1);
	assert(event2.getTitle() == "Name2");

	services.removeElement("Name1", date1, "admin");
	Event event3 = services.getElement(0);
	assert(event3.getTitle() == "Name2");

	services.updateElement("Name2", "abc", date2, 403, "-1", "admin");
	Event elem4 = services.getElement(0);
	assert(elem4.getTitle() == "Name2");
	assert(elem4.getDescription() == "abc");
	assert(elem4.getEventDate() == date2);
	assert(elem4.getLink() == "http.concert2");
	assert(elem4.getNumberOfPeople() == 403);

	assert(services.checkMonthEqual("2021/10/20", 10) == true);
	assert(services.checkMonthEqual("2021/10/20", 11) == false);

	services.addElement(event1, "user");
	services.updateElement("Name1", "abc", date1, 32, "http.2", "user");
	services.removeElement("Name1", date1, "user");
	services.addElement(event1, "user");
	Event event4 = services.getElementUser(0);
	assert(event4.getTitle() == "Name1");
	assert(services.getUserListSize() == 1);

	// ============================= DATE TEST

	try
	{
		inputValidator::checkDate("123");
	}
	catch (inputException& e)
	{
		assert(e.what() == string("\nInvalid date! Must be of type (yyyy/mm/dd).\nPlease enter a valid input!\n\n"));
	}

	try
	{
		inputValidator::checkDate("2021/10.32");
	}
	catch (inputException& e)
	{
		assert(e.what() == string("\nInvalid format! Must be of type (yyyy/mm/dd).\nPlease enter a valid input!\n\n"));
	}

	try
	{
		inputValidator::checkDate("2021/12/3a");
	}
	catch (inputException& e)
	{
		assert(e.what() == string("\nThe year, the month and the day must be integers!\nPlease enter a valid input!\n\n"));
	}

	try
	{
		inputValidator::checkDate("2021/13/10");
	}
	catch (inputException& e)
	{
		assert(e.what() == string("\nThe month must be an integer between 1 and 12!\nPlease enter a valid input!\n\n"));
	}

	try
	{
		inputValidator::checkDate("2021/12/32");
	}
	catch (inputException& e)
	{
		assert(e.what() == string("\nThe day must be an integer between 1 and 31!\nPlease enter a valid input!\n\n"));
	}

	inputValidator::checkDate("2020/10/20");

	// ============================= HOUR TEST

	try
	{
		inputValidator::checkHour("ab");
	}
	catch (inputException& e)
	{
		assert(e.what() == string("\nInvalid hour! Must be of type (hh:mm).\nPlease enter a valid input!\n\n"));
	}

	try
	{
		inputValidator::checkHour("23l32");
	}
	catch (inputException& e)
	{
		assert(e.what() == string("\nInvalid format! Must be of type (hh:mm).\nPlease enter a valid input!\n\n"));
	}

	try
	{
		inputValidator::checkHour("32:3a");
	}
	catch (inputException& e)
	{
		assert(e.what() == string("\nThe hour and minutes must be integers!\nPlease enter a valid input!\n\n"));
	}

	try
	{
		inputValidator::checkHour("32:23");
	}
	catch (inputException& e)
	{
		assert(e.what() == string("\nThe hour must be an integer between 0 and 23!\nPlease enter a valid input!\n\n"));
	}

	try
	{
		inputValidator::checkHour("23:69");
	}
	catch (inputException& e)
	{
		assert(e.what() == string("\nThe minutes must be an integer between 0 and 59!\nPlease enter a valid input!\n\n"));
	}

	inputValidator::checkHour("23:35");

}
