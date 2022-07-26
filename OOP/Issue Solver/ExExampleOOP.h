#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ExExampleOOP.h"

class ExExampleOOP : public QMainWindow
{
    Q_OBJECT

public:
    ExExampleOOP(QWidget *parent = Q_NULLPTR);

private:
    Ui::ExExampleOOPClass ui;
};
