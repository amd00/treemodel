
#include "treeitem.h"

TreeItem::TreeItem(TreeItem *_parent, qint32 _row) : m_data(), m_parent(_parent), m_children()
{
	if(m_parent)
	{
		if(!m_parent -> m_data.size())
			qFatal("Error: Empty headers. Set headers first");
		m_parent -> m_children.insert(_row, this);
	}
}

TreeItem::~TreeItem()
{
	qDeleteAll(m_children);
	m_children.clear();
}

void TreeItem::delChild(qint32 i)
{
	TreeItem *item = m_children.value(i, NULL);
	if(item)
		delete item;
	m_children.removeAt(i);
}

