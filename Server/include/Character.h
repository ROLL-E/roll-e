#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <map>
#include <list>
#include "Skill.h"
#include "ClientConnection.h"
#include "Inventory.h"

class Character {
private:
    QString name;
    QPointer<ClientConnection> client;
    std::map<std::string, int> attributes;
    std::list<Skill*> skills;


public:
    Inventory inventory;
    Character(std::map<std::string, int>, int);
    Character(const Character&);
    QString get_name() const;
    void set_name(const QString &);
    int get_attribute(std::string) const;

    void add_to_attribute(const std::string&, int);
    void set_attribute(const std::string&, int);
    void take_damage(const std::string&, int);

    std::list<Skill*> get_skills() const;
    void add_skill(Skill*);
    void remove_skill(Skill*);
    void add_item(int);
    void remove_item(int);
    bool has_item(int) const;

};

#endif
