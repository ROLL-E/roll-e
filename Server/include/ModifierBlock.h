#ifndef MODIFIERBLOCK_H
#define MODIFIERBLOCK_H
#include "LogicBlock.h"
#include "Character.h"
#include <string>
#include <map>

class ModifierBlock : public LogicBlock
{
private:
  std::map<std::string, int> modifiers;
  Character* target;
  ModifierBlock* previous_modifier;
public:
  ModifierBlock() = default;
  ModifierBlock(ModifierBlock&);
  LogicBlock* execute() override;
  void set_target(Character*);
  Character* get_target() const;
  std::map<std::string,int> get_modifiers() const;
  void remove_modifier(std::string);
  void set_modifier(std::string,int);
};

#endif
