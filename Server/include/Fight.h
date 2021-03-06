#ifndef FIGHT_H
#define FIGHT_H
#include "Character.h"
#include <QList>
#include <QMap>


class Scenario;

class Fight {
private:
    QList<Character*> list_of_characters;
    QMap<Character*, QList<Scenario*>> character_scenarios;
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
    bool current_char_can_make_move() const;
    Character* get_current_character() const;
    QList<Character*> get_characters() const;
};

#endif
