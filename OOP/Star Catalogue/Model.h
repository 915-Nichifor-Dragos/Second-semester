#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include "Repository.h"

class Model  : public QAbstractTableModel
{
	Q_OBJECT

public:
	Model(Repository& repo, QObject *parent = NULL);
	~Model() = default;

	int rowCount(const QModelIndex& index) const { return this->repo.getStars().size(); }
	int columnCount(const QModelIndex& index) const { return 5; }

	QVariant data(const QModelIndex& index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	Qt::ItemFlags flags(const QModelIndex& index) const;

	void addStar(Star st);

	void updateStar(string oldName, string name, int RA, int Dec, int diameter);

private:
	Repository& repo;

};
