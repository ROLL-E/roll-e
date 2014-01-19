#include "Character.h"

Character::Character(QMap<QString, qint16> new_attributes, quint16 start_max_weight)
  : attributes{new_attributes},
    inventory{start_max_weight} {
}


Character::Character(const Character& other)
  : name{other.name},
    attributes{other.attributes},
    skills{other.skills},
    inventory(other.inventory) {
}

// For debugging purposes
//void Character::get_status(){
//    qDebug() << name;
//    for(auto key : attributes.keys()){
//        qDebug() << key << attributes.value(key);
//    }
//    for(Item* item : inventory.get_items()){
//        qDebug() << item->get_name();
//    }
//    for(Item* item : inventory.get_equipped()){
//        qDebug() << item->get_name();
//    }
//    qDebug() << inventory.get_max_weight();
//    qDebug() << inventory.get_items().size();
//    qDebug() << inventory.get_weight();
//    for(Skill* skill : skills){
//        qDebug() << skill->get_name();
//    }
//}

QString Character::get_name() const {
  return name;
}

void Character::set_name(const QString& new_name) {
  name = new_name;
}

qint16 Character::get_attribute(const QString& attr_name) const {
  return attributes.value(attr_name); // operator[] is not const-safe
}

QMap<QString, qint16> Character::get_attributes() const {
  return attributes;
}

void Character::set_attribute(const QString& attr_name, qint16 value) {
  attributes[attr_name] = value;
}

void Character::add_to_attribute(const QString& attr_name, qint16 value) {
        attributes[attr_name] = value + attributes.value(attr_name);
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

void Character::add_item(Item* new_item) {
  inventory.add_item(new_item);
}

void Character::remove_item(Item* item_to_remove) {
  inventory.remove_item(item_to_remove);
}

bool Character::has_item(Item* item) const {
  return inventory.has_item(item);
}

QDataStream& Character::read_from_stream(QDataStream& ds) {
  ds >> name;
  ds >> attributes;
  ds >> inventory;

  int number_of_skills{0};
  ds >> number_of_skills;

  Skill* temp_skill = new Skill();
  for (int i{0}; i < number_of_skills; ++i) {
      ds >> temp_skill;
      skills.push_back(new Skill(*temp_skill));
  }
  temp_skill = nullptr;
  return ds;
}

QDataStream& operator>>(QDataStream& in_stream, Character*& character) {
    delete character;
    character = new Character(*(new QMap<QString,qint16>),0);
    return character->read_from_stream(in_stream);
}
