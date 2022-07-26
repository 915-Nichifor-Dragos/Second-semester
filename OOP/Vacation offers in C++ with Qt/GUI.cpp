#include "GUI.h"


GUI::GUI(Services* services) : services(services)
{
	this->start();
}

void GUI::start()
{
	this->gL = new QGridLayout{};
	this->setLayout(gL);

	this->font = new QFont{ "System", 10, 63, false };

	this->label = new QLabel{};
	this->userGUI = new QPushButton{ "User" };
	this->adminGUI = new QPushButton{ "Admin" };

	gL->addWidget(this->label, 0, 0, 1, 2);
	gL->addWidget(this->adminGUI, 1, 0);
	gL->addWidget(this->userGUI, 1, 1);
	this->label->setFont(*font);
	label->setText("<p style='text-align:center'><font color=#4D2D52>The application will run as</font></p>");
	
	this->adminGUI->setStyleSheet("background-color: #f2f2f2; padding: 6px; font: bold 12px;");
	this->userGUI->setStyleSheet("background-color: #f2f2f2; padding: 6px; font: bold 12px;");
	this->setStyleSheet("background-color:#D9DBF1; padding: 20px;");

	this->connectSignalsAndSlots();

	this->show();
}

void GUI::connectSignalsAndSlots()
{
	QObject::connect(this->userGUI, &QPushButton::clicked, this, &GUI::goToUser);
	QObject::connect(this->adminGUI, &QPushButton::clicked, this, &GUI::goToAdmin);
}

void GUI::goToUser()
{
	UserGUI* usr = new UserGUI(this->services);
	this->hide();
}

void GUI::goToAdmin()
{
	AdminGUI* adm = new AdminGUI(this->services);
	this->hide();
}

GUI::~GUI() = default;
