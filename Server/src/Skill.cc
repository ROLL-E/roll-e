#include "Skill.h"
#include <QFile>
#include <QDebug>

QMap<QString,qint8> Skill::get_modifiers() const {
    return modifiers;
}

qint8 Skill::get_modifier(const QString& name) const {
    return modifiers.value(name);
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

void Skill::clear_modifiers()
{
  modifiers.clear();
}

QDataStream& Skill::write_to_stream(QDataStream& ds) const {
    qDebug() << "Writing skill: " << name;
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
    skill = new Skill();
    return skill->read_from_stream(ds);
}

