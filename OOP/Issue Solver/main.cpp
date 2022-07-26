#include "ExExampleOOP.h"
#include <QtWidgets/QApplication>

#include "RepositoryIssues.h"
#include "RepositoryUsers.h"
#include "ServicesIssues.h"
#include "ServicesUsers.h"
#include "UserGUI.h"
#include "Tests.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RepositoryIssues ri = RepositoryIssues("issues.txt");
    RepositoryUsers ru = RepositoryUsers("users.txt");
    ServicesIssues* si = new ServicesIssues(ri);
    ServicesUsers* su = new ServicesUsers(ru);

    vector<UserGUI*> users;
    UserGUI* u;

    testadd();
    testupdate();

    for (auto element : su->getList())
    {
        u = new UserGUI(element, su, si);
        si->addObserver(u);
        users.push_back(u);
    }

    a.exec();

    for (auto element : users)
        delete(element);

    delete(si);
    delete(su);

    return 0;
}
