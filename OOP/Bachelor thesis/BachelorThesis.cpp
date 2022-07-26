#include "BachelorThesis.h"

#include <fstream>
#include <algorithm>

BachelorThesis::BachelorThesis(Teacher th, Service* service, QWidget *parent)
    : QMainWindow(parent), service(service), th(th)
{
    ui.setupUi(this);

    this->setUpTeacher();

    this->show();
}

void BachelorThesis::setUpTeacher()
{
    window = new QWidget{};
    this->ui.titleLabel->setText(QString::fromStdString("Teacher: " + this->th.getName()));
    this->populate();
}

int BachelorThesis::getSelectedIndexAll()
{
    QModelIndexList selectedIndexes = this->ui.allStudentsList->selectionModel()->selectedIndexes();

    if (selectedIndexes.size() == 0)
        return -1;

    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

int BachelorThesis::getSelectedIndexCoordinate()
{
    QModelIndexList selectedIndexes = this->ui.coordinatedList->selectionModel()->selectedIndexes();

    if (selectedIndexes.size() == 0)
        return -1;

    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void BachelorThesis::updateStud()
{
    string id = this->lineEdits[0]->text().toStdString();
    string newEmail = this->lineEdits[2]->text().toStdString();
    string newTitle = this->lineEdits[4]->text().toStdString();

    this->service->updateEmailTitle(id, newEmail, newTitle);

    this->service->notify();
    window->hide();
}

void BachelorThesis::addCoordinate()
{
    int index = this->getSelectedIndexAll();

    if (index == -1)
        return;

    string id = this->vectorSearch[index].getId();

    if (this->vectorSearch[index].getCoordinator() != "")
        return;

    this->service->updateStudent(id, this->th.getName());
    this->service->notify();
}

void BachelorThesis::approveThesis()
{
    int index = this->getSelectedIndexCoordinate();

    if (index == -1)
        return;

    string title = this->vectorCoordinated[index].getTitle();
    if (title == "No title")
        return;

    ofstream out(this->vectorCoordinated[index].getName() + ".txt");
    out << th.getName() + " approves the thesis " + this->vectorCoordinated[index].getTitle() + " authored by " + this->vectorCoordinated[index].getName();
    this->ui.coordinatedList->item(index)->setBackground(Qt::green);
}

void BachelorThesis::populate()
{
    this->ui.coordinatedList->clear();
    this->vectorCoordinated.clear();

    vector<Student> list = this->service->getStudents();

    std::sort(list.begin(), list.end(), [](Student s1, Student s2) {return s1.getYear() > s2.getYear(); });

    for (auto element : list)
    {
        if (element.getCoordinator() == this->th.getName())
        {
            this->vectorCoordinated.push_back(element);
            this->ui.coordinatedList->addItem(QString::fromStdString(element.getName() + " " + to_string(element.getYear()) + " " + element.getTitle() + " " + element.getCoordinator()));
        }
    }
}

void BachelorThesis::changeSearch()
{
    string data = this->ui.searchLineEdit->text().toStdString();

    this->ui.allStudentsList->clear();
    vectorSearch.clear();

    for (auto element : this->service->getStudents())
    {
        if (element.getName().find(data) != std::string::npos)
        {
            vectorSearch.push_back(element);
            this->ui.allStudentsList->addItem(QString::fromStdString(element.getId() + " " + element.getName() + " " + to_string(element.getYear()) + " " + element.getTitle() + " " + element.getCoordinator()));
        }
    }
}

void BachelorThesis::updateStudent()
{
    if (window->isVisible() == true)
        this->window->hide();

    window = new QWidget{};
    this->lineEdits.clear();
    this->labels.clear();
    this->horizontalLayouts.clear();

    int index = this->getSelectedIndexCoordinate();

    if (index == -1)
        return;

    QLabel* l1 = new QLabel{"Id: "};
    QLabel* l2 = new QLabel{"Name: "};
    QLabel* l3 = new QLabel{"Email: "};
    QLabel* l4 = new QLabel{"Year: "};
    QLabel* l5 = new QLabel{"Title: "};
    QLabel* l6 = new QLabel{"Coordinator: "};

    QLineEdit* le1 = new QLineEdit{};
    QLineEdit* le2 = new QLineEdit{};
    QLineEdit* le3 = new QLineEdit{};
    QLineEdit* le4 = new QLineEdit{};
    QLineEdit* le5 = new QLineEdit{};
    QLineEdit* le6 = new QLineEdit{};

    le1->setDisabled(true);
    le2->setDisabled(true);
    le4->setDisabled(true);
    le6->setDisabled(true);

    this->lineEdits.push_back(le1);
    this->lineEdits.push_back(le2);
    this->lineEdits.push_back(le3);
    this->lineEdits.push_back(le4);
    this->lineEdits.push_back(le5);
    this->lineEdits.push_back(le6);

    this->labels.push_back(l1);
    this->labels.push_back(l2);
    this->labels.push_back(l3);
    this->labels.push_back(l4);
    this->labels.push_back(l5);
    this->labels.push_back(l6);

    QHBoxLayout* lay1 = new QHBoxLayout{};
    QHBoxLayout* lay2 = new QHBoxLayout{};
    QHBoxLayout* lay3 = new QHBoxLayout{};
    QHBoxLayout* lay4 = new QHBoxLayout{};
    QHBoxLayout* lay5 = new QHBoxLayout{};
    QHBoxLayout* lay6 = new QHBoxLayout{};

    lay1->addWidget(l1);
    lay1->addWidget(le1);

    lay2->addWidget(l2);
    lay2->addWidget(le2);

    lay3->addWidget(l3);
    lay3->addWidget(le3);

    lay4->addWidget(l4);
    lay4->addWidget(le4);

    lay5->addWidget(l5);
    lay5->addWidget(le5);

    lay6->addWidget(l6);
    lay6->addWidget(le6);

    this->horizontalLayouts.push_back(lay1);
    this->horizontalLayouts.push_back(lay2);
    this->horizontalLayouts.push_back(lay3);
    this->horizontalLayouts.push_back(lay4);
    this->horizontalLayouts.push_back(lay5);
    this->horizontalLayouts.push_back(lay6);

    this->layout = new QVBoxLayout{};
    window->setLayout(layout);

    this->button = new QPushButton{ "Update" };

    this->layout->addLayout(lay1);
    this->layout->addLayout(lay2);
    this->layout->addLayout(lay3);
    this->layout->addLayout(lay4);
    this->layout->addLayout(lay5);
    this->layout->addLayout(lay6);
    this->layout->addWidget(button);

    Student stud = this->vectorCoordinated[index];

    le1->setText(QString::fromStdString(stud.getId()));
    le2->setText(QString::fromStdString(stud.getName()));
    le3->setText(QString::fromStdString(stud.getEmail()));
    le4->setText(QString::fromStdString(to_string(stud.getYear())));
    le5->setText(QString::fromStdString(stud.getTitle()));
    le6->setText(QString::fromStdString(stud.getCoordinator()));

    QObject::connect(this->button, &QPushButton::clicked, this, &BachelorThesis::updateStud);

    window->show();
}