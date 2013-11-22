#ifndef LOGICBLOCK_H
#define LOGICBLOCK_H
#include "Character.h"

class LogicBlock
{
private:
  LogicBlock* next;
  LogicBlock* last_block;
public:
  LogicBlock() = default;
  LogicBlock(LogicBlock&);
  LogicBlock* execute() const;
  void set_next(LogicBlock*);
  LogicBlock* get_next();
  void set_last(bool);
  bool get_last() const;
};

#endif
