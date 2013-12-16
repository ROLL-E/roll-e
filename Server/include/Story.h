#ifndef STORY_H
#define STORY_H
#include "ClientConnection.h"
#include "Ruleset.h"
#include "Server.h"
#include <list>
#include <QMap>
#include <QThread>
#include <QObject>

class Item;
class Fight;
class Scenario;
class Character;

class Story : public QObject {

  Q_OBJECT

private:
    std::list<Character*> characters;
    Fight* current_fight;
    std::list<Scenario*> current_scenarios;
    Ruleset& ruleset;
    QMap<int, Item*> items;
    QThread* netThread;
    Server* myServer;
public:

    Story(Ruleset&);

    void add_character(Character*);
    void add_scenario(Scenario*);
    void add_item(Item*);

    std::list<Character*> get_characters() const; //when would this be used?
    Fight* get_fight() const;
    std::list<Scenario*> get_scenarios() const;
    Ruleset& get_ruleset() const;
    QMap<int, Item*> get_items() const;

    void set_fight(Fight*);
    void set_items(QMap<int, Item*>);

    void remove_character(Character*);
    void remove_scenario(Scenario*);
    void remove_item(int);
    void remove_clientconnection(QPointer<ClientConnection>);

signals:

public slots:

};

#endif
