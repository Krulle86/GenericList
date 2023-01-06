#ifndef SPECIALICEDITEM_H
#define SPECIALICEDITEM_H

#include <QObject>

class SpecialicedItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit SpecialicedItem(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &newName);

signals:
    void nameChanged();
private:
    QString m_name;
};

#endif // SPECIALICEDITEM_H
