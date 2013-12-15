#ifndef FIGHT_H
#define FIGHT_H
#include "Character.h"
#include "Scenario.h"
#include <list>
#include <map>

class Fight {
private:
    std::list<Character*> list_of_characters;
    std::map<Character*, std::list<Scenario*>> character_scenarios;
    int current_character{0};


    bool run_next_scenario() const;

public:
    void run_next_round();
    void run_next_turn();
    void use_active(Scenario*);
    void add_character(Character*);
    void remove_character(Character*);
    void add_scenario(Character*, Scenario*);
    void remove_scenario(Character* , Scenario*);
};

#endif
