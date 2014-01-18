#include "Character.h"
#include "Skill.h"
#include <QFile>
#include <QDebug>

using namespace std;

Character::Character(QMap<QString, qint16> new_attributes, quint16 start_max_weight, Story* new_story)
  : attributes{new_attributes},
    story{new_story},
    inventory{start_max_weight, new_story} {
}

Character::Character(const Character& other, QObject *parent)
  : QObject(parent),
    name{other.name},
    attributes{other.attributes},
    skills{other.skills},
    inventory(other.inventory) {
}

QString Character::get_name() const {
  return name;
}

QPointer<ClientConnection> Character::get_connection(){
    return client;
}

void Character::set_connection(ClientConnection* connection){
    client = connection;
    if(client != nullptr){
    connect(this,SIGNAL(changed(Character*)),client,SLOT(push_data(Character*)));
    emit changed(this);
    }
}

void Character::set_story(Story* new_story)
{
  story = new_story;
  inventory.set_story(new_story);
}

void Character::set_name(const QString& new_name) {
    name = new_name;
    emit changed(this);
}

qint16 Character::get_attribute(QString attr_name) const {
    return attributes.value(attr_name); // operator[] is not const-safe
}

QMap<QString, qint16> Character::get_attributes() const
{
    return attributes;
}

void Character::set_attribute(const QString& attr_name, qint16 value) {
  attributes[attr_name] = value;
  emit changed(this);
}

void Character::add_to_attribute(const QString& attr_name, qint16 value) {
    attributes[attr_name] = value + attributes.value(attr_name);
    emit changed(this);
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
  emit changed(this);
}

QList<Skill*> Character::get_skills() const {
  return skills;
}

void Character::add_skill(Skill* new_skill) {
  skills.push_back(new_skill);
  emit changed(this);
}

void Character::remove_skill(Skill* skill_to_remove) {
  skills.removeOne(skill_to_remove); // won't this destroy the skill itself, since remove calls the element's destructor?
  emit changed(this);
}

void Character::add_item(quint16 new_id) {
  inventory.add_item(new_id);
  emit changed(this);
}

void Character::remove_item(quint16 id_to_remove) {
  inventory.remove_item(id_to_remove);
  emit changed(this);
}

bool Character::has_item(quint16 id) const {
  return inventory.has_item(id);
}

QDataStream& Character::write_to_stream(QDataStream& ds) {

    qDebug() << "character name";
    ds << name;
    qDebug() << "character attributes";
    ds << attributes;
    qDebug() << "dynamic casting";
  qDebug() << "inventory";
  ds << inventory;

  if (dynamic_cast<QFile*>(ds.device()) != nullptr) {
    qDebug() << "skill ids";
      ds << skill_ids;
      qDebug() << skill_ids;
      qDebug() << "after skill ids";
  }
  else {
      qDebug() << "skills";
      ds << skills.size();
      qDebug() << "skills.size()" << skills.size();

      for (Skill* ptr : skills){
          qDebug() << "attempting to write a skill.";
          ds << ptr;
      }
      qDebug() << "after skills";
  }
  qDebug() << "Serializing done!";
 return ds;
}

QDataStream& Character::read_from_stream(QDataStream& ds) {
  ds >> name;
  ds >> attributes;
  ds >> inventory;
  ds >> skill_ids;

  return ds;
}

QDataStream& operator<<(QDataStream& out_stream, Character*& character) {
  return character->write_to_stream(out_stream);
}

QDataStream& operator>>(QDataStream& in_stream, Character*& character) {
  character = new Character();
  return character->read_from_stream(in_stream);
}
