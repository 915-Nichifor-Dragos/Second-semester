#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_StarCatalogue.h"

#include "Service.h"
#include "Model.h"

class StarCatalogue : public QMainWindow
{
    Q_OBJECT

public:
    StarCatalogue(Astronomer astronomer, Service* serv, Model* mdl, QWidget* parent = nullptr);
    ~StarCatalogue() = default;

private:
    Ui::StarCatalogueClass ui;

    Repository studied;

    Astronomer astronomer;
    Model* mdl;
    Service* serv;
    Model* modelStudied;

public slots:
    void checkBoxChanged();
    void addStar();
    void updateStar();

};
