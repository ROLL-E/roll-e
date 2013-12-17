#ifndef WAITBLOCK_H
#define WAITBLOCK_H
#include "LogicBlock.h"

class WaitBlock : public LogicBlock
{
private:
  int wait_turns = 0;
  int wait_counter = 0;
public:
  WaitBlock() = default;
  WaitBlock(int turns) : wait_turns{turns} {};
  WaitBlock(WaitBlock&) = default;
  LogicBlock* execute() override;
  void set_wait_turns(int);
  int get_wait_turns() const;

  void populate_id_fields(QList<LogicBlock *> &, QList<Character *> &);
  void populate_pointer_fields(QList<LogicBlock *> &, QList<Character *> &);

  QDataStream& write_to_stream(QDataStream&);
  QDataStream& read_from_stream(QDataStream&);
};

//QDataStream& operator<<(QDataStream&, WaitBlock*&);
//QDataStream& operator>>(QDataStream&, WaitBlock*&);

#endif
