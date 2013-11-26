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


