#pragma once

#include <QAbstractTableModel>
#include <QTableView>

#include "libxpeccy/tape.h"

class xTapeCatModel : public QAbstractTableModel {
	Q_OBJECT
	public:
		xTapeCatModel(QObject* p = NULL);
		void fill(Tape*);
		int rowCount(const QModelIndex& = QModelIndex()) const;
		int columnCount(const QModelIndex& = QModelIndex()) const;
		void update();
		QModelIndex index(int row, int col, const QModelIndex &parent = QModelIndex()) const;
	private:
		int rcnt;
		int rcur;
		TapeBlockInfo* inf;
		QVariant data(const QModelIndex&, int) const;
		QVariant headerData(int, Qt::Orientation, int) const;
};

class xTapeCatTable : public QTableView {
	Q_OBJECT
	public:
		xTapeCatTable(QWidget* = NULL);
		void fill(Tape*);
		xTapeCatModel* model;
	private:
};
