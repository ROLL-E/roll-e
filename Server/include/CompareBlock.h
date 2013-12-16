#ifndef COMPAREBLOCK_H
#define COMPAREBLOCK_H
#include "LogicBlock.h"

class ValueBlock;

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

  QDataStream& write_to_stream(QDataStream&);
  QDataStream& read_from_stream(QDataStream&);
};


//QDataStream& operator<<(QDataStream&, CompareBlock*&);
//QDataStream& operator>>(QDataStream&, CompareBlock*&);


#endif
