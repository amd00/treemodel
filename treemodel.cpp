
#include <QStringList>
#include "treemodel.h"

TreeModel::TreeModel() : QAbstractItemModel(), m_root(NULL)
{
	m_root = new TreeItem(NULL, 0);
}

TreeModel::~TreeModel()
{
	if(m_root)
		delete m_root;
}

QVariant TreeModel::data(const QModelIndex &_ind, int _role) const
{
	if(!_ind.isValid())
		return QVariant();
	return this -> item(_ind) -> data(_ind.column(), _role);
}

bool TreeModel::setData(const QModelIndex &_ind, const QVariant &_val, int _role)
{
        if(!_ind.isValid())
                return false;
	TreeItem *item = this -> item(_ind);
	item -> m_data[_ind.column()][_role] = _val;
	Q_EMIT dataChanged(_ind, _ind);
	return true;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &_ind) const
{
	Qt::ItemFlags res = (Qt::ItemFlags)this -> item(_ind) -> flags(_ind.column());
	res = res ? res : (Qt::ItemFlags)m_root -> flags(_ind.column());
	return res;
}

Qt::ItemFlags TreeModel::flags(qint32 _column) const
{
	return (Qt::ItemFlags)m_root -> flags(_column);
}

void TreeModel::clear()
{
	removeRows(0, rowCount());
}

QVariant TreeModel::headerData(qint32 _section, Qt::Orientation _orient, qint32 _role) const
{
	if(_orient != Qt::Horizontal)
		return QVariant();
        if(m_root -> data(_section, _role).toString().isNull())
		return QVariant();
	return m_root -> data(_section, _role);
}

qint32 TreeModel::rowCount(const QModelIndex &_par) const
{
	TreeItem *item = this -> item(_par);
	return (item!=NULL)?item -> children().count():0;
}

qint32 TreeModel::columnCount(const QModelIndex &_ind) const
{
	Q_UNUSED(_ind)
	return m_root -> m_data.size();
}

QModelIndex TreeModel::index(qint32 _row, qint32 _column, const QModelIndex &_par) const
{
	if(!hasIndex(_row, _column, _par))
		return QModelIndex();
	TreeItem *par_item = this -> item(_par);
	TreeItem *item = par_item -> child(_row);
	if(!item)
		return QModelIndex();
	return createIndex(_row, _column, item);
}

QModelIndex TreeModel::parent(const QModelIndex &_ind) const
{
	TreeItem *item = this -> item(_ind);
	if(!item || !item -> parent() || !item -> parent() -> parent())
		return QModelIndex();
	qint32 row = item -> parent() -> parent() -> children().indexOf(item -> parent());
	return createIndex(row, 0, item -> parent());
}

bool TreeModel::insertRows(qint32 _row, qint32 _count, const QModelIndex &_par)
{
	if(_row < 0 || _row > rowCount(_par))
		return false;
	beginInsertRows(_par, _row, _row + _count - 1);
	TreeItem *par_item = this -> item(_par);
	for(qint32 i = 0; i < _count; i++)
		new TreeItem(par_item, _row + i);
	endInsertRows();
	return true;
}

bool TreeModel::removeRows(qint32 _row, qint32 _count, const QModelIndex &_par)
{
	if(_row < 0 || _row + _count > rowCount(_par) || _count == 0)
		return false;
	TreeItem *par_item = this -> item(_par);
	beginRemoveRows(_par, _row, _row + _count - 1);
	for(qint32 i = 0; i < _count; i++)
		par_item -> delChild(_row);
	endRemoveRows();
	return true;
}

void TreeModel::setHeader(const QStringList &_headers)
{
	ItemData data;
	foreach(QString head, _headers)
	{
		qint32 i = _headers.indexOf(head);
		RoleMap rm;
		rm[Qt::DisplayRole] = head;
		data[i] = rm;
		m_root -> setFlags(i, head.isNull() ? 0 : (qint32)(Qt::ItemIsEnabled | Qt::ItemIsSelectable));
	}

	m_root -> m_data = data;
	Q_EMIT headerDataChanged(Qt::Horizontal, 0, data.size() - 1);
}

QModelIndex TreeModel::addItem(const QModelIndex &_par, const ItemData &_data)
{
	QModelIndex _par_0 = _par.sibling(_par.row(), 0);
	qint32 new_item_row = rowCount(_par_0);
	if(!insertRow(new_item_row, _par_0))
		return QModelIndex();
	QModelIndex new_item_ind = index(new_item_row, 0, _par_0);
	this -> item(new_item_ind) -> m_data = _data;
	return new_item_ind;
}

void TreeModel::editItem(const QModelIndex &_ind, qint32 _role, const QVariant &_val)
{
	setData(_ind, _val, _role);
}

void TreeModel::delItem(const QModelIndex &_ind)
{
	if(!_ind.isValid())
		return;
	removeRow(_ind.row(), _ind.parent());
}

QVariant TreeModel::userData(const QModelIndex &_ind) const
{
	return this -> item(_ind) -> userData();
}

void TreeModel::setUserData(const QModelIndex &_ind, const QVariant &_data)
{
	this -> item(_ind) -> setUserData(_data);
}

void TreeModel::setFlags(const QModelIndex &_ind, Qt::ItemFlags _flags)
{
	this -> item(_ind) -> setFlags(_ind.column(), _flags);
}

void TreeModel::setFlags(qint32 _column, Qt::ItemFlags _flags)
{
	this -> m_root -> setFlags(_column, _flags);
}

TreeItem *TreeModel::item(const QModelIndex &_ind) const
{
	if(!_ind.isValid())
		return m_root;
	return static_cast<TreeItem*>(_ind.internalPointer());
}

void TreeModel::swapChildren(qint32 i, qint32 j, const QModelIndex &par)
{
    TreeItem *item = this -> item(par);
    item -> m_children.swap(i, j);
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(orientation == Qt::Vertical)
            return false;
    m_root->m_data[section][role] = value;
    return true;
}
