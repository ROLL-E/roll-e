#include "ValueBlock.h"
#include "Character.h"
#include <time.h>

using namespace std;

void ValueBlock::set_intention(QChar new_intention) {
  intention = new_intention;
}

QChar ValueBlock::get_intention() const {
  return intention;
}

void ValueBlock::set_value(int new_value) {
  value = new_value;
}

qint16 ValueBlock::get_value() const {
  return value;
}

void ValueBlock::set_sides(int new_sides) {
  sides = new_sides;
}

int ValueBlock::get_sides() const {
  return sides;
}

void ValueBlock::set_number(int new_number) {
  number = new_number;
}

int ValueBlock::get_number() const {
  return number;
}

void ValueBlock::set_target(Character* new_target) {
  target = new_target;
}

Character* ValueBlock::get_target() const {
  return target;
}

QList<QString> ValueBlock::get_attributes() const {
  return attributes;
}

void ValueBlock::add_to_attributes(const QString& new_attribute) {
  if (!attributes.contains(new_attribute))
    attributes.push_front(new_attribute);
  else
    throw logicblock_error("Attribute already exists");
}

void ValueBlock::remove_attribute(const QString& attribute) {
  if (attributes.contains(attribute))
    attributes.removeOne(attribute);
  else
    throw logicblock_error("Can't remove attriubte, it doesn't exist in the list");
}

QList<QString> ValueBlock::get_applicable_skills() const {
  return applicable_skills;
}

void ValueBlock::add_to_applicable_skills(const QString& name) {
  if (!applicable_skills.contains(name))
    applicable_skills.push_back(name);
  else
    throw logicblock_error("Skill already exsists");
}

void ValueBlock::remove_applicable_skill(const QString& name) {
  if (applicable_skills.contains(name))
    applicable_skills.removeOne(name);
  else
    throw logicblock_error("Can't remove skill, it doesn't exist in list");
}

QList<int> ValueBlock::get_applicable_items() const {
  return applicable_items;
}

void ValueBlock::add_to_applicable_items(int id) {
  if (!applicable_items.contains(id))
    applicable_items.push_back(id);
  else
    throw logicblock_error("Item alredy exists");
}

void ValueBlock::remove_applicable_item(int id) {
  if (applicable_items.contains(id))
    applicable_items.removeOne(id);
  else
    throw logicblock_error("Can't remove item, it doesn't exist in list");
}

QMap<QString, bool> ValueBlock::get_flags() const {
  return flags;
}

void ValueBlock::set_flag(const QString& name, bool value) {
  flags[name] = value;
}

void ValueBlock::remove_flag(const QString& name) {
  if (flags.contains(name))
    flags.remove(name);
  else
    throw logicblock_error("Can't remove flag, it doesn't exist");
}

void ValueBlock::populate_id_fields(QList<LogicBlock*>& blocks, QList<Character*>& chars) {
  next_id = blocks.indexOf(get_next());
  target_id = chars.indexOf(target);
  if (get_next() != nullptr)
    get_next()->populate_id_fields(blocks, chars);
}

void ValueBlock::populate_pointer_fields(QList<LogicBlock*>& blocks, QList<Character*>& chars) {
  set_next(blocks.value(next_id));
  set_target(chars.value(target_id));
  if (get_next() != nullptr) {
    get_next()->populate_pointer_fields(blocks, chars);
  }
}

int ValueBlock::roll() const {
  int temp{0};
  srand(time(NULL));
  for (int i{0}; i < number ; ++i)
    temp += (rand() % sides) + 1;
  return temp;
}


LogicBlock* ValueBlock::execute() {
  if (intention == 's')
    return this->get_next();
  else if (intention == 'r') {
    value = roll();
  }
  else if (intention == 'a') {
    QList<QString>::iterator it;
    for (it = attributes.begin(); it != attributes.end(); ++it)
      value += target->get_attribute(*it);
    value += roll();
  }
  return this->get_next(); //Not yet implemented
}

QDataStream& ValueBlock::write_to_stream(QDataStream & ds) {

  ds << next_id;
  ds << get_last();

  ds << intention;
  ds << value;
  ds << sides;
  ds << number;
  ds << attributes;
  ds << applicable_skills;
  ds << applicable_items;
  ds << target_id;
  ds << flags;

  return ds;
}

QDataStream& ValueBlock::read_from_stream(QDataStream & ds) {
  bool temp_last;

  ds >> next_id;
  ds >> temp_last;

  set_last(temp_last);

  ds >> intention;
  ds >> value;
  ds >> sides;
  ds >> number;
  ds >> attributes;
  ds >> applicable_skills;
  ds >> applicable_items;
  ds >> target_id;
  ds >> flags;

  return ds;
}
