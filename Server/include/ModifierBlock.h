#ifndef MODIFIERBLOCK_H
#define MODIFIERBLOCK_H
#include "LogicBlock.h"
#include <QString>
#include <QMap>

class Character;

class ModifierBlock : public LogicBlock
{
private:
  QMap<QString, qint8> modifiers;
  Character* target;
  ModifierBlock* previous_modifier;
public:
  ModifierBlock() = default;
  ModifierBlock(ModifierBlock&);
  LogicBlock* execute() override;
  void set_target(Character*);
  Character* get_target() const;
  QMap<QString,qint8> get_modifiers() const;
  void remove_modifier(QString);
  void set_modifier(QString,int);
};

#endif
