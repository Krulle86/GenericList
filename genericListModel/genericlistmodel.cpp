#include "genericlistmodel.h"
#include "genericitemlist.h"

#include <QMetaProperty>
#include <QDebug>

using namespace GenericList;

GenericModel::GenericModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

ItemList *GenericModel::itemList() const
{
    return m_list;
}

void GenericModel::setItemList(ItemList *newList)
{
    beginResetModel();

    if (m_list)
        m_list->disconnect(this);

    m_list = newList;

    if (m_list) {
        connect(m_list, &ItemList::preItemAppended, this, [=]() {
            const int index = m_list->items().size();
            beginInsertRows(ROOT_MODEL_INDEX, index, index);
        });
        connect(m_list, &ItemList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(m_list, &ItemList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(ROOT_MODEL_INDEX, index, index);
        });
        connect(m_list, &ItemList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(m_list, &ItemList::connectionDataChanged, this, &GenericModel::connectionDataChanged);
    }

    endResetModel();
}

QVariant GenericModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const QObject *item = m_list->items().at(index.row());
    return item->property(item->metaObject()->property(role).name());
}

bool GenericModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << Q_FUNC_INFO << QString("i: %1, value: %2").arg(index.row()).arg(value.toString());
    if(!index.isValid())
        return false;

    QObject *item = m_list->items().at(index.row());
    return item->setProperty(item->metaObject()->property(role).name(), value);
}

int GenericModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_list->items().size();
}

QHash<int, QByteArray> GenericModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    if (!m_list->items().isEmpty()) {
        for(int i = 0; i < m_list->items().at(0)->metaObject()->propertyCount(); i++) {
            roles[i] = m_list->items().at(0)->metaObject()->property(i).name();
        }
    }

    return roles;
}

Qt::ItemFlags GenericModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

void GenericModel::connectionDataChanged(int indexOfSender, int signalIndexHashValue)
{
    QModelIndex idx = createIndex(indexOfSender,0);

    QVector<int> roles;
    roles.append(signalIndexHashValue);
    emit dataChanged(idx, idx, roles);
}

