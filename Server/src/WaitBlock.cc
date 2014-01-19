#include "WaitBlock.h"

void WaitBlock::set_wait_turns(int new_number) {
    wait_turns = new_number;
}

int WaitBlock::get_wait_turns() const {
  return wait_turns;
}

void WaitBlock::populate_id_fields(QList<LogicBlock*>& blocks, QList<Character*>& chars) {
  next_id = blocks.indexOf(get_next());
  if (get_next() != nullptr)
    get_next()->populate_id_fields(blocks, chars);
}

void WaitBlock::populate_pointer_fields(QList<LogicBlock*>& blocks, QList<Character*>& chars) {
  set_next(blocks.value(next_id));
  if (get_next() != nullptr) {
    get_next()->populate_pointer_fields(blocks, chars);
  }
}

LogicBlock* WaitBlock::execute() {

    if (wait_counter == wait_turns - 1)
        return this->get_next();
    else
        wait_counter++;
    return this;
}

QDataStream& WaitBlock::write_to_stream(QDataStream & ds) {
  ds << next_id;
  ds << wait_turns;
  ds << wait_counter;

  return ds;
}

QDataStream& WaitBlock::read_from_stream(QDataStream & ds) {
  ds >> next_id;
  ds >> wait_turns;
  ds >> wait_counter;

  return ds;
}
