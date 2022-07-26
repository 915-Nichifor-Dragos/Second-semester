#include "ScreenWriting.h"

#include <fstream>

ScreenWriting::ScreenWriting(TableModel* model, Writer writer, IdeaService* is, WriterService* ws, QWidget* parent)
    : QMainWindow(parent), ws(ws), is(is), writer(writer), model(model)
{
    ui.setupUi(this);

    this->ui.tableView->setModel(model);
    this->setUpWriter();

    this->show();
}


void ScreenWriting::setUpWriter()
{
    this->ui.titleLabel->setText(QString::fromStdString(writer.getName()));
    if (writer.getExpertise() != "Senior")
    {
        this->ui.reviseButton->setDisabled(true);
    }
}

void ScreenWriting::addIdea()
{
    string creator = this->writer.getName();
    string status = "proposed";

    vector<Idea> ideas = this->is->getList();

    string description = this->ui.descriptionLineEdit->text().toStdString();
    int act = this->ui.actLineEdit->text().toInt();
    
    if (act != 1 and act != 2 and act != 3)
    {
        return;
    }
    if (description.size() == 0)
        return;

    Idea id = Idea{ description, status, creator, act };
    // this->is->addElement(id);
    // is->notify();
    this->model->addElement(id);
}

void ScreenWriting::reviseIdea()
{
    QModelIndex index = this->ui.tableView->currentIndex();
    int row = index.row();
    int column = index.column();
    if (row < 0 or column < 0 or row > this->is->getList().size() or column > 4)
        return;

    Idea id = this->is->getList()[row];

    if (id.getStatus() == "Proposed")
    {
        // this->is->updateElement(row);
        this->model->updateElement(row);
    }

    // is->notify();
} 

void ScreenWriting::developIdea()
{
    vector<Idea> ideas = this->is->getList();

    this->suitable.clear();
    this->buttons.clear();
    this->texts.clear();

    for (auto element : ideas)
    {
        if (element.getCreator() == writer.getName())
            suitable.push_back(element);
    }

    QTextEdit* te;
    QPushButton* bt;

    for (auto element : suitable)
    {
        te = new QTextEdit{};
        te->setText(QString::fromStdString(element.getDescription()));
        this->texts.push_back(te);
        bt = new QPushButton{};
        bt->setText("Save");
        this->buttons.push_back(bt);
    }

    QWidget* textWindow = new QWidget{};
    QVBoxLayout* boxLayout = new QVBoxLayout{};
    textWindow->setLayout(boxLayout);

    vector <QHBoxLayout*> hLayouts;
    QHBoxLayout* horizontalLayout;

    for (int i = 0; i < this->texts.size(); i++)
    {
        horizontalLayout = new QHBoxLayout{};
        hLayouts.push_back(horizontalLayout);
        horizontalLayout->addWidget(this->texts[i]);
        horizontalLayout->addWidget(this->buttons[i]);
    }

    for (int i = 0; i < hLayouts.size(); i++)
    {
        boxLayout->addLayout(hLayouts[i]);
    }

    for (int i = 0; i < suitable.size(); i++)
    {
        QTextEdit* textEdit = this->texts[i];
        string file = this->writer.getName() + ".txt";
        IdeaService* isc = this->is;
        Idea id = this->suitable[i];
        QObject::connect(this->buttons[i], &QPushButton::clicked, this, [id, textEdit, file, isc]()
            {
                ofstream f{file};
                string description = textEdit->toPlainText().toStdString();
                f << description << "\n";
                f.close();
                isc->updateDescriptionIdeea(id, textEdit->toPlainText().toStdString());
            });
    }
    textWindow->show();
}

void ScreenWriting::savePlot()
{
    string total = "Act 1-\n";

    for (auto element : this->is->getList())
    {
        if (element.getStatus() == "Accepted" and element.getAct() == 1)
        {
            total = total + element.getDescription() + " (" + element.getCreator() + ")\n";
        }
    }

    total += "Act 2-\n";

    for (auto element : this->is->getList())
    {
        if (element.getStatus() == "Accepted" and element.getAct() == 2)
        {
            total = total + element.getDescription() + " (" + element.getCreator() + ") ";
        }
    }

    total += "Act 3-\n";

    for (auto element : this->is->getList())
    {
        if (element.getStatus() == "Accepted" and element.getAct() == 3)
        {
            total = total + element.getDescription() + " (" + element.getCreator() + ") ";
        }
    }

    ofstream out("Plot.txt");

    out << total;

}
