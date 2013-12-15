#include "Fight.h"

using namespace std;

void Fight::add_character(Character* new_char) {
    list_of_characters.push_back(new_char);
    character_scenarios[new_char];
}

void Fight::remove_character(Character* character) {
    list_of_characters.remove(character);
    character_scenarios.erase(character);
}

void Fight::add_scenario(Character* character, Scenario* scenario) {
    character_scenarios.at(character).push_back(scenario);
}

void Fight::remove_scenario(Character* character, Scenario* scenario) {
    character_scenarios.at(character).remove(scenario);
}

void Fight::use_active(Scenario* scenario) {
    list<Character*>::iterator it;
    it = list_of_characters.begin();
    advance(it,current_character);

    add_scenario(*it,scenario); //Adding scenario to current character.

    character_scenarios.at(*it).front()->wait_turns(scenario->find_turn_depth()); //Adding WaitBlocks to main scenario for the current character.
}


void Fight::run_next_turn() {
    list<Character*>::iterator it;
    it = list_of_characters.begin();
    advance(it,current_character);

    list<Scenario*> list_to_run = character_scenarios.at(*it);

    for_each (list_to_run.begin(), list_to_run.end(), run);


}

