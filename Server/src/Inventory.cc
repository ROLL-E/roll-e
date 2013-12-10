#include "Inventory.h"
#include <algorithm>

using namespace std;

Inventory::Inventory(quint16 new_max_weight)
  : max_weight{new_max_weight} {
}

Inventory::Inventory(const Inventory& other)
  : items{other.items},
    max_weight{other.max_weight},
    current_weight{other.current_weight},
    equipped{other.equipped} {
}

quint16 Inventory::get_weight() const {
  return current_weight;
}

quint16 Inventory::get_max_weight() const {
  return max_weight;
}

QList<quint16> Inventory::get_equipped() const {
  return equipped;
}

bool Inventory::has_item(quint16 id) const {
  return (find(items.begin(), items.end(), id) != items.end());
}

void Inventory::set_max_weight(quint16 new_max) {
  max_weight = new_max;
}

void Inventory::add_item(quint16 id_to_add) {
  items.push_back(id_to_add);
}

void Inventory::remove_item(quint16 id_to_remove) {
  items.removeOne(id_to_remove);
}

void Inventory::equip(quint16 id_to_equip){
  equipped.push_back(id_to_equip);
}

void Inventory::unequip(quint16 id_to_unequip) {
  equipped.removeOne(id_to_unequip);
}

QDataStream& Inventory::write_to_stream(QDataStream& ds) const {
  ds << items;
  ds << max_weight;
  ds << current_weight;
  ds << equipped;

  return ds;
}

QDataStream& Inventory::read_from_stream(QDataStream& ds) {
  ds >> items;
  ds >> max_weight;
  ds >> current_weight;
  ds >> equipped;

  return ds;
}

QDataStream& operator<<(QDataStream& ds, Inventory& inv) {
  return inv.write_to_stream(ds);
}

QDataStream& operator>>(QDataStream& ds, Inventory& inv) {
  return inv.read_from_stream(ds);
}


