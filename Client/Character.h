#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <list>

#include "Skill.h"
#include "Item.h"
#include "ServerConnection.h"
#include "ClientInventory.h"

class Character {
public:
  Character(std::map<std::string,int>);
  Character(const Character&);
  
  std::string get_name() const;
  void set_name(std::string);
  int get_attribute(std::string) const;
  void set_attribute(std::string, int);
  void add_to_attribute(std::string, int);
  void take_damage(std::string, int);
  std::list<Skill*> get_skills();
  void add_skill(Skill*);
  void remove_skill(Skill*);
  void add_item(int);
  void remove_item(int);
  bool has_item(int) const;
  
private:
  std::string name;
  ServerConnection* server;
  std::map<std::string, int> attributes;
  std::list<Skill*> skills;
  ClientInventory inventory;
  
};

#endif
