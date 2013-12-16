#include "Story.h"
#include "Item.h"

using namespace std;

Story::Story(Ruleset& new_ruleset) : ruleset(new_ruleset) {
  myServer = new Server;
  netThread = new QThread;
  myServer->moveToThread(netThread);
  // connect(worker,SIGNAL(error(QSTRING)),this,SLOT(errorString(QSTRING)));
  connect(myServer, SIGNAL(got_message()), myServer, SLOT(redirect_messages(this)));
  connect(myServer,SIGNAL(got_request()),myServer,SLOT(push_data(this)));
  connect(netThread, SIGNAL(started()), myServer, SLOT(start()));
  connect(myServer, SIGNAL(finished()), netThread, SLOT(quit()));
  connect(myServer, SIGNAL(finished()), myServer, SLOT(deleteLater()));
  connect(netThread, SIGNAL(finished()), netThread, SLOT(deleteLater()));
  // Start the networking
  netThread->start();
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

QList<Character *> Story::get_characters() const {
  return characters;
}

Character* Story::get_character(QString name){
    QList::const_iterator it = characters.cbegin();
    while((*it)->get_name() != name){
        it++;
        if(it = characters.cend()){
            throw(std::out_of_range("could not find receiver, this should be impossible."));
        }
    }
    return (*it);
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

QMap<int, Item*> Story::get_items() const {
  return items;
}

void Story::set_fight(Fight* new_fight) {
  current_fight = new_fight;
}

void Story::set_items(QMap<int, Item*> map) {
  items = map;
}

void Story::remove_character(Character* char_to_remove) {
  characters.remove(char_to_remove);
}

void Story::remove_scenario(Scenario* scenario_to_remove) {
  current_scenarios.remove(scenario_to_remove);
}

void Story::remove_item(int id_to_remove) {
  items.remove(id_to_remove);
}
