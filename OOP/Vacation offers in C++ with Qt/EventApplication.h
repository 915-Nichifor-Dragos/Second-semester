#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EventApplication.h"

class EventApplication : public QMainWindow
{
    Q_OBJECT

public:
    EventApplication(QWidget *parent = Q_NULLPTR);

private:
    Ui::EventApplicationClass ui;
};
