#pragma once

#include "genericitemlist.h"
#include <QAbstractListModel>
#include <QDebug>

//Q_MOC_INCLUDE("genericitemlist.h")

namespace GenericList {

    static const QModelIndex ROOT_MODEL_INDEX;

    class GenericModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(ItemList *itemList READ itemList WRITE setItemList)
    public:
        explicit GenericModel(QObject *parent = nullptr);

        ItemList *itemList() const;
        void setItemList(ItemList *newList);

        QVariant data(const QModelIndex &index, int role) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role) override;
        int rowCount(const QModelIndex &parent) const override;
        QHash<int, QByteArray> roleNames() const override;
        Qt::ItemFlags flags(const QModelIndex& index) const override;

    private:
        ItemList *m_list = nullptr;
        const QHash<int, QByteArray> m_roles;

    public slots:
        void connectionDataChanged(int indexOfSender, int signalIndexHashValue);

    };
}

