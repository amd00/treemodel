#ifndef _TREEMODEL_H_
#define _TREEMODEL_H_

#include <QAbstractItemModel>

#include "treeitem.h"

class TreeModel : public QAbstractItemModel
{
	Q_OBJECT

private:
	TreeItem *m_root;

public:
	TreeModel();
	virtual ~TreeModel();

	void setHeader(const QStringList &_headers);
	QModelIndex addItem(const QModelIndex &_par, const ItemData &_data);
	void editItem(const QModelIndex &_ind, qint32 _role, const QVariant &_val);
	void delItem(const QModelIndex &_ind);
	QVariant userData(const QModelIndex &_ind) const;
	void setUserData(const QModelIndex &_ind, const QVariant &_data);
	void setFlags(const QModelIndex &_ind, Qt::ItemFlags _flags);
	void setFlags(qint32 _column, Qt::ItemFlags _flags);
	Qt::ItemFlags flags(const QModelIndex &_ind) const;
	Qt::ItemFlags flags(qint32 _column) const;
	void clear();

protected:
	virtual bool setData(const QModelIndex &_ind, const QVariant &_val, int _role = Qt::EditRole);
	virtual QVariant data(const QModelIndex &_ind, int _role) const;
	virtual QVariant headerData(qint32 _section, Qt::Orientation _orient, qint32 _role = Qt::DisplayRole) const;
	bool setHeaderData(int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole);

	virtual qint32 rowCount(const QModelIndex &_par = QModelIndex()) const;
	virtual qint32 columnCount(const QModelIndex &_ind) const;

	QModelIndex index(qint32 _row, qint32 _column, const QModelIndex &_par) const;
	QModelIndex parent(const QModelIndex &_ind) const;

	bool insertRows (qint32 _row, qint32 _count, const QModelIndex &_par = QModelIndex());
	bool removeRows (qint32 _row, qint32 _count, const QModelIndex &_par = QModelIndex());

	TreeItem *item(const QModelIndex &_ind) const;
	void swapChildren(qint32 i, qint32 j, const QModelIndex &par);
};

#endif // TREEMODEL_H
