#ifndef VALUEBLOCK_H
#define VALUEBLOCK_H
#include "LogicBlock.h"
#include "Character.h"
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include <stdlib.h>

class ValueBlock : public LogicBlock
{
private:
  char intention;
  int value;
  int sides;
  int number;
  std::list<std::string> attributes;
  std::list<std::string> applicable_skills;
  std::list<int> applicable_items;
  Character* target;
  std::map<std::string,bool> flags;
  
  int roll() const;
  int fetch_attribute(const std::string&) const;
  int fetch_item_bonus(int) const;
  int fetch_skill_bonus(const std::string&) const;
  int modify(int) const;
  
public:
  ValueBlock() = default;
  ValueBlock(ValueBlock&);

  LogicBlock* execute() override;
  void set_intention(char);
  void set_value(int);
  void set_sides(int);
  void set_number(int);
  void set_target(Character*);
  void set_flag(const std::string&, bool);
  
  char get_intention() const;
  int get_value() const;
  int get_sides() const;
  int get_number() const;
  std::list<std::string> get_attributes() const;
  std::list<std::string> get_applicable_skills() const;
  std::list<int> get_applicable_items() const;
  Character* get_target() const;
  std::map<std::string, bool> get_flags() const;
  
  void add_to_attributes(const std::string&);
  void add_to_applicable_skills(const std::string&);
  void add_to_applicable_items(int);
  
  void remove_attribute(const std::string&);
  void remove_applicable_skill(const std::string&);
  void remove_applicable_item(int);
  void remove_flag(const std::string&);
  
};

#endif
