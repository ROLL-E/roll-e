#ifndef STORY_H
#define STORY_H
#include "ClientConnection.h"
#include "Ruleset.h"
#include "Server.h"
#include "Character.h"
#include <QThread>
#include <QObject>
#include <QList>
#include <QMap>
#include "Ruleset.h"

class Item;
class Fight;
class Scenario;
class Character;
class Server;
class Ruleset;

class Story {

private:
  QList<Character*> characters;
  Fight* current_fight;
  QList<Scenario*> current_scenarios;
  Ruleset* ruleset;
  QMap<quint16, Item*> items;
  QThread* netThread;

public:
  Server* myServer;
  QMap<quint16, Scenario*> scenario_id_map;
  Story(Ruleset*);

  void add_character(Character*);
  void add_scenario(Scenario*);
  void add_item(Item*);

  QList<Character*>& get_characters();
  Character* get_character(QString);
  Fight* get_fight() const;
  QList<Scenario*>& get_scenarios();
  Ruleset* get_ruleset();
  QMap<quint16, Item*> get_items() const;
  Item* get_item(quint16) const;

  void set_fight(Fight*);
  void set_items(QMap<quint16, Item*>);

  void remove_character(Character*);
  void remove_scenario(Scenario*);
  void remove_item(quint16);


};

#endif
