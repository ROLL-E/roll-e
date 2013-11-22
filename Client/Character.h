#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include "Skill.h"
#include "Item.h"
#include "ClientConnection.h"

class Character {
public:
  Character(std::map<std::string,int>);
  Character(const Character&);
  
  std::string get_name();
  void set_name(std::string);
  int get_attribute(std::string);
  void set_attribute(std::string, int);
  void add_to_attribute(std::string, int);
  void take_damage(std::string, int);
  std::list<Skill*> get_skills();
  void add_skill(Skill*);
  void remove_skill(Skill*);
  void add_item(int);
  void remove_item(int);
  bool has_item(int);
  
private:
  std::string name;
  ClientConnection* client;
  std::map<std::string, int> attributes;
  std::list<Skill*> skills;
  Inventory inventory;
  
}