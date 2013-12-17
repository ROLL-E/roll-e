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
  qint16 lhs_id;
  qint16 rhs_id;
  qint16 alternate_next_id;

  CompareBlock() = default;
  CompareBlock(CompareBlock&);
  LogicBlock* execute() override;
  void set_lhs(ValueBlock*);
  void set_rhs(ValueBlock*);
  ValueBlock* get_lhs() const;
  ValueBlock* get_rhs() const;
  void set_alternate(LogicBlock*);
  LogicBlock* get_alternate() const;

  void add_to_list(QList<LogicBlock *> &);
  void populate_id_fields(QList<LogicBlock *> &, QList<Character *> &);
  void populate_pointer_fields(QList<LogicBlock *> &, QList<Character *> &);

  QDataStream& write_to_stream(QDataStream&);
  QDataStream& read_from_stream(QDataStream&);
};


//QDataStream& operator<<(QDataStream&, CompareBlock*&);
//QDataStream& operator>>(QDataStream&, CompareBlock*&);


#endif
