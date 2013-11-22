#ifndef MODIFIERBLOCK_H
#define MODIFIERBLOCK_H
#include "LogicBlock.h"
#include <string>

class ModifierBlock : public LogicBlock
{
private:
  std::map<string.int> modifiers;
  Charcter* target;
  ModifierBlock* previous_modifier;
public:
  ModifierBlock() = default,
  ModifierBlock(ModifierBlock&);
  LogicBlock* execute() const;
  void set_target(Character*);
  Character* get_target() const;
  std::map<std::string,int> get_modifiers() const;
  void remove_modifier(std::string);
  void set_modifier(std::string,int);
};

#endif