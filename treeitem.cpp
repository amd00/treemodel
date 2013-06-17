#include "treeitem.h"

/*! \class TreeItem
	Класс \e TreeItem содержит данные и реализует функционал элемента дерева.
*/
/*! Создаёт объект класса \e TreeItem и встраивает его в дерево. Если <em>_parent=NULL</em>, то это корневой элемент.
  \param _parent - указатель на родительский элемент.
  \param _row - строка, в которую добавляется элемент.
  */
TreeItem::TreeItem(TreeItem *_parent, qint32 _row) : m_data(), m_parent(_parent), m_children()
{
	if(m_parent)
	{
		if(!m_parent -> m_data.size())
			qFatal("Error: Empty headers. Set headers first");
		m_parent -> m_children.insert(_row, this);
	}
}

/*! Уничтожает объект класса и всех потомков.
  */
TreeItem::~TreeItem()
{
	qDeleteAll(m_children);
	m_children.clear();
}

/*! \fn QVariant TreeItem::data(qint32 i, qint32 _role) const
  Получение данных роли \e _role для \e i-го столбца.
  \param i - номер столбца.
  \param _role - роль данных.
  \returns данные.
  */
/*! \fn qint32 TreeItem::flags(qint32 i) const
  Получение флагов для \e i-го столбца.
  \param i - номер столбца.
  \returns флаги.
  */
/*! \fn QVariant TreeItem::userData() const
  Получение пользовательских данных, хранимых в элементе.
  \returns пользовательские данные.
  */
/*! \fn TreeItem *TreeItem::parent()
  Указатель на родительский объект элемента.
  \returns указатель на родительский объект.
  */
/*! \fn TreeItemList TreeItem::children() const
  Список потомков элемента.
  \returns список потомков.
  */
/*! \fn TreeItem *TreeItem::child(qint32 i)
  Указатель на \e i-го потомка элемента.
  \param i - номер потомка.
  \returns указатель на потомка.
  */
/*! \fn void TreeItem::setData(qint32 i, qint32 _role, const QVariant &_data)
  Присваивает данным в \e i-м столбце роли \e _role значение \e _data.
  \param i - номер столбца.
  \param _role - роль данных.
  \param _data - данные.
  */
/*! \fn void TreeItem::setFlags(qint32 i, qint32 _flags)
  Устанавливает флаги для \e i-го столбца элемента в значение \e _flags.
  \param i - номер столбца.
  \param _flags - флаги.
*/
/*! \fn void TreeItem::setUserData(const QVariant &_user_data)
  Присваивает пользовательским данным значение \e _user_data.
  \param _user_data - данные.
  */

/*! Удаляет потомка под номером \e i.
  \param i - номер удаляемого элемента.
  */
void TreeItem::delChild(qint32 i)
{
	TreeItem *item = m_children.value(i, NULL);
	if(item)
		delete item;
	m_children.removeAt(i);
}

