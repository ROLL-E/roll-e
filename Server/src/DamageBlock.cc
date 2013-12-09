#include "DamageBlock.h"
#include <iostream>

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
