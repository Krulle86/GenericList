#pragma once

#include <QObject>
#include "genericitemlist.h"
#include "specialiceditem.h"

class SpecialicedList : public GenericList::GenericItemList<SpecialicedItem>
{
    Q_OBJECT
public:
    explicit SpecialicedList(QObject *parent = nullptr);

public slots:
    void appendItem(const QString &name);
    bool removeItemAt(int index);
    int count();
};

