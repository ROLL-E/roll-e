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
  quint16 target_id;
  quint16 valueblock_id;

  DamageBlock() = default;
  DamageBlock(DamageBlock&);
  ~DamageBlock() = default;

  LogicBlock* execute() override;
  void set_target(Character*);
  Character* get_target() const;
  void set_valueblock(ValueBlock*);
  ValueBlock* get_valueblock() const;
  void set_type(const QString&);

  void populate_id_fields(QList<LogicBlock *> &, QList<Character *> &);
  void populate_pointer_fields(QList<LogicBlock *> &, QList<Character *> &);

  QDataStream& write_to_stream(QDataStream&);
  QDataStream& read_from_stream(QDataStream&);
};


#endif
