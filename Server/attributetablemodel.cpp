#include "attributetablemodel.h"

AttributeTableModel::AttributeTableModel(QObject *parent) :
  QAbstractListModel(parent)
{
}

int AttributeTableModel::rowCount(const QModelIndex&) const {
  return attributes.size();
}

/*int AttributeTableModel::columnCount(const QModelIndex&) const {
  return 2;
}*/

QVariant AttributeTableModel::data(const QModelIndex &index, int role) const{
  if (!index.isValid()) return QVariant();
  if (index.row() >= attributes.size() || index.column() >= 2) return QVariant();
  if (role == Qt::DisplayRole) {

    if (index.column() == 1)
      return attributes.values().at(index.row());
    else
      return attributes.keys().at(index.row());
  }
}
/*
QVariant AttributeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole)

    if (section == 0)
      return QVariant("Attribute");
    else
      return QVariant("Value");

  else return QVariant();

}*/

Qt::ItemFlags AttributeTableModel::flags(const QModelIndex &index) const {
  return QAbstractListModel::flags(index);
}


