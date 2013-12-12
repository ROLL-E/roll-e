#include "Character.h"

using namespace std;

Character::Character(QMap<QString, qint16> new_attributes, quint16 start_max_weight, Story* new_story)
  : attributes{new_attributes},
    story{new_story},
    inventory{start_max_weight, new_story} {
}

Character::Character(const Character& other)
  : name{other.name},
    attributes{other.attributes},
    skills{other.skills},
    inventory(other.inventory) {
}

QString Character::get_name() const {
  return name;
}

void Character::set_name(const QString& new_name) {
  name = new_name;
}

qint16 Character::get_attribute(QString attr_name) const {
  return attributes.value(attr_name); // operator[] is not const-safe
}

void Character::set_attribute(const QString& attr_name, qint16 value) {
  attributes[attr_name] = value;
}

void Character::add_to_attribute(const string& attr_name, int value) {
        attributes[attr_name] = value + attributes.at(attr_name);
}

void Character::take_damage(const QString& type, qint16 amount) {
  //TODO add the handling
  // placeholder for testing:
  if (attributes.count("health") == 1) {
    if (type == "blunt") {
      if (attributes.count("armor") == 1)
        attributes["health"] -= amount - attributes["armor"];
    }
    else
      attributes["health"] -= amount;
  }
}

QList<Skill*> Character::get_skills() const {
  return skills;
}

void Character::add_skill(Skill* new_skill) {
  skills.push_back(new_skill);
}

void Character::remove_skill(Skill* skill_to_remove) {
  skills.removeOne(skill_to_remove); // won't this destroy the skill itself, since remove calls the element's destructor?
}

void Character::add_item(quint16 new_id) {
  inventory.add_item(new_id);
}

void Character::remove_item(quint16 id_to_remove) {
  inventory.remove_item(id_to_remove);
}

bool Character::has_item(quint16 id) const {
  return inventory.has_item(id);
}

QDataStream& Character::write_to_stream(QDataStream& ds) {
 ds << name;
 ds << attributes;
 ds << skills;
 ds << inventory;

 return ds;
}

QDataStream& Character::read_from_stream(QDataStream& ds) {
  ds >> name;
  ds >> attributes;
  ds >> skills;
  ds >> inventory;

  return ds;
}

QDataStream& operator<<(QDataStream& out_stream, Character*& character) {
  return character->write_to_stream(out_stream);
}

QDataStream& operator>>(QDataStream& in_stream, Character*& character) {
  return character->read_from_stream(in_stream);
}
