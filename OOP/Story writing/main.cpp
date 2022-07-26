#include "ScreenWriting.h"
#include <QtWidgets/QApplication>

#include "IdeaRepository.h"
#include "WriterRepository.h"
#include "IdeaService.h"
#include "WriterService.h"
#include "Tests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IdeaRepository ir{ "idea.txt" };
    WriterRepository wr{ "writer.txt" };

    ir.sort();

    IdeaService* is = new IdeaService{ ir };
    WriterService* ws = new WriterService{ wr };

    vector <ScreenWriting*> GUIS;
    ScreenWriting* w;

    testAdd();
    testUpdate();

    TableModel* model = new TableModel{ is->getRepo() };

    for (auto element : ws->getList())
    {
        w = new ScreenWriting{ model, element, is, ws };
        is->addObserver(w);
        GUIS.push_back(w);
    }

    return a.exec();
}
