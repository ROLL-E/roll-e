#ifndef ATTRIBUTETABLEMODEL_H
#define ATTRIBUTETABLEMODEL_H

#include <QAbstractListModel>
#include <QMap>

class AttributeTableModel : public QAbstractListModel
{
  Q_OBJECT
public:
  explicit AttributeTableModel(QObject *parent = 0);
  AttributeTableModel(QMap<QString, qint16> new_attr, QObject *parent = 0) :
    QAbstractListModel(parent),
    attributes(new_attr)
  {}

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  //int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  //QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;

signals:

public slots:

private:
    QMap<QString, qint16> attributes;

};

#endif // ATTRIBUTETABLEMODEL_H
