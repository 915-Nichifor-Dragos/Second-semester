#pragma once

#include <QWidget>
#include "ui_UserGUI.h"

#include <QMessageBox>

#include "ServicesIssues.h"
#include "ServicesUsers.h"

class UserGUI : public QWidget, public Observer
{
	Q_OBJECT

public:
	UserGUI(User user, ServicesUsers* su, ServicesIssues* si, QWidget *parent = Q_NULLPTR);
	~UserGUI() { this->si->write(); };

private:

	Ui::UserGUI ui;
	ServicesUsers* su;
	ServicesIssues* si;
	User user;

	void update() { this->populate(); };

	int getSelectedIndex();
	void populate();

	void setProgrammer();
	void setTester();

public slots:

	void addIssue();
	void resolveIssue();
	void removeIssue();

};