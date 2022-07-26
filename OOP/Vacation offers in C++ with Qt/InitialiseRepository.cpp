#include "InitialiseRepository.h"

initialiseRepository::initialiseRepository()
{
    this->start();
}

void initialiseRepository::start()
{
    this->gL = new QVBoxLayout{};
    this->setLayout(gL);

    this->font = new QFont("System", 10, 63, false);

    this->label = new QLabel{};
    this->buttonCSV = new QPushButton{ "CSV Repository" };
    this->buttonHTML = new QPushButton{ "HTML Repository" };
    connectSignalsAndSlots();

    gL->addWidget(buttonCSV);
    gL->addWidget(buttonHTML);
    gL->addWidget(label);
    label->setText("<p style='text-align:center'><font color=black>Welcome to the Event Scheduleing App! <br> Select your repository!</font></p>");
    label->setFont(*font);

    this->buttonCSV->setStyleSheet("background-color: #f2f2f2; padding: 6px; font: bold 12px;");
    this->buttonHTML->setStyleSheet("background-color: #f2f2f2; padding: 6px; font: bold 12px;");
    this->setStyleSheet("background-color:#D9DBF1; padding: 30px;");

    this->show();
}

void initialiseRepository::connectSignalsAndSlots()
{
    QObject::connect(this->buttonCSV, &QPushButton::clicked, this, &initialiseRepository::initialiseRepositoryCSV);
    QObject::connect(this->buttonHTML, &QPushButton::clicked, this, &initialiseRepository::initialiseRepositoryHTML);
}


void initialiseRepository::initialiseRepositoryCSV()
{
    FileRepository* database = new FileRepository("database.txt");
    this->hide();
    FileRepository* userlist = new FileRepositoryCSV("userlist.txt", "data.csv");
    Services* services = new Services(database, userlist);
    GUI* gui = new GUI(services);
}


void initialiseRepository::initialiseRepositoryHTML()
{
    FileRepository* database = new FileRepository("database.txt");
    this->hide();
    FileRepository* userlist = new FileRepositoryHTML("userlist.txt", "data.html");
    Services* services = new Services(database, userlist);
    GUI* gui = new GUI(services);
}

initialiseRepository::~initialiseRepository() = default;
