#include "Scenario.h"
#include <QDebug>
#include "WaitBlock.h"

using namespace std;

void Scenario::set_flag(const QString& name, bool value) {
    current_flags[name] = value;
}

QMap<QString,bool> Scenario::get_flags() const {
    return current_flags;
}

bool Scenario::get_flag(const QString& name) const {
  return current_flags.value(name, false);
}


void Scenario::set_head(LogicBlock* new_head) {
    head = new_head;
}

LogicBlock* Scenario::get_head() const {
    return head;
}

int Scenario::find_turn_depth() const { //Will only count one of the possible routes if the tree has CompareBlocks.
    int depth{0};
    LogicBlock* next_block{head};
    while (next_block != nullptr) {
        if (next_block->get_last())
            ++depth;
        next_block = next_block->get_next();
    }
    return depth;
}

void Scenario::wait_turns(int turns) {
    LogicBlock* old_next{next_block};
    next_block = new WaitBlock(turns);
    next_block->set_next(old_next);
}

void Scenario::set_next_block(LogicBlock* new_next) {
    next_block = new_next;
}

LogicBlock* Scenario::get_next_block() const {
    return next_block;
}

void Scenario::run() {
    bool cont{false};
    if (next_block == nullptr)
        throw logicblock_error("Can't run scenario, it dosen't have any blocks");
    do {
        cont = !next_block->get_last();
        next_block = next_block->execute();
    } while (cont && next_block != nullptr);
}

QDataStream& Scenario::write_to_stream(QDataStream& ds) {
  ds << description;
  ds << head_id;
  ds << next_block_id;
  ds << current_flags;

  return ds;
}

QDataStream& Scenario::read_from_stream(QDataStream& ds) {
  ds >> description;
  ds >> head_id;
  ds >> next_block_id;
  ds >> current_flags;

  return ds;
}

QDataStream& operator<<(QDataStream& ds, Scenario*& scenario) {
  return scenario->write_to_stream(ds);
}

QDataStream& operator>>(QDataStream& ds, Scenario*& scenario) {
  return scenario->read_from_stream(ds);
}
