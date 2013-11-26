#ifndef STORY_H
#define STROY_H
#include "Character.h"
#include "ClientConnection.h"
#include "Fight.h"
#include "Ruleset.h"
#include "Scenario.h"
#include "Item.h"
#include <list>

class Story {

private:
    std::list<Character*> characters;
    Fight* current_fight;
    std::list<Scenario*> current_scenarios;
    Ruleset& ruleset;
    std::list<Item*> items;
    std::list<ClientConnection*> clients;

public:
    Story() = default;
    Story(Story&);

    void add_character(Character*);
    void add_scenario(Scenario*);
    void add_item(Item*);
    void add_clientconnection(ClientConnection*);

    std::list<Character*> get_characters() const;
    Fight* get_fight() const;
    std::list<Scenario*> get_scenarios() const;
    Ruleset& get_ruleset() const;
    std::list<Item*> get_items() const;
    std::list<ClientConnection*> get_clientconnections() const;

    void set_fight(Fight*);

    void remove_character(Character*);
    void remove_scenario(Scenario*);
    void remove_item(Item*);
    void remove_clientconnection(ClientConnection*);

};

#endif