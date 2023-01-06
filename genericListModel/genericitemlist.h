#pragma once

#include <QObject>
#include <QHash>

namespace GenericList {

    class ItemList : public QObject
    {
        Q_OBJECT

    public:
        explicit ItemList(QObject *parent = nullptr);
        ~ItemList();

        QVector<QObject *> items() const;

        // implement new functions
        void appendItem(QObject *item);
        bool removeItemAt(int i);
        bool insertItem(int index, QObject *item);
        int count();

    signals:
        void preItemAppended();
        void postItemAppended();

        void preItemRemoved(int index);
        void postItemRemoved();

        void connectionDataChanged(int indexOfSender, int signalIndexHashValue);

    private slots:
        void onDataChanged();               // slot that emit's dataChanged signal

    protected:
        QVector<QObject *> m_itemList;
        QHash<int, int> m_propertySignalIndexHash;
    };

    template <typename T>
    class GenericItemList : public ItemList
    {
    public:
        explicit GenericItemList(QObject *parent) :
            ItemList(parent) {}

        void appendItem(T *item) {
            ItemList::appendItem(dynamic_cast<QObject*>(item));
        }
        bool removeItemAt(int i) { return ItemList::removeItemAt(i); }

        int count() {
            return m_itemList.count();
        }
    };
}

