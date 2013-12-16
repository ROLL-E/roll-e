#include "Character.h"

using namespace std;

Character::Character(map<string, int> new_attributes, int start_max_weight)
  : attributes{new_attributes},
    inventory{start_max_weight} {
}

Character::Character(const Character& other)
  : name{other.name},
    attributes{other.attributes},
    skills{other.skills},
    inventory(other.inventory) {
}

string Character::get_name() const {
  return name;
}

void Character::set_name(const string& new_name) {
  name = new_name;
}

int Character::get_attribute(const string& attr_name) const {
  return attributes.at(attr_name); // operator[] is not const-safe
}

void Character::set_attribute(const string& attr_name, int value) {
  attributes[attr_name] = value;
}

void Character::add_to_attribute(const string& attr_name, int value) {
        attributes[attr_name] = value + attributes.at(attr_name);
}


std::list<Skill*> Character::get_skills() const {
  return skills;
}

void Character::add_skill(Skill* new_skill) {
  skills.push_back(new_skill);
}

void Character::remove_skill(Skill* skill_to_remove) {
  skills.remove(skill_to_remove); // won't this destroy the skill itself, since remove calls the element's destructor?
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

ServerConnection* Character::get_server() const {
    return server;
}

void Character::set_server(ServerConnection* new_server) {
    server = new_server;
}


