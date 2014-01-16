#include "Story.h"
#include "Item.h"
#include "Server.h"
#include "Scenario.h"

Story::Story(Ruleset* new_ruleset) : ruleset(new_ruleset) {
}

void Story::startServer(){
    myServer = new Server{this};
    netThread = new QThread;
    myServer->moveToThread(netThread);
    // connect(worker,SIGNAL(error(QSTRING)),this,SLOT(errorString(QSTRING)));
    connect(netThread, SIGNAL(started()), myServer, SLOT(start()));
    connect(this,SIGNAL(serverStop()),myServer,SLOT(stopServer()));
    connect(myServer, SIGNAL(finished()), netThread, SLOT(quit()));
    connect(myServer, SIGNAL(finished()), myServer, SLOT(deleteLater()));
    connect(netThread, SIGNAL(finished()), netThread, SLOT(deleteLater()));
    // Start the networking
    netThread->start();
    netThread->wait(1000);
}

void Story::stopServer(){
    if(myServer != nullptr){
    emit serverStop();
    netThread->wait(3000);
    }
}

Story::~Story()
{
  emit serverStop();
  for (Character* c : characters)
    delete c;
  for (Scenario* scen : current_scenarios)
    delete scen;
  delete ruleset;
  for (quint16 key : items.keys())
    delete items.value(key);

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

QList<Character*>& Story::get_characters() {
  return characters;
}

Character* Story::get_character(QString name){
    QList<Character*>::const_iterator it = characters.cbegin();
    while((*it)->get_name() != name){
        it++;
        if(it == characters.cend()){
            qDebug() << "Character not found";
            return nullptr;
        }
    }
    return (*it);
}

Fight* Story::get_fight() const {
  return current_fight;
}

QList<Scenario*>& Story::get_scenarios() {
  return current_scenarios;
}

Ruleset *Story::get_ruleset() {
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

Item* Story::get_item(quint16 id) const {
    return items.value(id, nullptr);
}

