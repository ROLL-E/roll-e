#include "Item.h"

using namespace std;

Item::Item(const Item& other)
  : name{other.name},
    modifiers{other.modifiers},
    ID{Item::next_ID},
    attributes{other.attributes} {

  ++Item::next_ID;
}

Item::Item(const string& new_name) : name{new_name} {
  ID = Item::next_ID++;
}

string Item::get_name() const {
  return name;
}

map<string, int> Item::get_modifiers() const {
  return modifiers;
}

int Item::get_id() const {
  return ID;
}

map<string, int> Item::get_attributes() const {
  return attributes;
}

int Item::get_weight() const {
  return weight;
}

void Item::set_name(const string& new_name) {
  name = new_name;
}

void Item::set_modifier(const string& mod_name, int value) {
  modifiers[mod_name] = value;
}

void Item::set_attribute(const string& attr_name, int value) {
  attributes[attr_name] = value;
}

void Item::set_weight(int new_weight) {
  weight = new_weight;
}

void Item::remove_attribute(const string& attr_to_remove) {
  attributes.erase(attr_to_remove);
}

void Item::remove_modifier(const string& mod_to_remove) {
  modifiers.erase(mod_to_remove);
}



