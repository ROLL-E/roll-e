#ifndef LOGICBLOCK_H
#define LOGICBLOCK_H

class LogicBlock
{
private:
  LogicBlock* next = nullptr;
  bool last_block;
public:
  LogicBlock() = default;
  LogicBlock(LogicBlock&);

  virtual LogicBlock* execute() = 0;
  void set_next(LogicBlock*);
  LogicBlock* get_next();
  void set_last(bool);
  bool get_last() const;
  LogicBlock* get_self();
};

#endif
