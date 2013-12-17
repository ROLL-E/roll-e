#ifndef VALUEBLOCK_H
#define VALUEBLOCK_H
#include "LogicBlock.h"

#include <QList>

#include <QString>
#include <QMap>
#include <algorithm>
#include <stdlib.h>

class Character;

class ValueBlock : public LogicBlock
{
private:
  QChar intention;
  int value{0};
  int sides{0};
  int number{0};
  QList<QString> attributes;
  QList<QString> applicable_skills;
  QList<int> applicable_items;
  Character* target;
  QMap<QString,bool> flags;
  
  int roll() const;
  int fetch_attribute(const QString&) const;
  int fetch_item_bonus(int) const;
  int fetch_skill_bonus(const QString&) const;
  int modify(int) const;
  
public:
  quint16 target_id;

  ValueBlock() = default;
  ValueBlock(ValueBlock&);

  LogicBlock* execute() override;
  void set_intention(QChar);
  void set_value(int);
  void set_sides(int);
  void set_number(int);
  void set_target(Character*);
  void set_flag(const QString&, bool);
  
  QChar get_intention() const;
  qint16 get_value() const;
  int get_sides() const;
  int get_number() const;
  QList<QString> get_attributes() const;
  QList<QString> get_applicable_skills() const;
  QList<int> get_applicable_items() const;
  Character* get_target() const;
  QMap<QString, bool> get_flags() const;
  
  void add_to_attributes(const QString&);
  void add_to_applicable_skills(const QString&);
  void add_to_applicable_items(int);
  
  void remove_attribute(const QString&);
  void remove_applicable_skill(const QString&);
  void remove_applicable_item(int);
  void remove_flag(const QString&);
  
  void populate_id_fields(QList<LogicBlock *> &, QList<Character *> &);
  void populate_pointer_fields(QList<LogicBlock *> &, QList<Character *> &);

  QDataStream& write_to_stream(QDataStream&);
  QDataStream& read_from_stream(QDataStream&);

};

//QDataStream& operator<<(QDataStream&, ValueBlock*&);
//QDataStream& operator>>(QDataStream&, ValueBlock*&);

#endif
