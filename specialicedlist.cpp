#include "specialicedlist.h"

SpecialicedList::SpecialicedList(QObject *parent)
    : GenericList::GenericItemList<SpecialicedItem>{parent}
{

}

void SpecialicedList::appendItem(const QString &name)
{
    SpecialicedItem *item = new SpecialicedItem(this);
    item->setName(name);
    GenericItemList::appendItem(item);
}

bool SpecialicedList::removeItemAt(int index)
{
    return GenericItemList::removeItemAt(index);
}

int SpecialicedList::count()
{
    return GenericItemList::count();
}
