#include "DamageBlock.h"
#include <iostream>
#include "Character.h"
#include "ValueBlock.h"

DamageBlock::DamageBlock(DamageBlock& other) {
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

LogicBlock* DamageBlock::execute() {
    if (target == nullptr || valueblock == nullptr)
        throw logicblock_error("Can't execute damageblock, need a target and a valueblock");
    else {
        target->take_damage(type, valueblock->get_value());
        return this->get_next();
    }
}

QDataStream& DamageBlock::write_to_stream(QDataStream& ds) {
  ds << get_next();
  ds << get_last();


  return ds;
}

QDataStream& DamageBlock::read_from_stream(QDataStream& ds) {
  LogicBlock* temp_next;
  bool temp_last;

  ds >> temp_next;
  ds >> temp_last;

  set_next(temp_next);
  set_last(temp_last);
  return ds;
}
/*
QDataStream& operator<<(QDataStream& ds, DamageBlock*& block) {
  return block->write_to_stream(ds);
}

QDataStream& operator>>(QDataStream& ds, DamageBlock*& block) {
  return block->read_from_stream(ds);
}*/
