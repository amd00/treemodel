#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>

class TreeItem;

typedef QList<TreeItem*> TreeItemList;				//!< Список объектов класса \e TreeItem.
typedef QMap<qint32, QVariant> RoleMap;	//!< Набор значений для различных ролей.
typedef QMap<qint32, RoleMap> ItemData;				//!< Набор данных полей элемента.
typedef QMap<qint32, qint32> FlagsMap;		//!< Набор флагов полей элемента.

//! Класс \e TreeItem реализует элемент дерева.
class TreeItem
{
	friend class TreeModel;
private:
	ItemData m_data;			//!< Набор данных для каждого поля и каждой роли элемента.
	FlagsMap m_flags;			//!< Набор флагов для каждого поля элемента.
	QVariant m_user_data;		//!< Произвольные пользовательские данные.
	TreeItem *m_parent;			//!< Указатель на родительский элемент.
	TreeItemList m_children;	//!< Список детей элемента.

public:
	~TreeItem();																								//!< Деструктор.

private:
	TreeItem(TreeItem *_parent, qint32 _row);																	//!< Конструктор.

	QVariant data(qint32 i, qint32 _role) const { return m_data.value(i).value(_role); }						//!< Данные для \e i-го поля роли \e _role.
	qint32 flags(qint32 i) const { return m_flags.value(i, 0); }												//!< Флаги для \e i-го поля.
	QVariant userData() const { return m_user_data; }															//!< Пользовательские данные.

	TreeItem *parent() { return m_parent; }																		//!< Указатель на родительский элемент.
	TreeItemList children() const { return m_children; }														//!< Список потомков элемента.
	TreeItem *child(qint32 i) { return m_children.value(i, NULL); }												//!< \e i-й потомок элемента.

	void setData(qint32 i,qint32 _role, const QVariant &_data) { m_data[i][_role] = _data; }					//!< Запись данных \e _data в \e i-е поле для роли \e _role.
	void setFlags(qint32 i, qint32 _flags) { m_flags[i] = _flags; }												//!< Запись флагов\e _flags в \e i-е поле.
	void setUserData(const QVariant &_user_data)  { m_user_data = _user_data; }									//!< Запись пользовательских данных.

	void delChild(qint32 i);																					//!< Удаление \e i-го потомка.
};

#endif // TREEITEM_H

