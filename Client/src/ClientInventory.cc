#include "ClientInventory.h"
#include <algorithm>
#include "Item.h"
#include <QDebug>


ClientInventory::ClientInventory(quint16 new_max_weight)
  : max_weight{new_max_weight} {
}

ClientInventory::ClientInventory(const ClientInventory& other)
  : items{other.items},
    max_weight{other.max_weight},
    current_weight{other.current_weight},
    equipped{other.equipped} {
}

QList<Item*> ClientInventory::get_items(){
    return items;
}

quint16 ClientInventory::get_weight() const {
  return current_weight;
}

quint16 ClientInventory::get_max_weight() const {
  return max_weight;
}

QList<Item*> ClientInventory::get_equipped() const {
  return equipped;
}

bool ClientInventory::has_item(Item* item) const {
  return (std::find(items.begin(), items.end(), item) != items.end());
}

void ClientInventory::set_max_weight(quint16 new_max) {
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

QDataStream& ClientInventory::read_from_stream(QDataStream& ds) {

  int number_of_items{0};
  int number_of_equipped_items{0};

  ds >> number_of_items;
  Item* temp_item = new Item(0);

  for (int i{0}; i < number_of_items; ++i) {
      ds >> temp_item;
      items.push_back(new Item(*temp_item));
  }

  ds >> number_of_equipped_items;

  for (int i{0}; i < number_of_equipped_items; ++i) {
      ds >> temp_item;
      equipped.push_back(temp_item);
  }
  delete temp_item;
  ds >> max_weight;
  ds >> current_weight;
  return ds;
}

QDataStream& operator>>(QDataStream& ds, ClientInventory& inv) {
  return inv.read_from_stream(ds);
}
