#pragma once

#include "GUI.h"

#include "qwidget.h"
#include "qpushbutton.h"
#include "qfont.h"
#include "qlabel.h"
#include "qgridlayout.h"
#include <QListWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>

class UserGUI : public QWidget
{
	Q_OBJECT;

private:

	void start();
	void connectSlotsAndSignals();
	void add();
	void remove();
	void goBack();
	void openRepo();
	void openLink();

	void populateList();
	int getSelectedIndex() const;
	int getSelectedIndexUser() const;

	Services* services;

	QGridLayout* gL;
	QHBoxLayout* hL;
	QVBoxLayout* vLUser;
	QVBoxLayout* vLAdmin;
	QFormLayout* eventDetails;
	QListWidget* eventList;
	QListWidget* userList;
	QPushButton* addButton, * removeButton, * backButton, * openRepositoryButton, *openEventButton;
	QLineEdit* titleLineEdit, * descriptionLineEdit, * dateLineEdit, * hourLineEdit, * numberOfPeopleLineEdit, * linkLineEdit;
	QFont* font;
	QLabel* label;

public:

	UserGUI(Services* services);
	~UserGUI();

};