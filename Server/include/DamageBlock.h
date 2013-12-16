#ifndef DAMAGEBLOCK_H
#define DAMAGEBLOCK_H
#include "LogicBlock.h"
#include <QString>

class ValueBlock;
class Character;

class DamageBlock : public LogicBlock
{
private:
  Character* target{nullptr};
  QString type;
  ValueBlock* valueblock{nullptr};
public:
  DamageBlock() = default;
  DamageBlock(DamageBlock&);
  LogicBlock* execute() override;
  void set_target(Character*);
  Character* get_target() const;
  void set_valueblock(ValueBlock*);
  ValueBlock* get_valueblock() const;

  QDataStream& write_to_stream(QDataStream&);
  QDataStream& read_from_stream(QDataStream&);
};

//QDataStream& operator<<(QDataStream&, DamageBlock*&);
//QDataStream& operator>>(QDataStream&, DamageBlock*&);

#endif
