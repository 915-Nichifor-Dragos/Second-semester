#include "Validators.h"
#include "Exceptions.h"

void inputValidator::checkDate(string date)
{
	if (date.size() != 10)
		throw inputException("\nInvalid date! Must be of type (yyyy/mm/dd).");
	if (date[4] != '/' or date[7] != '/')
		throw inputException("\nInvalid format! Must be of type (yyyy/mm/dd).");
	if (isdigit(date[0]) == 0 or isdigit(date[1]) == 0 or isdigit(date[2]) == 0 or isdigit(date[3]) == 0 or isdigit(date[5]) == 0 or isdigit(date[6]) == 0
		or isdigit(date[8]) == 0 or isdigit(date[9]) == 0)
		throw inputException("\nThe year, the month and the day must be integers!");

	int dateMonth = 0, dateDay = 0;
	dateMonth = (date[6] - '0') + (date[5] - '0') * 10;
	dateDay = (date[9] - '0') + (date[8] - '0') * 10;
	if (dateMonth < 1 or dateMonth > 12)
		throw inputException("\nThe month must be an integer between 1 and 12!");
	if (dateDay < 1 or dateDay > 31)
		throw inputException("\nThe day must be an integer between 1 and 31!");
}

void inputValidator::checkHour(string hour)
{
	if (hour.size() != 5)
		throw inputException("\nInvalid hour! Must be of type (hh:mm).");
	if (hour[2] != ':')
		throw inputException("\nInvalid format! Must be of type (hh:mm).");
	if (isdigit(hour[0]) == 0 or isdigit(hour[1]) == 0 or isdigit(hour[3]) == 0 or isdigit(hour[4]) == 0)
		throw inputException("\nThe hour and minutes must be integers!");

	int dateHour = 0, dateMin = 0;
	dateHour = (hour[1] - '0') + (hour[0] - '0') * 10;
	dateMin = (hour[4] - '0') + (hour[3] - '0') * 10;
	if (dateHour < 0 or dateHour > 23)
		throw inputException("\nThe hour must be an integer between 0 and 23!");
	if (dateMin < 0 or dateMin > 59)
		throw inputException("\nThe minutes must be an integer between 0 and 59!");
}
