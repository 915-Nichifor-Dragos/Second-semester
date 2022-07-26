#pragma once

#include <QObject>

#include "IdeaRepository.h"

#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
	Q_OBJECT

private:

	IdeaRepository& repo;

public:
	TableModel(IdeaRepository& repo, QObject *parent = NULL);
	~TableModel();

	int rowCount(const QModelIndex& index) const { return this->repo.getList().size(); };
	int columnCount(const QModelIndex& index) const { return 4; };

	QVariant data(const QModelIndex& index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	void addElement(Idea id);
	void updateElement(int value);
};
