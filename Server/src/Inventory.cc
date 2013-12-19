#include "Inventory.h"
#include <algorithm>
#include <stdexcept>
#include <QDebug>
#include <QFile>
#include "Story.h"
#include "Item.h"
using namespace std;

Inventory::Inventory(quint16 new_max_weight, Story* new_story)
  : max_weight{new_max_weight},
    current_weight{0},
    story{new_story}{
}

Inventory::Inventory(const Inventory& other)
  : items{other.items},
    max_weight{other.max_weight},
    current_weight{other.current_weight},
    equipped{other.equipped},
    story{other.story} {
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

QList<quint16> Inventory::get_items() const
{
  return items;
}

bool Inventory::has_item(quint16 id) const {
  return (find(items.begin(), items.end(), id) != items.end());
}

void Inventory::set_max_weight(quint16 new_max) {
  max_weight = new_max;
}

void Inventory::add_item(quint16 id_to_add) {
  Item* item{story->get_items().value(id_to_add, nullptr)};
  if (item == nullptr)
    throw out_of_range("Item does not exist");

  qint16 temp_weight{item->get_attributes().value("Weight",0x7fff)};
  if  (temp_weight != 0x7fff && current_weight + temp_weight > max_weight) {
      //TODO: add overweight handling
      qDebug() << "Can't add item " << id_to_add << ", overweight";
      return;

  } else
    current_weight += item->get_attributes().value("Weight");
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

  if (dynamic_cast<QFile*>(ds.device()) != nullptr){
      qDebug() << "Sending Item Id's";
      ds << items;
  }
  else {
    qDebug() << "sending items";
    ds << items.size();
    qDebug() << "Items.size()" << items.size();
    for (quint16 id : items) {
      ds << story->get_item(id);
    }
  }
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


