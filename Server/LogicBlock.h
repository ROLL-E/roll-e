#ifndef LOGICBLOCK_H
#define LOGICBLOCK_H

class LogicBlock
{
private:
  LogicBlock* next;
  bool last_block;
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
