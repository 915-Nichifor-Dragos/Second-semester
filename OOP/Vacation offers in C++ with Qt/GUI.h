#pragma once

#include "Services.h"
#include "AdminGUI.h"
#include "UserGUI.h"

#include <qwidget.h>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qlabel.h>

class GUI : public QWidget
{
	Q_OBJECT;

private:

	void start();
	void connectSignalsAndSlots();
	void goToUser();
	void goToAdmin();

	Services* services;

	QPushButton* adminGUI, * userGUI;
	QGridLayout* gL;
	QLabel* label;
	QFont* font;

public:

	GUI(Services* services);
	~GUI();

};