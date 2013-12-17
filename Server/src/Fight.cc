#include "Fight.h"
#include "Scenario.h"
using namespace std;

void Fight::add_character(Character* new_char) {
    list_of_characters.push_back(new_char);
    character_scenarios[new_char];
}

void Fight::remove_character(Character* character) {
    list_of_characters.removeOne(character);
    character_scenarios.remove(character);
}

void Fight::add_scenario(Character* character, Scenario* scenario) {
    character_scenarios[character].push_back(scenario);
}

void Fight::remove_scenario(Character* character, Scenario* scenario) {
    character_scenarios[character].removeOne(scenario);
}

void Fight::use_active(Scenario* scenario) {

    add_scenario(get_current_character(),scenario); //Adding scenario to current character.

    character_scenarios[get_current_character()].front()->wait_turns(scenario->find_turn_depth()); //Adding WaitBlocks to main scenario for the current character.
}

void Fight::run_next_turn() {
    QList<Scenario*> list_to_run = character_scenarios[get_current_character()];

    for (QList<Scenario*>::iterator it = list_to_run.begin(); it != list_to_run.end(); ++it) {
        if ((*it)->empty() && it != list_to_run.begin())
            character_scenarios[get_current_character()].erase(it);
        else if ((*it)->empty())
            throw runtime_error("Main scenario was empty when run_next_turn() in Fight was called");
        else
            (*it)->run();
    }
    if (current_character < list_of_characters.size() - 1)
        ++current_character;
    else
        current_character = 0;
}

//Will return true if the current character can make a move or not. (True will mean he has to decide what to do next)
bool Fight::current_char_can_make_move() const {
    return character_scenarios[get_current_character()].front()->empty();
}

void Fight::run_next_round() {
    for (uint16_t i{0}; i < list_of_characters.size(); ++i)
        run_next_turn();
}

Character* Fight::get_current_character() const{
    QList<Character*>::const_iterator it;
    it = list_of_characters.cbegin();
    advance(it,current_character);
    return *it;
}

