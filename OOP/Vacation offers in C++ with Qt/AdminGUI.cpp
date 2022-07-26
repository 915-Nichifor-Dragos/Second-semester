#include "AdminGUI.h"


AdminGUI::AdminGUI(Services* services): services(services)
{
	this->titleLineEdit = new QLineEdit{};
	this->descriptionLineEdit = new QLineEdit{};
	this->dateLineEdit = new QLineEdit{};
	this->hourLineEdit = new QLineEdit{};
	this->numberOfPeopleLineEdit = new QLineEdit{};
	this->linkLineEdit = new QLineEdit{};
	this->start();
}


void AdminGUI::start()
{
	this->eventList = new QListWidget{};
	this->gL = new QGridLayout{};
	this->vL = new QVBoxLayout{};
	this->setLayout(gL);
	this->eventDetails = new QFormLayout{};
	populateList();

	this->font = new QFont{ "System", 10, 63, false };
	this->label = new QLabel{};

	this->addButton = new QPushButton{ "Add an event" };
	this->removeButton = new QPushButton{ "Remove an event" };
	this->updateButton = new QPushButton{ "Update an event" };
	this->backButton = new QPushButton{ "Back" };

	this->eventDetails->addRow("Title:", titleLineEdit);
	this->eventDetails->addRow("Description:", descriptionLineEdit);
	this->eventDetails->addRow("Date:", dateLineEdit);
	this->eventDetails->addRow("Hour:", hourLineEdit);
	this->eventDetails->addRow("Number of people:", numberOfPeopleLineEdit);
	this->eventDetails->addRow("Link:", linkLineEdit);

	vL->addWidget(addButton);
	vL->addWidget(removeButton);
	vL->addWidget(updateButton);
	vL->addWidget(backButton);

	QLabel* note = new QLabel{};
	note->setText("*Please note that you can only  update the number of people going <br> to a event the link or the description.");

	gL->addWidget(this->label, 0, 0, 1, 3);
	gL->addWidget(this->eventList, 1, 2);
	gL->addLayout(vL, 1, 1);
	gL->addLayout(eventDetails, 2 ,1, 1, 2);
	gL->addWidget(note, 3, 1, 1, 3);

	connectSlotsAndSignals();

	this->label->setFont(*font);
	label->setText("<p style='text-align:center'><font color=#4D2D52>Admin menu</font></p>");

	this->addButton->setStyleSheet("background-color: #f2f2f2;");
	this->removeButton->setStyleSheet("background-color: #f2f2f2;");
	this->updateButton->setStyleSheet("background-color: #f2f2f2;");
	this->backButton->setStyleSheet("background-color: #f2f2f2;");

	this->titleLineEdit->setStyleSheet("background-color: white;");
	this->descriptionLineEdit->setStyleSheet("background-color: white;");
	this->dateLineEdit->setStyleSheet("background-color: white;");
	this->hourLineEdit->setStyleSheet("background-color: white;");
	this->numberOfPeopleLineEdit->setStyleSheet("background-color: white;");
	this->linkLineEdit->setStyleSheet("background-color: white;");

	this->eventList->setStyleSheet("background-color: white;");
	this->setStyleSheet("background-color:#D9DBF1;");

	this->show();
}


void AdminGUI::connectSlotsAndSignals()
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

	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::add);
	QObject::connect(this->removeButton, &QPushButton::clicked, this, &AdminGUI::remove);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::update);
	QObject::connect(this->backButton, &QPushButton::clicked, this, &AdminGUI::goBack);
}


int AdminGUI::getSelectedIndex() const {
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


void AdminGUI::add()
{
	std::string title = this->titleLineEdit->text().toStdString();
	std::string description = this->descriptionLineEdit->text().toStdString();
	std::string hour = this->hourLineEdit->text().toStdString();
	std::string date = this->dateLineEdit->text().toStdString();
	std::string numberOfPeopleStr = this->numberOfPeopleLineEdit->text().toStdString();
	std::string link = this->linkLineEdit->text().toStdString();

	int numberOfPeople;
	try {
		if (title.size() == 0 or description.size() == 0 or link.size() == 0)
			throw inputException("Size of title, description and link should be different than 0.");
		for (int i = 0; i < numberOfPeopleStr.size(); i++)
			if (std::isdigit(numberOfPeopleStr[i]) == false)
				throw(inputException("Number of people can not be a string."));

		numberOfPeople = stoi(numberOfPeopleStr);
		inputValidator::checkDate(date);
		inputValidator::checkHour(hour);
		date::DateTime datetime{date, hour};
		this->services->addElement(Event{ title, description, datetime, numberOfPeople, link }, "admin");
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


void AdminGUI::remove()
{
	std::string title = this->titleLineEdit->text().toStdString();
	std::string hour = this->hourLineEdit->text().toStdString();
	std::string date = this->dateLineEdit->text().toStdString();

	try {
		if (title.size() == 0)
			throw inputException("Size of title, description and link should be different than 0.");

		inputValidator::checkDate(date);
		inputValidator::checkHour(hour);
		date::DateTime datetime{date, hour};
		this->services->removeElement(title, datetime, "admin");
		try{
			this->services->removeElement(title, datetime, "user");
		}
		catch (updateRemoveException& ure)
		{

		}
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


void AdminGUI::update()
{
	std::string title = this->titleLineEdit->text().toStdString();
	std::string description = this->descriptionLineEdit->text().toStdString();
	std::string hour = this->hourLineEdit->text().toStdString();
	std::string date = this->dateLineEdit->text().toStdString();
	std::string numberOfPeopleStr = this->numberOfPeopleLineEdit->text().toStdString();
	std::string link = this->linkLineEdit->text().toStdString();

	int numberOfPeople;
	try {
		if (title.size() == 0 or description.size() == 0 or link.size() == 0)
			throw inputException("Size of title, description and link should be different than 0.");
		for (int i = 0; i < numberOfPeopleStr.size(); i++)
			if (std::isdigit(numberOfPeopleStr[i]) == false)
				throw(inputException("Number of people can not be a string."));

		numberOfPeople = stoi(numberOfPeopleStr);
		inputValidator::checkDate(date);
		inputValidator::checkHour(hour);
		date::DateTime datetime{ date, hour };
		this->services->updateElement(title, description, datetime, numberOfPeople, link, "admin");
		try {
			this->services->updateElement(title, description, datetime, numberOfPeople, link, "user");
		}
		catch (updateRemoveException& ure)
		{

		}
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


void AdminGUI::goBack()
{
	GUI* gui = new GUI{this->services};
	this->hide();
}


void AdminGUI::populateList()
{
	this->eventList->clear();
	vector<Event> list = this->services->getDatabaseList();

	for (Event& ev : list)
	{
		this->eventList->addItem(QString::fromStdString(ev.getTitle() + " " + ev.getEventDate().getDate() + " " + ev.getEventDate().getTime()));
	}
}


AdminGUI::~AdminGUI() = default;
