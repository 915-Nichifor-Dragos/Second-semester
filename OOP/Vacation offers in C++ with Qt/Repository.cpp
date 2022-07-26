#include "Repository.h"

int Repository::getSizeRepository() const
{
	return this->data.size();
}

Event Repository::getElement(int index)
{
	return this->data[index];
}

void Repository::addElement(const Event& element)
{
	for (auto& ev : this->data)
	{
		if ((ev.getTitle() == element.getTitle()) and (ev.getEventDate() == element.getEventDate()))
		{
			throw addException("\nThe event can not be added!");
		}
	}
	this->data.push_back(element);
	write();
}

void Repository::removeElement(string elementTitle, date::DateTime elementDateTime)
{
	for (auto& ev : this->data)
	{
		if ((ev.getTitle() == elementTitle) and (ev.getEventDate() == elementDateTime))
		{
			this->data.erase(std::remove(data.begin(), data.end(), ev), data.end());
			write();
			return;
		}
	}
	throw updateRemoveException("\nThe event does not exist!");
}

void Repository::updateElement(string elementTitle, string description, date::DateTime elementDateTime, int number, string link)
{

	for (auto& ev : this->data)
	{
		if ((ev.getTitle() == elementTitle) and (ev.getEventDate() == elementDateTime))
		{
			if (number != -1)
				ev.setNumberOfPeople(number);
			if (description != "-1")
				ev.setDescription(description);
			if (link != "-1")
				ev.setLink(link);
			write();
			return;
		}
	}
	throw updateRemoveException("\nThe event does not exist!");
}

const vector<Event>& Repository::getList() const
{
	return this->data;
}

void testRepository()
{
	// add operation 
	Repository repository = Repository{};
	date::DateTime date1 = date::DateTime{ "23:30", "2021/12/12" };
	Event event = Event{ "Name1", "Description1", date1, 50, "http.concert1" };
	assert(repository.getSizeRepository() == 0);
	repository.addElement(event);
	assert(repository.getSizeRepository() == 1);
	try {
		repository.addElement(event);
	}
	catch (addException& e)
	{
		assert(e.what() == string("\nThe event can not be added!\nYou can not add the same element twice!\n\n"));
	}
	date::DateTime date2 = date::DateTime{ "13:30", "2021/11/30" };
	Event event2 = Event{ "Name2", "Description2", date2, 75, "http.concert2" };
	repository.addElement(event2);
	assert(repository.getSizeRepository() == 2);
	Event elem1 = repository.getElement(0);
	Event elem2 = repository.getElement(1);
	assert(elem1.getTitle() == "Name1");
	assert(elem2.getTitle() == "Name2");

	// remove operation
	repository.removeElement("Name1", date1);
	assert(repository.getSizeRepository() == 1);
	try {
		repository.removeElement("Name1", date1);
	}
	catch (updateRemoveException& e)
	{
		assert(e.what() == string("\nThe event does not exist!\nYou can remove or update an event that already exists!\n\n"));
	}
	try {
		repository.updateElement("Name1", "-1", date1, 300, "abc");
	}
	catch (updateRemoveException& e)
	{
		assert(e.what() == "\nThe event does not exist!\nYou can remove or update an event that already exists!\n\n");
	}
	Event elem3 = repository.getElement(0);
	assert(elem3.getTitle() == "Name2");

	// update operation
	repository.updateElement("Name2", "-1", date2, 400, "abcdef");
	assert(repository.getSizeRepository() == 1);
	Event elem4 = repository.getElement(0);
	assert(elem4.getTitle() == "Name2");
	assert(elem4.getDescription() == "Description2");
	assert(elem4.getEventDate() == date2);
	assert(elem4.getLink() == "abcdef");
	assert(elem4.getNumberOfPeople() == 400);
	repository.updateElement("Name2", "abc", date2, -1, "-1");
	Event elem5 = repository.getElement(0);
	assert(elem5.getTitle() == "Name2");
	assert(elem5.getDescription() == "abc");
	assert(elem5.getEventDate() == date2);
	assert(elem5.getLink() == "abcdef");
	assert(elem5.getNumberOfPeople() == 400);
}