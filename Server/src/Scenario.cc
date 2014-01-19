#include "Scenario.h"
#include <QDebug>
#include <stdexcept>
#include "Story.h"
#include "CompareBlock.h"
#include "DamageBlock.h"
#include "ModifierBlock.h"
#include "LogicBlock.h"
#include "ValueBlock.h"
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

void Scenario::set_story(Story* story){
  parent_story = story;
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

bool Scenario::empty() const {
    return (next_block == nullptr);
}

QString Scenario::get_name()
{
    return name;
}

void Scenario::set_name(QString new_name) {
    name = new_name;
}

QDataStream& Scenario::write_to_stream(QDataStream& ds) {


  ds << description;
  ds << head_id;
  ds << next_block_id;
  ds << current_flags;


  for (LogicBlock* current_block : all_blocks) {
    ds << QString("Block");

    if (dynamic_cast<CompareBlock*>(current_block) != nullptr)
      ds << QChar('c');
    else if (dynamic_cast<DamageBlock*>(current_block) != nullptr)
      ds << QChar('d');
    else if (dynamic_cast<ModifierBlock*>(current_block) != nullptr)
      ds << QChar('m');
    else if (dynamic_cast<ValueBlock*>(current_block) != nullptr)
      ds << QChar('v');
    else if (dynamic_cast<WaitBlock*>(current_block) != nullptr)
      ds << QChar('w');

    ds << current_block;
  }
  ds << QString("End_Block");

  return ds;
}

QDataStream& Scenario::read_from_stream(QDataStream& ds) {
  all_blocks.clear();
  ds >> description;
  ds >> head_id;
  ds >> next_block_id;
  ds >> current_flags;

  LogicBlock* current_block;
  QChar current_type;
  QString tag;

  ds >> tag;
  while (tag != QString("End_Block")){
    ds >> current_type;
    switch (current_type.toLatin1()) {
    case 'c':
      current_block = new CompareBlock();
      ds >> current_block;
      break;
    case 'd':
      current_block = new DamageBlock();
      ds >> current_block;
      break;
    case 'm':
      current_block = new ModifierBlock();
      ds >> current_block;
      break;
    case 'v':
      current_block = new ValueBlock();
      ds >> current_block;
      break;
    case 'w':
      current_block = new WaitBlock();
      ds >> current_block;
      break;
    default:
      throw logicblock_error("Invalid block type in input stream");
    }
    all_blocks.append(current_block);
    ds >> tag;
  }




  return ds;
}

QDataStream& operator<<(QDataStream& ds, Scenario*& scenario) {
  return scenario->write_to_stream(ds);
}

QDataStream& operator>>(QDataStream& ds, Scenario*& scenario) {
  return scenario->read_from_stream(ds);
}
