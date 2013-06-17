/*! \mainpage Библиотека treemodel.
  Библиотека \e treemodel служит для реализации древовидных структур данных при использовании механизма
  работы с данными <b>Модель-Представление</b>, реализованного в библиотеке Qt версии 4.
  \par
  Для начала работы с классом \e TreeModel достаточно создать объект и задать заголовок с помощью метода
  \e setHeader
  \code
  TreeModel model;
  model.setHeader(QStringList() << "Заголовок1" << "Заголовок2" << "Заголовок3");
  \endcode
  \par
  После этого мы можем добавлять, удалять и редактировать данные в модели.
  Для это служат следующие методы:\n
  1. \e addItem() \n
  2. \e editItem() \n
  3. \e delItem() \n

  */

#include <QStringList>
#include "treemodel.h"

/*! \class TreeModel
	Класс \e TreeModel является наследником \e QAbstractItemModel и реализует модель данных для
	древовидных структур. Класс нужен для отображения данных в окне \e QTreeView.
	*/
/*! Создаёт объект класса. Инициализирует корневой элемент дерева.
  */
TreeModel::TreeModel() : QAbstractItemModel(), m_root(NULL)
{
	m_root = new TreeItem(NULL, 0);
}

/*! Уничтожает объект класса.
  */
TreeModel::~TreeModel()
{
	if(m_root)
		delete m_root;
}

/*! Возвращает данные для роли \e _role элемента дерева, имеющего индекс \e _ind.
  Переопределённый метод базоваго класса \e QAbstractItemModel.
  \param _ind - индекс элемента.
  \param _role - роль данных.
  \returns данные для роли элемента.
  */
QVariant TreeModel::data(const QModelIndex &_ind, int _role) const
{
	if(!_ind.isValid())
		return QVariant();
	return this -> item(_ind) -> data(_ind.column(), _role);
}

/*! В элемент с индексом \e _ind для роли \e _role записываются данные \e _val.
  Переопределённый метод базоваго класса \e QAbstractItemModel.
  \param _ind - индекс элемента.
  \param _val - значение.
  \param _role - роль данных.
  \returns \b true - в случае успеха, \b false - иначе.
  */
bool TreeModel::setData(const QModelIndex &_ind, const QVariant &_val, int _role)
{
        if(!_ind.isValid())
                return false;
	TreeItem *item = this -> item(_ind);
	item -> m_data[_ind.column()][_role] = _val;
	Q_EMIT dataChanged(_ind, _ind);
	return true;
}

/*! Возвращает флаги для элемента с индексом \e _ind. Переопределённый метод базоваго класса \e QAbstractItemModel.
  \param _ind - индекс элемента.
  \returns флаги для элемента.
  */
Qt::ItemFlags TreeModel::flags(const QModelIndex &_ind) const
{
	Qt::ItemFlags res = (Qt::ItemFlags)this -> item(_ind) -> flags(_ind.column());
	res = res ? res : (Qt::ItemFlags)m_root -> flags(_ind.column());
	return res;
}

/*! Возвращает флаги для столбца \e _column.
  \param _column - номер столбца.
  \returns флаги для столбца.
  */
Qt::ItemFlags TreeModel::flags(qint32 _column) const
{
	return (Qt::ItemFlags)m_root -> flags(_column);
}

/*! Очищает все данные в модели.
  Очищает все данные в модели.
  */
void TreeModel::clear()
{
	removeRows(0, rowCount());
}

/*! Возвращает данные заголовка. Переопределённый метод базоваго класса \e QAbstractItemModel.
  \param _section - номер секции.
  \param _orient - расположение заголовка (горизонтальное/вертикальное).
  \param _role - роль данных.
  \returns данные для роли заголовка.
  */
QVariant TreeModel::headerData(qint32 _section, Qt::Orientation _orient, qint32 _role) const
{
	if(_orient != Qt::Horizontal)
		return QVariant();
// 	if(_role != Qt::DisplayRole)
// 		return QVariant();
        if(m_root -> data(_section, _role).toString().isNull())
		return QVariant();
	return m_root -> data(_section, _role);
}

/*! Возвращает количество строк (потомков) для элемента с индексом \e _par.
   Переопределённый метод базоваго класса \e QAbstractItemModel.
  \param _par - родительский элемент.
  \returns количество потомков \e _par.
  */
qint32 TreeModel::rowCount(const QModelIndex &_par) const
{
	TreeItem *item = this -> item(_par);
	return (item!=NULL)?item -> children().count():0;
}

/*! Возвращает количество столбцов для элемента с индексом \e _ind.
   Переопределённый метод базоваго класса \e QAbstractItemModel.
  \param _ind - индекс элемента.
  \returns количество столбцов.
  */
qint32 TreeModel::columnCount(const QModelIndex &_ind) const
{
	Q_UNUSED(_ind)
	return m_root -> m_data.size();
}

/*! Генерирует индекс для элемента, который содержится в строке \e _row и слолбце \e _column
  родительского элемента с индексом \e _par. Переопределённый метод базоваго класса \e QAbstractItemModel.
  \param _row - строка.
  \param _column - столбец.
  \param _par - индекс родительского элемента.
  \returns индекс элемента.
  */
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

/*! Генерирует индекс элемента потомком которого является элемент с индексом \e _ind.
   Переопределённый метод базоваго класса \e QAbstractItemModel.
  \param _ind - индекс элемента.
  \returns индекс родительского элемента.
  */
QModelIndex TreeModel::parent(const QModelIndex &_ind) const
{
	TreeItem *item = this -> item(_ind);
	if(!item || !item -> parent() || !item -> parent() -> parent())
		return QModelIndex();
	qint32 row = item -> parent() -> parent() -> children().indexOf(item -> parent());
	return createIndex(row, 0, item -> parent());
}

/*! Вставка \e _count строк начиная с позиции \e _row в элемент с индексом \e _par.
  Переопределённый метод базоваго класса \e QAbstractItemModel.
  \param _row - номер строки.
  \param _count - количество вставляемых строк.
  \param _par - индекс родительского элемента.
  \returns \b true - в случае успеха, \b false - иначе.
  */
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

/*! Удаление \e _count строк начиная с позиции \e _row из элемента с индексом \e _par.
  Переопределённый метод базоваго класса \e QAbstractItemModel.
  \param _row - номер строки.
  \param _count - количество удаляемых строк.
  \param _par - индекс родительского элемента.
  \returns \b true - в случае успеха, \b false - иначе.
  */
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

/*! Задаёт текст заголовков. Чтобы сделать столбец скрытым, нужно в списке \e _headers задать ему значение QString::null.
  \param _headers - список строк, содержащих заголовки.
  */
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

/*! Добавляет нового элемента-потомка к элементу \e _par и задаёт ему набор данных \e _data.
  \param _par - индекс родительского элемента.
  \param _data - набор данных для нового элемента.
  \returns индекс нового элемента.
  */
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

/*! Редактирование элемента с индексом \e _ind. Ему для роли \e _role присваиваются данные \e _data.
  \param _ind - индекс элемента.
  \param _role - роль данных.
  \param _val - данные.
  */
void TreeModel::editItem(const QModelIndex &_ind, qint32 _role, const QVariant &_val)
{
	setData(_ind, _val, _role);
}

/*! Удаление элемента с индексом \e _ind и всех его потомков.
  \param _ind - индекс элемента.
  */
void TreeModel::delItem(const QModelIndex &_ind)
{
	if(!_ind.isValid())
		return;
	removeRow(_ind.row(), _ind.parent());
}

/*! Пользовательские данные для элемента с индексом \e _ind.
  \param _ind - индекс элемента.
  \returns пользовательские данные.
  */
QVariant TreeModel::userData(const QModelIndex &_ind) const
{
	return this -> item(_ind) -> userData();
}

/*! Записть пользовательских данных \e _data в элемент с индексом \e _ind.
  \param _ind - индекс элемента.
  \param _data - данные.
  */
void TreeModel::setUserData(const QModelIndex &_ind, const QVariant &_data)
{
	this -> item(_ind) -> setUserData(_data);
}

/*! Запись набора флагов \e _flags в элемент с индексом \e _ind.
  \param _ind - индекс элемента.
  \param _flags - набор флагов.
  */
void TreeModel::setFlags(const QModelIndex &_ind, Qt::ItemFlags _flags)
{
	this -> item(_ind) -> setFlags(_ind.column(), _flags);
}

/*! Запись набора флагов \e _flags для столбца \e _column.
  \param _column - номер столбца.
  \param _flags - набор флагов.
  */
void TreeModel::setFlags(qint32 _column, Qt::ItemFlags _flags)
{
	this -> m_root -> setFlags(_column, _flags);
}

/*! Получение элемента дерева по его индексу \e _ind. Корневой элемент имеет невалидный индекс.
  \param _ind - индекс элемента.
  \returns элемент дерева.
  */
TreeItem *TreeModel::item(const QModelIndex &_ind) const
{
	if(!_ind.isValid())
		return m_root;
	return static_cast<TreeItem*>(_ind.internalPointer());
}
/*! Меняет местами потомков с индексами i и j.
  \param i - индекс потомка.
  \param j - индекс потомка.
  \param par - родитель элементов.
  */
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
