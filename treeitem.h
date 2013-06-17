#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>

class TreeItem;

typedef QList<TreeItem*> TreeItemList;
typedef QMap<qint32, QVariant> RoleMap;
typedef QMap<qint32, RoleMap> ItemData;
typedef QMap<qint32, qint32> FlagsMap;

class TreeItem
{
	friend class TreeModel;
private:
	ItemData m_data;
	FlagsMap m_flags;
	QVariant m_user_data;
	TreeItem *m_parent;
	TreeItemList m_children;

public:
	~TreeItem();

private:
	TreeItem(TreeItem *_parent, qint32 _row);

	QVariant data(qint32 i, qint32 _role) const { return m_data.value(i).value(_role); }
	qint32 flags(qint32 i) const { return m_flags.value(i, 0); }
	QVariant userData() const { return m_user_data; }

	TreeItem *parent() { return m_parent; }
	TreeItemList children() const { return m_children; }
	TreeItem *child(qint32 i) { return m_children.value(i, NULL); }

	void setData(qint32 i,qint32 _role, const QVariant &_data) { m_data[i][_role] = _data; }
	void setFlags(qint32 i, qint32 _flags) { m_flags[i] = _flags; }
	void setUserData(const QVariant &_user_data)  { m_user_data = _user_data; }

	void delChild(qint32 i);
};

#endif // TREEITEM_H

