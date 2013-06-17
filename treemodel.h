#ifndef _TREEMODEL_H_
#define _TREEMODEL_H_

#include <QAbstractItemModel>

#include "treeitem.h"

//! Класс, реализующий модель дерева.
class TreeModel : public QAbstractItemModel
{
	Q_OBJECT

private:
	TreeItem *m_root;	//!< Корневой элемент.

public:
	TreeModel();																									//!< Конструктор.
	virtual ~TreeModel();																							//!< Деструктор.

	void setHeader(const QStringList &_headers);																	//!< Задание заголовков.
	QModelIndex addItem(const QModelIndex &_par, const ItemData &_data);											//!< Добавление нового элемента к родителю.
	void editItem(const QModelIndex &_ind, qint32 _role, const QVariant &_val);										//!< Редактирование данных элемента.
	void delItem(const QModelIndex &_ind);																			//!< Удаление элемента.
	QVariant userData(const QModelIndex &_ind) const;																//!< Пользовательские данные элемента.
	void setUserData(const QModelIndex &_ind, const QVariant &_data);												//!< Запись пользовательских данных.
	void setFlags(const QModelIndex &_ind, Qt::ItemFlags _flags);													//!< Запись флагов.
	void setFlags(qint32 _column, Qt::ItemFlags _flags);															//!< Запись флагов.
	Qt::ItemFlags flags(const QModelIndex &_ind) const;																//!< Флаги элемента.
	Qt::ItemFlags flags(qint32 _column) const;																		//!< Флаги столбца.
        void clear();																			//!< Очищает все данные в модели.

protected:
	virtual bool setData(const QModelIndex &_ind, const QVariant &_val, int _role = Qt::EditRole);					//!< Редактирование данных.
	virtual QVariant data(const QModelIndex &_ind, int _role) const;												//!< Получение данных.
	virtual QVariant headerData(qint32 _section, Qt::Orientation _orient, qint32 _role = Qt::DisplayRole) const;	//!< Данные заголовка.
        bool setHeaderData(int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole);

	virtual qint32 rowCount(const QModelIndex &_par = QModelIndex()) const;											//!< Количество строк.
	virtual qint32 columnCount(const QModelIndex &_ind) const;														//!< Количество столбцов.

	QModelIndex index(qint32 _row, qint32 _column, const QModelIndex &_par) const;									//!< Индекс элемента.
	QModelIndex parent(const QModelIndex &_ind) const;																//!< Индекс родительского элемента.

	bool insertRows (qint32 _row, qint32 _count, const QModelIndex &_par = QModelIndex());							//!< Вставка строк.
	bool removeRows (qint32 _row, qint32 _count, const QModelIndex &_par = QModelIndex());							//!< Удаление строк.

	TreeItem *item(const QModelIndex &_ind) const;																	//!< Получение элемента по индексу.
        void swapChildren(qint32 i, qint32 j, const QModelIndex &par);   //!< Поменять местами двух потомков.
};

#endif // TREEMODEL_H
