#include "specialiceditem.h"

SpecialicedItem::SpecialicedItem(QObject *parent)
    : QObject{parent}
{

}

QString SpecialicedItem::name() const
{
    return m_name;
}

void SpecialicedItem::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}
