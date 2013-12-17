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
  qint8 get_modifier(const QString&) const;
  QString get_name() const;


  void set_modifier(const QString&,qint8);
  void set_name(const QString&);

  void remove_modifier(const QString&);

  QDataStream& read_from_stream(QDataStream&);
  QDataStream& write_to_stream(QDataStream&) const;

};

QDataStream& operator<<(QDataStream&, Skill*&);
QDataStream& operator>>(QDataStream&, Skill*&);

#endif
