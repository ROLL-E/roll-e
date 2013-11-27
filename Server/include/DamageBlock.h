#ifndef DAMAGEBLOCK_H
#define DAMAGEBLOCK_H
#include "LogicBlock.h"
#include<string>

class DamageBlock : public LogicBlock
{
private:
  Character* target;
  std::string type;
public:
  DamageBlock() = default;
  DamageBlock(DamageBlock&);
  LogicBlock* execute() override;
  void set_target(Character*);
  Character* get_target() const;
};

#endif
