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
  WaitBlock(WaitBlock&) = default;
  LogicBlock* execute() override;
  void set_wait_turns(int);
  int get_wait_turns() const;
};

#endif
