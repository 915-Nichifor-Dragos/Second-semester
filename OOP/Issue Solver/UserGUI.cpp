#include "UserGUI.h"

UserGUI::UserGUI(User user, ServicesUsers* su, ServicesIssues* si, QWidget *parent)
	: QWidget(parent), su(su), si(si), user(user)
{
	ui.setupUi(this);

	if (user.getType() == "programmer")
		setProgrammer();
	if (user.getType() == "tester")
		setTester();

	populate();

	this->show();
}

int UserGUI::getSelectedIndex()
{
	QModelIndexList selectedIndexes = this->ui.issuesListWidget->selectionModel()->selectedIndexes();

	if (selectedIndexes.isEmpty())
		return -1;

	int index = selectedIndexes.at(0).row();
	return index;
}

void UserGUI::populate()
{
	this->ui.issuesListWidget->clear();

	vector<Issue> issues = this->si->getList();
	/*std::sort(issues.begin(), issues.end(), [](Issue i1, Issue i2) {
		if (i1.getStatus() == i2.getStatus())
			return i1.getDescription() > i2.getDescription();
		if (i1.getStatus() == "open")
			return true;
		return false;
		});*/

	for (auto element : issues)
	{
		QString itm = QString::fromStdString(element.getDescription() + " | " + element.getStatus() + " | " + element.getReporter() + " | " + element.getSolver());
		this->ui.issuesListWidget->addItem(itm);
	}

}

void UserGUI::setProgrammer()
{
	this->ui.titleLabel->setText("Programmer: " + QString::fromStdString(user.getName()));
	this->ui.addButton->setDisabled(true);
}

void UserGUI::setTester()
{
	this->ui.titleLabel->setText("Tester: " + QString::fromStdString(user.getName()));
	this->ui.resolveButton->setDisabled(true);
}

void UserGUI::resolveIssue()
{
	int index = this->getSelectedIndex();
	if (index == -1)
		return;

	vector<Issue> issues = this->si->getList();
	/*std::sort(issues.begin(), issues.end(), [](Issue i1, Issue i2) {
		if (i1.getStatus() == i2.getStatus())
			return i1.getDescription() > i2.getDescription();
		if (i1.getStatus() == "open")
			return true;
		return false;
		});*/

	if (issues[index].getStatus() != "open")
	{
		QMessageBox::critical(this, "Error at trying to solve the issue!", "This issue has already been solved!");
		return;
	}
	this->si->updateStatus(index, user.getName());
	this->si->notify();
}

void UserGUI::removeIssue()
{
	int index = this->getSelectedIndex();
	if (index == -1)
		return;

	vector<Issue> issues = this->si->getList();
	/*std::sort(issues.begin(), issues.end(), [](Issue i1, Issue i2) {
		if (i1.getStatus() == i2.getStatus())
			return i1.getDescription() > i2.getDescription();
		if (i1.getStatus() == "open")
			return true;
		return false;
		});*/

	if (issues[index].getStatus() != "closed")
	{
		QMessageBox::critical(this, "Error at removing issue!", "This issue has not been solved!");
		return;
	}
	this->si->removeElement(index);
	this->si->notify();

}

void UserGUI::addIssue()
{
	string description = this->ui.descriptionLineEdit->text().toStdString();
	string name = this->user.getName();

	for (auto element : this->si->getList())
	{
		if (element.getDescription() == description)
		{
			QMessageBox::critical(this, "Error at adding a new issue!", "This issue has already been reported!");
			this->ui.descriptionLineEdit->clear();
			return;
		}
	}

	Issue i(description, "open", name, "");

	this->si->addElement(i);
	this->ui.descriptionLineEdit->clear();
	si->notify();
}
