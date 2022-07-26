#include "Exam.h"
#include <QtWidgets/QApplication>

#include "Repository.h"
#include "Service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Repository repo("user.txt", "post.txt", "topic.txt");
    Service* serv = new Service{ repo };

    vector<Exam*> GUIs;

    for (auto element : serv->getUsers())
    {
        Exam* v = new Exam(element, serv);
        serv->addObserver(v);
        GUIs.push_back(v);
    }

    a.exec();

    serv->write();

    return 0;
}
