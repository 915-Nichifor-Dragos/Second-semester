#include "StarCatalogue.h"
#include <QtWidgets/QApplication>

#include "Service.h"
#include "Model.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Repository repo("stars.txt", "astronomers.txt");

    Service* serv = new Service(repo);
    Model* mdl = new Model(repo);

    vector<StarCatalogue*> GUIs;
    StarCatalogue* stc;

    for (auto element : repo.getAstronomers())
    {
        stc = new StarCatalogue(element, serv, mdl);
    }

    a.exec();

    serv->write();

    return 0;
}
