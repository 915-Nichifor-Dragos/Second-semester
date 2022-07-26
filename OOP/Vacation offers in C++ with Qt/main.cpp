#include "EventApplication.h"
#include "Repository.h"
#include "FileRepository.h"
#include "FileRepositoryCSV.h"
#include "FileRepositoryHTML.h"
#include "Services.h"
#include "InitialiseRepository.h"

#include <qgridlayout.h>
#include <QPushButton>
#include <QtWidgets/QApplication>
#include <qlabel.h>
#include <qfont.h>
#include <qobject.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initialiseRepository* repos = new initialiseRepository();

    return a.exec();
}