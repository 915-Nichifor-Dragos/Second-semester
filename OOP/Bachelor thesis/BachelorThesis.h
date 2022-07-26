#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BachelorThesis.h"
#include "Observable.h"

#include "Service.h"
#include "Student.h"

class BachelorThesis : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    BachelorThesis(Teacher th, Service* service, QWidget *parent = nullptr);
    ~BachelorThesis() = default;

private:
    Ui::BachelorThesisClass ui;
    Service* service;
    Teacher th;

    vector<Student> vectorSearch;
    vector<Student> vectorCoordinated;

    void populate();
    void setUpTeacher();

    vector<QLineEdit*> lineEdits;
    vector<QLabel*> labels;
    vector<QHBoxLayout*> horizontalLayouts;
    QVBoxLayout* layout;
    QPushButton* button;
    QWidget* window;

    int getSelectedIndexAll();
    int getSelectedIndexCoordinate();

    void update() { this->populate(); this->changeSearch(); }

    void updateStud();

public slots:
    void changeSearch();
    void addCoordinate();
    void approveThesis();
    void updateStudent();
};
