#include "Character.h"

using namespace std;

Character::Character(std::map<std::string, int> new_attributes)
  : attributes{new_attributes} {

}

Character::Character(const Character& other)
  : name{other.name},
    attributes{other.attributes},
    skills{other.skills} {
}

string Character::get_name() const {
  return name;
}

void Character::set_name(const string& new_name) {
  name = new_name;
}

int Character::get_attribute(const string& attr_name) {
  return attributes[attr_name];
}

void Character::set_attribute(const string& attr_name, int value) {
  attributes[attr_name] = value;
}

// add_to_attribute?

void Character::take_damage(const string& type, int amount) {
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

std::list<Skill*> Character::get_skills() {
  return skills;
}

void Character::add_skill(Skill* new_skill) {
  skills.push_back(new_skill);
}

void Character::remove_skill(Skill* skill_to_remove) {
  skills.remove(skill_to_remove); // won't this destroy the skill itself, since remove calls the element's destructor?
}

void Character::add_item(int new_id) {
  inventory.add_item(new_id);
}

void Character::remove_item(int id_to_remove) {
  inventory.remove_item(id_to_remove);
}

bool Character::has_item(int id) const {
  return inventory.has_item(id);
}

