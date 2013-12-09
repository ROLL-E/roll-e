#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <map>
#include <list>
#include "Skill.h"

class Character {
private:
    std::string name;
    //ClientConnection* client;
    std::map<std::string, int> attributes;
    std::list<Skill*> skills;
    //Inventory inventory;
public:
    Character(std::map<std::string, int>);
    Character(Character&);
    std::string get_name() const;
    void set_name(std::string);
    int get_attribute(std::string) const;
    void set_attribute(std::string, int);
    void add_to_attributes(std::string, int) {};
    void take_damage(std::string, int) {};
    std::list<Skill*> get_skills() const;
    void add_skill(Skill*);
    void remove_skill(Skill*);
    void add_item(int);
    void remove_item(int);
    bool has_item(int) const;

};

#endif
