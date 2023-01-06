#include "genericitemlist.h"

#include <QDebug>
#include <QMetaProperty>
#include <QModelIndex>

using namespace GenericList;

ItemList::ItemList(QObject *parent)
    : QObject{parent}
{

}

ItemList::~ItemList()
{
    for(int i = 0; i < m_itemList.size(); i++) {
        delete m_itemList.takeAt(i);
    }
}

QVector<QObject *> ItemList::items() const
{
    return m_itemList;
}

bool ItemList::insertItem(int index, QObject *item)
{
    if (index < 0 || index >= m_itemList.size())
        return false;

    m_itemList.insert(index, item);

    return true;
}

void ItemList::appendItem(QObject *item)
{
    /* map the notify()-signal-index with the property-index when the first item get's inserted */
    if (m_itemList.isEmpty()) {
        for(int i = 0; i < item->metaObject()->propertyCount(); i++) {
            m_propertySignalIndexHash.insert(item->metaObject()->property(i).notifySignalIndex(), i);
        }
    }

    /* connect each notify()-signals to the onDataChanged()-slot which call's the dataChanged()-signal */
    for(int i = 0; i < item->metaObject()->propertyCount(); i++) {
        connect(item, "2" + item->metaObject()->property(i).notifySignal().methodSignature(), this, SLOT(onDataChanged()));
    }

    emit preItemAppended();

    m_itemList.append(item);

    emit postItemAppended();
}

bool ItemList::removeItemAt(int index)
{
    qDebug() << Q_FUNC_INFO << " index: " << index;
    if (index < 0 || index >= m_itemList.size())
        return false;

    QObject *tmpObject = m_itemList.at(index);

    for(int i = 0; i < tmpObject->metaObject()->propertyCount(); i++) {
        disconnect(tmpObject, "2" + tmpObject->metaObject()->property(i).notifySignal().methodSignature(), this, SLOT(onDataChanged()));
    }

    emit preItemRemoved(index);
    delete m_itemList.takeAt(index);
    emit postItemRemoved();
    return true;
}

int ItemList::count()
{
    return m_itemList.size();
}

void ItemList::onDataChanged()
{
    emit connectionDataChanged(m_itemList.indexOf(sender()), m_propertySignalIndexHash.value(senderSignalIndex()));
}
