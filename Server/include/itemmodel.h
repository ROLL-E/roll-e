#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QObject>

class ItemModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE set_name  NOTIFY nameChanged)
    Q_PROPERTY(QString attribute READ attribute WRITE set_attribute  NOTIFY attributeChanged)
    Q_PROPERTY(int item_id READ item_id WRITE set_item_id  NOTIFY itemIdChanged)
public:
    ItemModel(QObject* parent=0);
    ItemModel(const QString &name, const QString &attribute, const int item_id, QObject* parent=0);

    QString name() const;
    void set_name(const QString &name);

    QString attribute() const;
    void set_attribute(const QString &attribute);

    int item_id() const;
    void set_item_id(const int &item_id);

signals:
    void nameChanged();
    void attributeChanged();
    void itemIdChanged();

private:
    QString name_;
    QString attribute_;
    int item_id_;


};

#endif // ITEMMODEL_H
