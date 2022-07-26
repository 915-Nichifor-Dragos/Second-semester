#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Exam.h"

#include "Observer.h"

#include "Service.h"
#include "User.h"

class Exam : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    Exam(User user, Service* serv, QWidget *parent = nullptr);
    ~Exam();

    void start();
    void update() { this->start(); }

    int getSelectedIndex();
    int getSelectedIndexSubs();

private:
    Ui::ExamClass ui;
    Service* serv;
    User user;
    vector<string> topics;
    vector<Post> feed;
    vector<Post> posts;
    vector<string> changed;

public slots:
    void addPost();
    void updatePost();
    void lineChanged();
    void addSubs();

};
