#pragma once

#include "GUI.h"
#include "Repository.h"
#include "FileRepository.h"
#include "FileRepositoryCSV.h"
#include "FileRepositoryHTML.h"
#include "Services.h"

#include <qwidget.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qstyle.h>

class initialiseRepository : public QWidget
{
	Q_OBJECT;
	
private:

	void start();
	void connectSignalsAndSlots();
	void initialiseRepositoryCSV();
	void initialiseRepositoryHTML();

	QPushButton* buttonCSV, *buttonHTML;
	QVBoxLayout* gL;
	QFont* font;
	QLabel* label;

public:

	initialiseRepository();
	~initialiseRepository();
};