#include "Skill.h"

quint16 Skill::next_ID{0};

Skill::Skill(const QString& new_name) : name{new_name} {
  ID = next_ID++;
}

Skill::Skill(const quint16& new_id) : ID{new_id} {
  next_ID = new_id + 1;
}

void Skill::set_modifier(const QString& mod_name, qint8 value) {
  modifiers[mod_name] = value;
}

void Skill::set_name(const QString& new_name) {
  name = new_name;
}

QDataStream& Skill::write_to_stream(QDataStream& ds) const {
  ds << name;
  ds << modifiers;

  return ds;
}

QDataStream& Skill::read_from_stream(QDataStream& ds) {
  ds >> name;
  ds >> modifiers;

  return ds;
}

QDataStream& operator<<(QDataStream& ds, Skill*& skill) {
  return skill->write_to_stream(ds);
}

QDataStream& operator>>(QDataStream& ds, Skill*& skill) {
  return skill->read_from_stream(ds);
}

