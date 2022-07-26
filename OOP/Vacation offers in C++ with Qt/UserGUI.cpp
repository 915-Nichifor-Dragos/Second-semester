#include "UserGUI.h"


UserGUI::UserGUI(Services* services) : services(services)
{
	this->titleLineEdit = new QLineEdit{};
	this->descriptionLineEdit = new QLineEdit{};
	this->dateLineEdit = new QLineEdit{};
	this->hourLineEdit = new QLineEdit{};
	this->numberOfPeopleLineEdit = new QLineEdit{};
	this->linkLineEdit = new QLineEdit{};
	this->start();
}


void UserGUI::start()
{
	this->eventList = new QListWidget{};
	this->userList = new QListWidget{};

	this->gL = new QGridLayout{};
	this->hL = new QHBoxLayout{};

	this->setLayout(gL);
	populateList();

	this->font = new QFont{ "System", 10, 63, false };
	this->label = new QLabel{};

	this->eventDetails = new QFormLayout{};
	this->addButton = new QPushButton{ "Add an event" };
	this->removeButton = new QPushButton{ "Remove an event" };
	this->backButton = new QPushButton{ "Back" };
	this->openRepositoryButton = new QPushButton{ "Open CSV/HTML" };
	this->openEventButton = new QPushButton{ "Open Link" };

	this->eventDetails->addRow("Title:", titleLineEdit);
	this->eventDetails->addRow("Description:", descriptionLineEdit);
	this->eventDetails->addRow("Date:", dateLineEdit);
	this->eventDetails->addRow("Hour:", hourLineEdit);
	this->eventDetails->addRow("Number of people:", numberOfPeopleLineEdit);
	this->eventDetails->addRow("Link:", linkLineEdit);

	this->vLAdmin = new QVBoxLayout{};
	vLAdmin->addWidget(this->eventList);
	QLabel* labelList = new QLabel{};
	labelList->setFont(*font);
	labelList->setText("<p style='text-align:center'><font color=#4D2D52>Event list</font></p>");
	vLAdmin->addWidget(labelList);

	this->vLUser = new QVBoxLayout{};
	vLUser->addWidget(this->userList);
	QLabel* labelUser = new QLabel{};
	labelUser->setFont(*font);
	labelUser->setText("<p style='text-align:center'><font color=#4D2D52>User list</font></p>");
	vLUser->addWidget(labelUser);

	connectSlotsAndSignals();

	this->label->setFont(*font);
	label->setText("<p style='text-align:center'><font color=#4D2D52>User menu</font></p>");
	this->setStyleSheet("background-color:#D9DBF1");

	this->label->setFont(*font);
	label->setText("<p style='text-align:center'><font color=#4D2D52>Admin menu</font></p>");
	this->addButton->setStyleSheet("background-color: #f2f2f2;");
	this->removeButton->setStyleSheet("background-color: #f2f2f2;");
	this->openEventButton->setStyleSheet("background-color: #f2f2f2;");
	this->openRepositoryButton->setStyleSheet("background-color: #f2f2f2;");
	this->backButton->setStyleSheet("background-color: #f2f2f2;");

	this->titleLineEdit->setStyleSheet("background-color: white;");
	this->descriptionLineEdit->setStyleSheet("background-color: white;");
	this->dateLineEdit->setStyleSheet("background-color: white;");
	this->hourLineEdit->setStyleSheet("background-color: white;");
	this->numberOfPeopleLineEdit->setStyleSheet("background-color: white;");
	this->linkLineEdit->setStyleSheet("background-color: white;");

	this->userList->setStyleSheet("background-color: white;");
	this->eventList->setStyleSheet("background-color: white;");

	this->setStyleSheet("background-color:#D9DBF1;");

	hL->addWidget(addButton);
	hL->addWidget(removeButton);
	hL->addWidget(openRepositoryButton);
	hL->addWidget(openEventButton);
	hL->addWidget(backButton);

	gL->addWidget(this->label, 0, 0, 1, 3);
	gL->addLayout(vLUser, 1, 1);
	gL->addLayout(vLAdmin, 1, 2);
	gL->addLayout(hL, 2, 1, 1, 3);
	gL->addLayout(eventDetails, 3, 1, 1, 2);

	this->show();
}

void UserGUI::connectSlotsAndSignals()
{
	QObject::connect(this->eventList, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->getSelectedIndex();
		if (selectedIndex < 0)
			return;
		Event event = this->services->getDatabaseList()[selectedIndex];
		this->titleLineEdit->setText(QString::fromStdString(event.getTitle()));
		this->descriptionLineEdit->setText(QString::fromStdString(event.getDescription()));
		this->dateLineEdit->setText(QString::fromStdString(event.getEventDate().getDate()));
		this->hourLineEdit->setText(QString::fromStdString(event.getEventDate().getTime()));
		this->numberOfPeopleLineEdit->setText(QString::number(event.getNumberOfPeople()));
		this->linkLineEdit->setText(QString::fromStdString(event.getLink()));
		});

	QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::add);
	QObject::connect(this->removeButton, &QPushButton::clicked, this, &UserGUI::remove);
	QObject::connect(this->backButton, &QPushButton::clicked, this, &UserGUI::goBack);
	QObject::connect(this->openRepositoryButton, &QPushButton::clicked, this, &UserGUI::openRepo);
	QObject::connect(this->openEventButton, &QPushButton::clicked, this, &UserGUI::openLink);
}


void UserGUI::add()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0)
	{
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(QString::fromStdString("Select an event from the list first."));
		error->setWindowTitle("Invalid operation!");
		error->exec();
		return;
	}
	Event event = this->services->getDatabaseList()[selectedIndex];

	try {
		this->services->addElement(Event{ event.getTitle(), event.getDescription(), event.getEventDate(), event.getNumberOfPeople(), event.getLink() }, "user");
		this->populateList();
	}
	catch (inputException& exc) {
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(QString::fromStdString(exc.what()));
		error->setWindowTitle("Invalid input!");
		error->exec();
	}
	catch (addException& ae) {
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(QString::fromStdString(ae.what()));
		error->setWindowTitle("Error at adding event!");
		error->exec();
	}
}


void UserGUI::remove()
{
	int selectedIndex = this->getSelectedIndexUser();
	if (selectedIndex < 0)
	{
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(QString::fromStdString("Select an event from the list first."));
		error->setWindowTitle("Invalid operation!");
		error->exec();
		return;
	}
	Event event = this->services->getUserList()[selectedIndex];

	try {
		this->services->removeElement(event.getTitle(), event.getEventDate(), "user");
		this->populateList();
	}
	catch (inputException& exc) {
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(QString::fromStdString(exc.what()));
		error->setWindowTitle("Invalid input!");
		error->exec();
	}
	catch (updateRemoveException& ure) {
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(QString::fromStdString(ure.what()));
		error->setWindowTitle("Error at adding event!");
		error->exec();
	}
}


void UserGUI::goBack()
{
	GUI* gui = new GUI{ this->services };
	this->hide();
}


void UserGUI::openRepo()
{
	this->services->open();
}


void UserGUI::openLink()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0)
	{
		auto* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(QString::fromStdString("Select an event from the list first."));
		error->setWindowTitle("Invalid operation!");
		error->exec();
		return;
	}
	Event event = this->services->getDatabaseList()[selectedIndex];
	event.open();
}


void UserGUI::populateList()
{
	this->eventList->clear();
	vector<Event> list = this->services->getDatabaseList();

	for (Event& ev : list)
	{
		this->eventList->addItem(QString::fromStdString(ev.getTitle() + " " + ev.getEventDate().getDate() + " " + ev.getEventDate().getTime()));
	}

	this->userList->clear();
	vector<Event> user = this->services->getUserList();

	for (Event& ev : user)
	{
		this->userList->addItem(QString::fromStdString(ev.getTitle() + " " + ev.getEventDate().getDate() + " " + ev.getEventDate().getTime()));
	}
}


int UserGUI::getSelectedIndex() const
{
	QModelIndexList selectedIndexes = this->eventList->selectionModel()->selectedIndexes();
	if (selectedIndexes.empty()) {
		this->titleLineEdit->clear();
		this->descriptionLineEdit->clear();
		this->dateLineEdit->clear();
		this->hourLineEdit->clear();
		this->numberOfPeopleLineEdit->clear();
		this->linkLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

int UserGUI::getSelectedIndexUser() const
{
	QModelIndexList selectedIndexes = this->userList->selectionModel()->selectedIndexes();
	if (selectedIndexes.empty()) {
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}


UserGUI::~UserGUI() = default;