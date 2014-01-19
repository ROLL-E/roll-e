#include "DamageBlock.h"
#include <iostream>
#include "Character.h"
#include "ValueBlock.h"

DamageBlock::DamageBlock(DamageBlock& other) : LogicBlock(){
    target = other.target;
    valueblock = other.valueblock;
    type = other.type;
}

void DamageBlock::set_target(Character* new_target) {
    target = new_target;
}

Character* DamageBlock::get_target() const {
    return target;
}

void DamageBlock::set_valueblock(ValueBlock* new_block) {
    valueblock = new_block;
}

ValueBlock* DamageBlock::get_valueblock() const {
  return valueblock;
}

void DamageBlock::set_type(const QString& new_type) {
  type = new_type;
}

void DamageBlock::populate_id_fields(QList<LogicBlock*>& blocks, QList<Character*>& chars) {
  next_id = blocks.indexOf(get_next());
  target_id = chars.indexOf(target);
  valueblock_id = blocks.indexOf(valueblock);
  if (get_next() != nullptr)
    get_next()->populate_id_fields(blocks,chars);
}

void DamageBlock::populate_pointer_fields(QList<LogicBlock*>& blocks, QList<Character*>& chars) {
  set_next(blocks.value(next_id));
  set_target(chars.value(target_id));
  set_valueblock(dynamic_cast<ValueBlock*>(blocks.value(valueblock_id)));
  if (get_next() != nullptr) {
    get_next()->populate_pointer_fields(blocks, chars);
  }
}

LogicBlock* DamageBlock::execute() {
    if (target == nullptr || valueblock == nullptr)
        throw logicblock_error("Can't execute damageblock, need a target and a valueblock");
    else {
        target->take_damage(type, valueblock->get_value());
        return this->get_next();
    }
}

QDataStream& DamageBlock::write_to_stream(QDataStream& ds) {
  ds << next_id;
  ds << get_last();

  ds << type;
  ds << target_id;
  ds << valueblock_id;

  return ds;
}

QDataStream& DamageBlock::read_from_stream(QDataStream& ds) {
  bool temp_last;

  ds >> next_id;
  ds >> temp_last;

  set_last(temp_last);

  ds >> type;
  ds >> target_id;
  ds >> valueblock_id;

  return ds;
}

