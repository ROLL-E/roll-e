#include "Inventory.h"
#include <algorithm>

using namespace std;

Inventory::Inventory(int new_max_weight)
  : max_weight{new_max_weight} {
}

Inventory::Inventory(const Inventory& other)
  : items{other.items},
    max_weight{other.max_weight},
    current_weight{other.current_weight},
    equipped{other.equipped} {
}

int Inventory::get_weight() const {
  return current_weight;
}

int Inventory::get_max_weight() const {
  return max_weight;
}

list<int> Inventory::get_equipped() const {
  return equipped;
}

bool Inventory::has_item(int id) const {
  return (find(items.begin(), items.end(), id) != items.end());
}

void Inventory::set_max_weight(int new_max) {
  max_weight = new_max;
}

void Inventory::add_item(int id_to_add) {
  items.push_back(id_to_add);
}

void Inventory::remove_item(int id_to_remove) {
  items.remove(id_to_remove);
}

void Inventory::equip(int id_to_equip){
  equipped.push_back(id_to_equip);
}

void Inventory::unequip(int id_to_unequip) {
  equipped.remove(id_to_unequip);
}


