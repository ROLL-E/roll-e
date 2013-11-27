#ifndef COMPAREBLOCK_H
#define COMPAREBLOCK_H
#include "LogicBlock.h"
#include "ValueBlock.h"

class CompareBlock : public LogicBlock
{
private:
  LogicBlock* alternate_next;
  ValueBlock* lhs_block;
  ValueBlock* rhs_block;
  
public:
  CompareBlock() = default;
  CompareBlock(CompareBlock&);
  LogicBlock* execute() override;
  void set_lhs(ValueBlock*);
  void set_rhs(ValueBlock*);
  ValueBlock* get_lhs() const;
  ValueBlock* get_rhs() const;
  void set_alternate(LogicBlock*);
  LogicBlock* get_alternate() const;
};

#endif
