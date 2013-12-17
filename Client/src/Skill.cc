#include "Skill.h"

QMap<QString,qint8> Skill::get_modifiers() const {
  return modifiers;
}

QString Skill::get_name() const {
  return name;
}

void Skill::set_modifier(const QString& mod_name, qint8 value) {
  modifiers[mod_name] = value;
}

void Skill::set_name(const QString& new_name) {
  name = new_name;
}
