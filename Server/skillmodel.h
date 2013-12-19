#ifndef SKILLMODEL_H
#define SKILLMODEL_H

#include <QAbstractListModel>
#include <QList>

class Skill;

class SkillModel : public QAbstractListModel
{
  Q_OBJECT
public:
  explicit SkillModel(QObject *parent = 0);
  SkillModel(QList<Skill*> new_skills) : skills(new_skills) {}

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
signals:

public slots:

private:
  QList<Skill*> skills;
};

#endif // SKILLMODEL_H
