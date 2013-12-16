#include "CompareBlock.h"
#include "ValueBlock.h"

void CompareBlock::set_lhs(ValueBlock* new_lhs) {
    lhs_block = new_lhs;
}

void CompareBlock::set_rhs(ValueBlock* new_rhs) {
    rhs_block = new_rhs;
}

ValueBlock* CompareBlock::get_lhs() const {
    return lhs_block;
}

ValueBlock* CompareBlock::get_rhs() const {
    return rhs_block;
}

void CompareBlock::set_alternate(LogicBlock* new_alternate) {
    alternate_next = new_alternate;
}

LogicBlock* CompareBlock::get_alternate() const {
    return alternate_next;
}

LogicBlock* CompareBlock::execute() {
    if (lhs_block == nullptr || rhs_block == nullptr || alternate_next == nullptr)
        throw logicblock_error("Must have a lhs, rhs and a alternate next");
    else if (lhs_block->get_value() < rhs_block->get_value())
        return this->get_next();
    else
        return alternate_next;
}

QDataStream& CompareBlock::write_to_stream(QDataStream& ds) {
  ds << get_next();
  ds << get_last();

  ds << alternate_next;
  ds << lhs_block;
  ds << rhs_block;
  return ds;
}

QDataStream& CompareBlock::read_from_stream(QDataStream& ds) {
  LogicBlock* temp_next;
  bool temp_last;

  ds >> temp_next;
  ds >> temp_last;

  set_next(temp_next);
  set_last(temp_last);

  //ds >> alternate_next;
  //ds >> lhs_block;
  //ds >> rhs_block;
  return ds;
}

//QDataStream& operator<<(QDataStream& ds, CompareBlock*& block) {
//  return block->write_to_stream(ds);
//}

//QDataStream& operator>>(QDataStream& ds, CompareBlock*& block) {
//  return block->read_from_stream(ds);
//}
