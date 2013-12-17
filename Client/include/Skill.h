#ifndef SKILL_H
#define SKILL_H
#include <QString>
#include <QMap>
#include <QDataStream>

class Skill
{
private:
  QString name;
  QMap<QString, qint8> modifiers;

public:
  static void set_next_ID(quint16);

  Skill(const QString& new_name): name{new_name} {}
  Skill() {}

  QMap<QString,qint8> get_modifiers() const;
  QString get_name() const;


  void set_modifier(const QString&,qint8);
  void set_name(const QString&);

  void remove_modifier(const QString&);

};
#endif
