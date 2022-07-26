#include "StarCatalogue.h"

StarCatalogue::StarCatalogue(Astronomer astronomer, Service* serv, Model* mdl, QWidget* parent)
    : QMainWindow(parent), serv(serv), mdl(mdl), astronomer(astronomer)
{
    ui.setupUi(this);

    this->ui.label->setText(QString::fromStdString(this->astronomer.getName()));
    this->ui.tableView->setModel(mdl);

    for (auto element : this->serv->getStars())
        if (element.getConstelation() == astronomer.getConstelation())
            studied.addStar(element);
    
    modelStudied = new Model(studied);

    this->ui.updateButton->setDisabled(true);

    this->show();
}

void StarCatalogue::addStar()
{
    string name = this->ui.nameLineEdit->text().toStdString();
    string constelation = this->astronomer.getConstelation();
    int RA = this->ui.RALineEdit->text().toInt();
    int Dec = this->ui.decLineEdit->text().toInt();
    int diameter = this->ui.diameterLineEdit->text().toInt();

    if (name.size() == 0)
        return;

    for (auto element : this->serv->getStars())
    {
        if (element.getName() == name)
            return;
    }

    Star st = Star(name, constelation, RA, Dec, diameter);

    this->serv->addStar(st);
    this->studied.addStar(st);

    mdl->addStar(st);
    modelStudied->addStar(st);

}

void StarCatalogue::updateStar()
{
    QModelIndexList selectedIndexes = this->ui.tableView->selectionModel()->selectedIndexes();
    int selectedIndex = selectedIndexes.at(0).row();

    string oldName = this->studied.getStars()[selectedIndex].getName();

    string name = this->ui.nameLineEdit->text().toStdString();
    int RA = this->ui.RALineEdit->text().toInt();
    int Dec = this->ui.decLineEdit->text().toInt();
    int diameter = this->ui.diameterLineEdit->text().toInt();

    if (name.size() == 0)
        return;

    for (auto element : this->serv->getStars())
    {
        if (element.getName() == name)
            return;
    }

    if (diameter < 10)
        return;

    this->serv->updateStar(oldName, name, RA, Dec, diameter);
    this->studied.updateStar(oldName, name, RA, Dec, diameter);

    this->mdl->updateStar(oldName, name, RA, Dec, diameter);
    this->modelStudied->updateStar(oldName, name, RA, Dec, diameter);

}

void StarCatalogue::checkBoxChanged()
{
    if (this->ui.checkBox->isChecked() == true)
    {
        this->ui.tableView->setModel(modelStudied);
        this->ui.updateButton->setDisabled(false);
    }
    else
    {
        this->ui.tableView->setModel(mdl);
        this->ui.updateButton->setDisabled(true);
    }
}
