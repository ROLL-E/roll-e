#ifndef STORY_H
#define STORY_H
#include <QList>
#include <QMap>

class Item;
class Fight;
class Scenario;
class Character;
class Ruleset;
class ClientConnection;

class Story {

private:
  QList<Character*> characters;
  Fight* current_fight;
  QList<Scenario*> current_scenarios;
  Ruleset& ruleset;
  QMap<quint16, Item*> items;
  QList<ClientConnection*> clients;

public:
  QMap<quint16, Scenario*> scenario_id_map;

  Story(Ruleset&);

  void add_character(Character*);
  void add_scenario(Scenario*);
  void add_item(Item*);
  void add_clientconnection(ClientConnection*);

  QList<Character*>& get_characters();
  Fight* get_fight() const;
  QList<Scenario*> get_scenarios() const;
  Ruleset& get_ruleset() const;
  QMap<quint16, Item*> get_items() const;
  QList<ClientConnection*> get_clientconnections() const;

  void set_fight(Fight*);
  void set_items(QMap<quint16, Item*>);

  void remove_character(Character*);
  void remove_scenario(Scenario*);
  void remove_item(quint16);
  void remove_clientconnection(ClientConnection*);

};

#endif
