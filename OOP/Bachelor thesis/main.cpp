#include "BachelorThesis.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    Repository repo{ "Students.txt", "Teachers.txt" };
    Service* serv = new Service{repo};

    vector<BachelorThesis*> GUIs;

    for (int i = 0 ; i < serv->getTeachers().size(); i ++)
    {
        BachelorThesis* bt = new BachelorThesis{ serv->getTeachers()[i], serv};
        GUIs.push_back(bt);
        serv->addObserver(bt);
    }

    a.exec();

    serv->write();

    return 0;
}
