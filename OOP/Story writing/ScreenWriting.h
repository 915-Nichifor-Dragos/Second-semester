#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ScreenWriting.h"
#include <QTextEdit>

#include "IdeaService.h"
#include "WriterService.h"
#include "TableModel.h"

class ScreenWriting : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    ScreenWriting(TableModel* model, Writer writer, IdeaService* is, WriterService* ws, QWidget *parent = Q_NULLPTR);

private:
    Ui::ScreenWritingClass ui;

    vector <QTextEdit*> texts;
    vector <QPushButton*> buttons;
    vector <Idea> suitable;

    Writer writer;
    IdeaService* is;
    WriterService* ws;
    TableModel* model;

    void update(){ delete model; model = new TableModel{ this->is->getRepo() }; this->ui.tableView->setModel(model); };
    void setUpWriter();

public slots:

    void addIdea();
    void reviseIdea();
    void developIdea();
    void savePlot();

};
