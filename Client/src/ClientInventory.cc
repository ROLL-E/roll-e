#include "ClientInventory.h"
#include <algorithm>

using namespace std;

ClientInventory::ClientInventory(int new_max_weight)
  : max_weight{new_max_weight} {
}

ClientInventory::ClientInventory(const ClientInventory& other)
  : items{other.items},
    max_weight{other.max_weight},
    current_weight{other.current_weight},
    equipped{other.equipped} {
}

int ClientInventory::get_weight() const {
  return current_weight;
}

int ClientInventory::get_max_weight() const {
  return max_weight;
}

QList<Item*> ClientInventory::get_equipped() const {
  return equipped;
}

bool ClientInventory::has_item(Item* item) const {
  return (find(items.begin(), items.end(), item) != items.end());
}

void ClientInventory::set_max_weight(int new_max) {
  max_weight = new_max;
}

void ClientInventory::add_item(Item* item_to_add) {
  items.push_back(item_to_add);
}

void ClientInventory::remove_item(Item* item_to_remove) {
  items.removeOne(item_to_remove);
}

void ClientInventory::equip(Item* item_to_equip){
  equipped.push_back(item_to_equip);
}

void ClientInventory::unequip(Item* item_to_unequip) {
  equipped.removeOne(item_to_unequip);
}


