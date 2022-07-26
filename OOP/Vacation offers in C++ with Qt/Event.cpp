#include "Event.h"


// DATE TIME =====================================================

date::DateTime::DateTime(string Date, string Time)
{
    this->date = Date;
    this->time = Time;
}

string date::DateTime::getDate()
{
    return this->date;
}

string date::DateTime::getTime()
{
    return this->time;
}

bool date::DateTime::operator==(DateTime a)
{
    if ((this->getDate() == a.date) and (this->getTime() == a.time))
        return true;
    return false;
}


// EVENT =========================================================


Event::Event(string Title, string Description, date::DateTime Date, int NumberOfPeople, string Link)
{
    this->date = Date;
    this->title = Title;
    this->description = Description;
    this->numberOfPeople = NumberOfPeople;
    this->link = Link;
}

string Event::getTitle() const
{
    return this->title;
}

string Event::getLink() const
{
    return this->link;
}

string Event::getDescription() const
{
    return this->description;
}

date::DateTime Event::getEventDate() const
{
    return this->date;
}

int Event::getNumberOfPeople() const
{
    return this->numberOfPeople;
}

void Event::setDescription(const string& description)
{
    this->description = description;
}

void Event::setNumberOfPeople(int number)
{
    this->numberOfPeople = number;
}

void Event::setLink(const string& link)
{
    this->link = link;
}

bool Event::operator==(Event a)
{
    if ((this->date == a.date) and (this->title == a.title))
        return true;
    return false;
}

void Event::open()
{
    ShellExecuteA(NULL, NULL, "chrome.exe", this->getLink().c_str(), NULL, SW_SHOWMAXIMIZED);
}

istream& operator>>(istream& is, Event& ev)
{
    if (is.eof())
        is.setstate(ios_base::failbit); // operator bool returns true for eof => enforce false to terminate the loop
    else
    {
        try {
            string line;
            getline(is, line);
            vector<string> elements;
            elements = tokenize(line, ',');
            if (elements.size() == 0)
                return is;
            ev.title = elements[0];
            ev.description = elements[1];
            inputValidator::checkDate(elements[2]);
            inputValidator::checkHour(elements[3]);
            ev.date = date::DateTime(elements[2], elements[3]);
            ev.numberOfPeople = stoi(elements[4]);
            ev.link = elements[5];

        }
        catch (inputException& e)
        {
            try {
                throw inputFileException("\nThe event in the file is not valid.");
            }
            catch (inputFileException& e)
            {
                cout << e.what();
            }
        }
    }
    return is;
}

ostream& operator<<(ostream& os, const Event& ev)
{
    date::DateTime date = ev.getEventDate();
    stringstream nrPeople;
    nrPeople << ev.numberOfPeople;
    os << ev.getTitle() << "," << ev.getDescription() << "," << date.getDate() << "," << date.getTime() << "," << nrPeople.str() << "," << ev.getLink() << "\n";

    return os;
}



// TEST =====================================================



void testEventDate()
{
    date::DateTime date = date::DateTime{ "23:30", "2021/12/12" };
    Event event = Event{ "Name", "Description", date, 50, "http.concert" };
    assert(event.getTitle() == "Name");
    assert(event.getDescription() == "Description");
    date::DateTime d = event.getEventDate();
    assert(d.getTime() == "2021/12/12");
    assert(d.getDate() == "23:30");
    assert(event.getNumberOfPeople() == 50);
    assert(event.getLink() == "http.concert");
    date::DateTime date2 = date::DateTime{ "13:30", "2002/03/02" };
    assert((date == date2) == false);
}