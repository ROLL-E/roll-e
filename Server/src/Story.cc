#include "Story.h"
#include "Item.h"

using namespace std;

Story::Story(Ruleset& new_ruleset)
  : ruleset(new_ruleset) {
  myServer = new Server{};
}

void Story::add_character(Character* new_character) {
  characters.push_back(new_character);
}

void Story::add_scenario(Scenario* new_scenario) {
  current_scenarios.push_back(new_scenario);
}

void Story::add_item(Item* new_item) {
  items[new_item->get_id()] = new_item;
}

std::list<Character*> Story::get_characters() const {
  return characters;
}

Fight* Story::get_fight() const {
  return current_fight;
}

std::list<Scenario*> Story::get_scenarios()  const {
  return current_scenarios;
}

Ruleset& Story::get_ruleset() const {
  return ruleset;
}

std::map<int, Item*> Story::get_items() const {
  return items;
}

void Story::set_fight(Fight* new_fight) {
  current_fight = new_fight;
}

void Story::remove_character(Character* char_to_remove) {
  characters.remove(char_to_remove);
}

void Story::remove_scenario(Scenario* scenario_to_remove) {
  current_scenarios.remove(scenario_to_remove);
}

void Story::remove_item(int id_to_remove) {
  items.erase(id_to_remove);
}

