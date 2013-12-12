#include "Story.h"
#include "Item.h"

using namespace std;

Story::Story(Ruleset& new_ruleset)
  : ruleset(new_ruleset) {
}

void Story::add_character(Character* new_character) {
  characters.append(new_character);
}

void Story::add_scenario(Scenario* new_scenario) {
  current_scenarios.append(new_scenario);
}

void Story::add_item(Item* new_item) {
  items.insert(new_item->get_id(), new_item);
}

QList<Character*> Story::get_characters() const {
  return characters;
}

Fight* Story::get_fight() const {
  return current_fight;
}

QList<Scenario*> Story::get_scenarios()  const {
  return current_scenarios;
}

Ruleset& Story::get_ruleset() const {
  return ruleset;
}

QMap<quint16, Item*> Story::get_items() const {
  return items;
}

void Story::set_fight(Fight* new_fight) {
  current_fight = new_fight;
}

void Story::set_items(QMap<quint16, Item*> map) {
  items = map;
}

void Story::remove_character(Character* char_to_remove) {
  characters.removeOne(char_to_remove);
}

void Story::remove_scenario(Scenario* scenario_to_remove) {
  current_scenarios.removeOne(scenario_to_remove);
}

void Story::remove_item(quint16 id_to_remove) {
  items.remove(id_to_remove);
}


