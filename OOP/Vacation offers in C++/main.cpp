#include <iostream>
#include "Event.h"
#include "Repository.h"
#include "Services.h"
#include "UI.h"
#include <crtdbg.h>
#include "Exceptions.h"
#include <algorithm>
#include <iterator>
#include "FileRepository.h"
#include "FileRepositoryCSV.h"
#include "FileRepositoryHTML.h"
#include "Comparator.h"

void test()
{
	testEventDate();
	cout << "DONE EVENT AND DATE TEST\n";
	testRepository();
	cout << "DONE REPOSITORY TEST\n";
	testServices();
	cout << "DONE SERVICES TEST\n";
	testComparator();
	cout << "DONE COMPARATOR TEST\n";
}

bool check_command(int command)
{
	if (command == 1 or command == 2 or command == 3)
		return true;
	return false;
}

bool check_mode(int mode)
{
	if (mode == 1 or mode == 2)
		return true;
	return false;
}

void print_choose_repo_menu()
{
	cout << "1) CSV type repository.\n";
	cout << "2) HTML type repository.\n";
}

void print_menu()
{
	cout << "1) Use as administrator.\n";
	cout << "2) Use as user.\n";
	cout << "3) Exit.\n";
}

void print_open_menu()
{
	cout << "1) Memory.\n";
	cout << "2) File.\n";
}

void start_keyboard()
{
	int command;

	Repository* userlist = new Repository();
	Repository* database = new Repository();

	Services services = Services(database, userlist);

	UI ui = UI(services);

	DateTime data1 = DateTime{ "2021/11/30", "21:40" };
	DateTime data2 = DateTime{ "2021/01/06", "20:30" };
	DateTime data3 = DateTime{ "2021/01/19", "08:30" };
	DateTime data4 = DateTime{ "2021/09/05", "11:00" };
	DateTime data5 = DateTime{ "2021/07/25", "17:00" };
	DateTime data6 = DateTime{ "2021/06/26", "15:45" };
	DateTime data7 = DateTime{ "2021/02/01", "13:15" };
	DateTime data8 = DateTime{ "2021/03/12", "20:00" };
	DateTime data9 = DateTime{ "2021/04/24", "19:40" };
	DateTime data10 = DateTime{ "2021/10/30", "16:20" };

	ui.addElement("Treasure Hunt in Carol Park", "Entertainment", data1, 500, "https://shop.secretromania.com/product/treasure-hunt-in-parcul-carol-din-bucuresti/");
	ui.addElement("Sports Festival", "Sports", data2, 200, "https://www.sportsfestival.com/");
	ui.addElement("Form Days 2022", "Music", data3, 100, "https://www.songkick.com/festivals/3298258-form-days/id/39465933-form-days-festival-2022");
	ui.addElement("The history of romanians", "History", data8, 750, "https://clujulcultural.ro/istoria-romanilor-pe-scurt-pusa-in-scena-de-magic-puppet/");
	ui.addElement("Discoteca 80", "Music", data4, 300, "https://www.discoteca80.ro/");
	ui.addElement("Untold 2022", "Music", data5, 200000, "https://untold.com/");
	ui.addElement("Magic Show", "Entertainment", data7, 1000, "https://teatrulgong.ro/places/sibiu-magic-show-aocisubeuyp5iw");
	ui.addElement("Nabucco", "Music", data6, 5000, "https://operacluj.ro/spectacole/2021-2022/nabucco-20-march-2022-18-30/");
	ui.addElement("IT Contest 2022", "Technology", data9, 500, "https://itcompetition.hilti.group/");
	ui.addElement("The Red Theater", "Opera", data10, 500, "https://teatrulrosu.ro/");

	cout << "\nAll entities have been read! They are now accessible in memory!\n\n";

	while (true)
	{
		print_menu();
		cout << "\nYour command is: ";
		cin >> command;
		cout << "\n";
		if (check_command(command) == true)
		{
			if (command == 1)
			{
				ui.startUiAdministrator();
			}
			if (command == 2)
			{
				ui.startUiUser();
			}
			if (command == 3)
			{
				cout << "Exiting...\n";
				break;
			}
		}
		else
			cout << "Please enter a valid command!\n\n";
	}

}


void start_file()
{
	int command;

	int type;
	cout << "\n";
	print_choose_repo_menu();
	cout << "The type of file the database will work with is: ";
	cin >> type;
	if (check_mode(type) == false)
		throw startException("\nPlease enter a valid type of file!");

	FileRepository* database = new FileRepository("data_admin.txt");
	cout << "\nDatabase was read from memory!\n";

	//FileRepository* userlist = new FileRepository("data_user.txt");

	if (type == 1)
	{
		FileRepositoryCSV* userlist = new FileRepositoryCSV("data_user.txt", "output.csv");
		cout << "Userlist was read from memory!\n\n";

		Services services = Services(database, userlist);

		UI ui = UI(services);

		while (true)
		{
			print_menu();
			cout << "\nYour command is: ";
			cin >> command;
			cout << "\n";
			if (check_command(command) == true)
			{
				if (command == 1)
				{
					ui.startUiAdministrator();
				}
				if (command == 2)
				{
					ui.startUiUser();
				}
				if (command == 3)
				{
					cout << "Exiting...\n";
					delete database;
					delete userlist;
					break;
				}
			}
			else
				cout << "Please enter a valid command!\n\n";
		}
	}
	else
	{
		FileRepositoryHTML* userlist = new FileRepositoryHTML("data_user.txt", "output.html");
		cout << "Userlist was read from memory!\n\n";

		Services services = Services(database, userlist);

		UI ui = UI(services);

		while (true)
		{
			print_menu();
			cout << "\nYour command is: ";
			cin >> command;
			cout << "\n";
			if (check_command(command) == true)
			{
				if (command == 1)
				{
					ui.startUiAdministrator();
				}
				if (command == 2)
				{
					ui.startUiUser();
				}
				if (command == 3)
				{
					cout << "Exiting...\n";
					delete database;
					delete userlist;
					break;
				}
			}
			else
				cout << "Please enter a valid command!\n\n";
		}
	}
}


int main()
{
	test();
	cout << "\nPROGRAM STARTING NOW...\n\n";
	print_open_menu();
	cout << "The type of the repository will be: ";

	try {
		int mode;
		cin >> mode;
		if (check_mode(mode) == false)
			throw startException("\nInvalid start command!");
		if (mode == 1)
			start_keyboard();
		else
			start_file();
	}
	catch (startException& e)
	{
		cout << e.what();
	}

	return 0;
}