#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QObject>

class ItemModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE set_name  NOTIFY nameChanged)
    Q_PROPERTY(QString attribute READ attribute WRITE set_attribute  NOTIFY attributeChanged)
public:
    ItemModel(QObject* parent=0);
    ItemModel(const QString &name, const QString &attribute, QObject* parent=0);

    QString name() const;
    void set_name(const QString &name);

    QString attribute() const;
    void set_attribute(const QString &attribute);

signals:
    void nameChanged();
    void attributeChanged();

private:
    QString name_;
    QString attribute_;


};

#endif // ITEMMODEL_H
