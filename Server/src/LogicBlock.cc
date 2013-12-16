#include "LogicBlock.h"

LogicBlock::LogicBlock(LogicBlock& other) {
    last_block = other.last_block;
    next = other.next;
}

void LogicBlock::set_next(LogicBlock* new_block) {
    next = new_block;
}

void LogicBlock::set_last(bool new_value) {
    last_block = new_value;
}

LogicBlock* LogicBlock::get_next() {
    return next;
}

bool LogicBlock::get_last() const {
    return last_block;
}

LogicBlock* LogicBlock::get_self() {
    return this;
}

QDataStream& operator<<(QDataStream& ds, LogicBlock*& block) {
  return block->write_to_stream(ds);
}

QDataStream& operator>>(QDataStream& ds, LogicBlock*& block) {
  return block->read_from_stream(ds);
}

