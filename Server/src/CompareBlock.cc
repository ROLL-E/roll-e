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

void CompareBlock::add_to_list(QList<LogicBlock*>& blocks) {
  blocks.append(this);
  if (get_next() != nullptr){
    get_next()->add_to_list(blocks);
    alternate_next->add_to_list(blocks);
  }
}

void CompareBlock::populate_id_fields(QList<LogicBlock*>& blocks, QList<Character*>& chars){
  next_id = blocks.indexOf(get_next());
  lhs_id = blocks.indexOf(lhs_block);
  rhs_id = blocks.indexOf(rhs_block);
  alternate_next_id = blocks.indexOf(alternate_next);
  if (get_next() != nullptr) {
    get_next()->populate_id_fields(blocks, chars);
    alternate_next->populate_id_fields(blocks, chars);
  }
}

void CompareBlock::populate_pointer_fields(QList<LogicBlock*>& blocks, QList<Character*>& chars) {
  set_next(blocks.value(next_id));
  set_lhs(dynamic_cast<ValueBlock*>(blocks.value(lhs_id)));
  set_rhs(dynamic_cast<ValueBlock*>(blocks.value(rhs_id)));
  set_alternate(blocks.value(alternate_next_id));
  if (get_next() != nullptr) {
    get_next()->populate_pointer_fields(blocks, chars);
    alternate_next->populate_pointer_fields(blocks, chars);
  }
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
  ds << next_id;
  ds << get_last();

  ds << alternate_next_id;
  ds << lhs_id;
  ds << rhs_id;
  return ds;
}

QDataStream& CompareBlock::read_from_stream(QDataStream& ds) {
  bool temp_last;

  ds >> next_id;
  ds >> temp_last;

  set_last(temp_last);

  ds >> alternate_next_id;
  ds >> lhs_id;
  ds >> rhs_id;
  return ds;
}

//QDataStream& operator<<(QDataStream& ds, CompareBlock*& block) {
//  return block->write_to_stream(ds);
//}

//QDataStream& operator>>(QDataStream& ds, CompareBlock*& block) {
//  return block->read_from_stream(ds);
//}
