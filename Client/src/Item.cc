#include "Item.h"
#include <stdexcept>
#include <iostream>
#include <QDebug>

using namespace std;

quint16 Item::next_ID{0};

void Item::set_next_ID(quint16 new_ID){
  next_ID = new_ID;
}

Item::Item(const Item& other)
  : name{other.name},
    modifiers{other.modifiers},
    ID{next_ID},
    attributes{other.attributes} {

  ++next_ID;
}

Item::Item(const QString& new_name)
  : name{new_name} {
  ID = next_ID++;
}

Item::Item(const quint16& new_id) : ID{new_id} {
  next_ID = new_id + 1;
}

QString Item::get_name() const {
  return name;
}

QMap<QString, qint8> Item::get_modifiers() const {
  return modifiers;
}

quint16 Item::get_id() const {
  return ID;
}

QMap<QString, qint16> Item::get_attributes() const {
  return attributes;
}

void Item::set_name(const QString& new_name) {
  name = new_name;
}

void Item::set_modifier(const QString& mod_name, qint8 value) {
  modifiers[mod_name] = value;
}

void Item::set_attribute(const QString& attr_name, qint16 value) {
  attributes[attr_name] = value;
}

void Item::remove_attribute(const QString& attr_to_remove) {
  if (attributes.remove(attr_to_remove) == 0)
    throw invalid_argument("Attribute does not exist");
}

void Item::remove_modifier(const QString& mod_to_remove) {
  if (modifiers.remove(mod_to_remove) == 0)
    throw invalid_argument("Modifier does not exist");
}
