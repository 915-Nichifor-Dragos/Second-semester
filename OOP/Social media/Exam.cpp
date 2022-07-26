#include "Exam.h"

#include <algorithm>

Exam::Exam(User user, Service* serv, QWidget *parent)
    : QMainWindow(parent), user(user), serv(serv)
{
    ui.setupUi(this);

    ui.label_4->setText(QString::fromStdString(this->user.getName()));

    this->start();

    this->show();
}

Exam::~Exam()
{}

void Exam::start()
{
    this->posts.clear();
    this->feed.clear();
    this->topics.clear();

    for (auto element : this->serv->getTopics())
    {
        string topic = element.getTopic();
        vector<string> users = element.getUsers();

        for (auto us : users)
        {
            if (us == this->user.getName())
                this->topics.push_back(topic);
        }

    }

    for (auto element : this->serv->getPosts())
    {
        string mention = "@" + this->user.getName();
        if (element.getText().find(mention) != std::string::npos)
            this->feed.push_back(element);
        else
        {
            for (auto tp : this->topics)
            {
                string tpc = "#" + tp;
                if (element.getText().find(tpc) != std::string::npos)
                    this->feed.push_back(element);
            }
        }
    }

    for (auto element : this->serv->getPosts())
    {
        if (element.getUser() == this->user.getName())
            this->posts.push_back(element);
    }

    this->ui.postList->clear();
    this->ui.feedList->clear();
    this->ui.subscriptionList->clear();

    std::sort(this->posts.begin(), this->posts.end(), [](Post p1, Post p2) {if (p1.getDate() == p2.getDate()) return p1.getTime() > p2.getDate(); return p1.getTime() > p2.getDate(); });
    std::sort(this->feed.begin(), this->feed.end(), [](Post p1, Post p2) {if (p1.getDate() == p2.getDate()) return p1.getTime() > p2.getDate(); return p1.getTime() > p2.getDate(); });

    for (auto element : this->posts)
    {
        this->ui.postList->addItem(QString::fromStdString(element.getDate() + ", " + element.getTime() + ": " + element.getText()));
    }

    for (auto element : this->topics)
    {
        this->ui.subscriptionList->addItem(QString::fromStdString(element));
    }

    for (auto element : this->feed)
    {
        this->ui.feedList->addItem(QString::fromStdString(element.getDate() + ", " + element.getTime() + ": " + element.getText() + ", " + element.getUser()));
        //string mention = "@" + this->user.getName();
        //if (element.getText().find(mention) != std::string::npos)
            //this->ui.feedList->item(this->ui.feedList->currentRow())->setForeground(Qt::blue);
    }
}

int Exam::getSelectedIndex()
{
    QModelIndexList selectedIndexes = this->ui.postList->selectionModel()->selectedIndexes();

    if (selectedIndexes.size() == 0)
        return -1;

    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

int Exam::getSelectedIndexSubs()
{
    QModelIndexList selectedIndexes = this->ui.subscriptionList->selectionModel()->selectedIndexes();

    if (selectedIndexes.size() == 0)
        return -1;

    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void Exam::updatePost()
{
    int index = this->getSelectedIndex();
    if (index == -1)
        return;

    string text = ui.textLineEdit->text().toStdString();

    string id = this->posts[index].getId();

    this->serv->updatePost(id, text);
    this->serv->notify();

}

void Exam::lineChanged()
{
    changed.clear();
    this->ui.subscriptionList->clear();
    string line = this->ui.lineEdit->text().toStdString();
    for (auto element: this->serv->getTopics())
        if (element.getTopic().find(line) != std::string::npos)
        {
            changed.push_back(element.getTopic());
            this->ui.subscriptionList->addItem(QString::fromStdString(element.getTopic()));
        }
}

void Exam::addSubs()
{
    int index = this->getSelectedIndexSubs();

    if (index == -1)
        return;

    string sub = this->changed[index];
    this->serv->addUserTopic(sub, this->user.getName());
    this->start();
}

void Exam::addPost()
{
    string text = ui.textLineEdit->text().toStdString();
    string date = ui.dateLineEdit->text().toStdString();
    string time = ui.timeLineEdit->text().toStdString();

    if (text.size() < 3)
        return;

    this->serv->addPost(this->user.getName(), text, date, time);
    this->serv->notify();
}

