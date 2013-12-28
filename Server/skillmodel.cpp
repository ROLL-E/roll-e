#include "skillmodel.h"
#include "Skill.h"

SkillModel::SkillModel(QObject *parent) :
  QAbstractListModel(parent)
{

}

int SkillModel::rowCount(const QModelIndex &parent) const {
  return skills.size();
}

QVariant SkillModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  if (index.row() >= skills.size()) return QVariant();
  if (role == Qt::DisplayRole) {
    return QVariant(skills.at(index.row())->get_name());
  }
  else
    return QVariant();
}

Qt::ItemFlags SkillModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags flags = QAbstractListModel::flags(index);
  return flags;
}

