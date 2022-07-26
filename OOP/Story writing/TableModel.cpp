#include "TableModel.h"

TableModel::TableModel(IdeaRepository& repo, QObject *parent)
	: QAbstractTableModel(parent), repo(repo)
{
}

TableModel::~TableModel()
{
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	if (role == Qt::EditRole or role == Qt::DisplayRole)
	{
		Idea id = this->repo.getList()[row];

		if (column == 0)
			return QString::fromStdString(id.getDescription());
		if (column == 1)
			return QString::fromStdString(id.getStatus());
		if (column == 2)
			return QString::fromStdString(id.getCreator());
		if (column == 3)
			return QString::number(id.getAct());
	}

	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole and orientation == Qt::Horizontal)
	{
		if (section == 0)
			return "Description";
		if (section == 1)
			return "Status";
		if (section == 2)
			return "Creator";
		if (section == 3)
			return "Act";
	}

	return QVariant();
}

void TableModel::addElement(Idea id)
{
	this->beginResetModel();
	this->repo.addElement(id);
	this->endResetModel();
}

void TableModel::updateElement(int value)
{
	this->beginResetModel();
	this->repo.updateElement(value);
	this->endResetModel();
}

