#include "Model.h"

Model::Model(Repository& repo, QObject *parent)
	: QAbstractTableModel(parent), repo(repo)
{}

QVariant Model::data(const QModelIndex & index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		int row = index.row();
		int col = index.column();

		Star star = this->repo.getStars()[row];

		if (col == 0)
			return QString::fromStdString(star.getName());
		if (col == 1)
			return QString::fromStdString(star.getConstelation());
		if (col == 2)
			return QString::number(star.getRA());
		if (col == 3)
			return QString::number(star.getDec());
		if (col == 4)
			return QString::number(star.getDiameter());

	}
	return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole and orientation == Qt::Horizontal)
	{
		if (section == 0)
			return "Name";
		if (section == 1)
			return "Constelation";
		if (section == 2)
			return "RA";
		if (section == 3)
			return "Dec";
		if (section == 4)
			return "Diameter";

	}
	return QVariant();
}

Qt::ItemFlags Model::flags(const QModelIndex& index) const
{
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void Model::addStar(Star st)
{
	this->beginResetModel();
	this->repo.addStar(st);
	this->endResetModel();
}

void Model::updateStar(string oldName, string name, int RA, int Dec, int diameter)
{
	this->beginResetModel();
	this->repo.updateStar(oldName, name, RA, Dec, diameter);
	this->endResetModel();
}
