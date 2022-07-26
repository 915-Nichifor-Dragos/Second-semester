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

class AdminGUI : public QWidget
{
	Q_OBJECT;

private:

	void start();
	void connectSlotsAndSignals();
	void add();
	void remove();
	void update();
	void goBack();

	void populateList();
	int getSelectedIndex() const;

	Services* services;

	QGridLayout* gL;
	QVBoxLayout* vL;
	QFormLayout* eventDetails;
	QListWidget* eventList;
	QPushButton* addButton, *removeButton, *updateButton, *backButton;
	QLineEdit* titleLineEdit, * descriptionLineEdit, * dateLineEdit, * hourLineEdit, * numberOfPeopleLineEdit, * linkLineEdit;
	QFont* font;
	QLabel* label;

public:

	AdminGUI(Services* services);
	~AdminGUI();

};