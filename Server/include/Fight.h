#ifndef FIGHT_H
#define FIGHT_H
#include "Character.h"
#include "Scenario.h"
#include <list>
#include <map>

class Scenario;

class Fight {
private:
    std::list<Character*> list_of_characters;
    std::map<Character*, std::list<Scenario*>> character_scenarios;
    uint16_t current_character{0};


    bool run_next_scenario() const; //Don't this is going to be needed.

public:
    void run_next_round();
    void run_next_turn();
    void use_active(Scenario*);
    void add_character(Character*);
    void remove_character(Character*);
    void add_scenario(Character*, Scenario*);
    void remove_scenario(Character* , Scenario*);
    Character* get_current_character() const;
};

#endif
