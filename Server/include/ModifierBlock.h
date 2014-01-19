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
  quint16 target_id;
  quint16 previous_mod_id;

  ModifierBlock() = default;
  ModifierBlock(ModifierBlock&);
  ~ModifierBlock() = default;

  LogicBlock* execute() override;
  void set_target(Character*);
  Character* get_target() const;
  QMap<QString,qint8> get_modifiers() const;
  qint8 get_modifier(const QString&) const;
  void remove_modifier(QString);
  void set_modifier(QString,qint8);

  void set_previous_modifier(ModifierBlock*);
  ModifierBlock* get_previous_modifer() const;

  void populate_id_fields(QList<LogicBlock *> &, QList<Character *> &);
  void populate_pointer_fields(QList<LogicBlock *> &, QList<Character *> &);

  QDataStream& write_to_stream(QDataStream&);
  QDataStream& read_from_stream(QDataStream&);
};

#endif
