#ifndef DAMAGEBLOCK_H
#define DAMAGEBLOCK_H
#include "LogicBlock.h"
#include "ValueBlock.h"
#include<string>

class DamageBlock : public LogicBlock
{
private:
  Character* target{nullptr};
  std::string type;
  ValueBlock* valueblock{nullptr};
public:
  DamageBlock() = default;
  DamageBlock(DamageBlock&);
  LogicBlock* execute() override;
  void set_target(Character*);
  Character* get_target() const;
  void set_valueblock(ValueBlock*);
  ValueBlock* get_valueblock() const;
};

#endif
