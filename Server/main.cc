#include "serverwindow.h"
#include <QApplication>
#include <iostream>
#include <QDebug>
#include <QString>
#include <QMap>
#include <QFile>
#include <QDir>
#include <stdexcept>
#include "LogicBlock.h"
#include "ModifierBlock.h"
#include "WaitBlock.h"
#include "ValueBlock.h"
#include "DamageBlock.h"
#include "CompareBlock.h"
#include "Story.h"
#include "GameSave.h"
#include "Character.h"
#include "Item.h"
#include "Server.h"
#include "Fight.h"
#include "Ruleset.h"
#include "Scenario.h"
#include "Skill.h"

int main(int argc, char *argv[])
{

  QList<QString> attr_list{"health", "armor", "strength"};
  Ruleset* rs = new Ruleset(attr_list);

  Story* main_story = new Story(rs);

  QMap<QString, qint16> attr_map{{"health", 10}, {"armor", 2}, {"strength", 5}};
  main_story->add_character(new Character(attr_map, 100, main_story));

  qDebug() << "Creating Bob.";
  Character* bob = main_story->get_characters().front();
  bob->set_name("BOB!");

  try {
    Item* hammer1 = new Item("Hammer of doom");
    main_story->add_item(hammer1);
    hammer1->set_attribute("Weight", 20);

    Item* hammer2 = new Item("nicer hammah");
    main_story->add_item(hammer2);
    hammer2->set_attribute("Weight", 20);
    hammer2->set_modifier("str", -20);

    bob->add_item(hammer1->get_id());
    bob->add_item(hammer2->get_id());


    qDebug() << "Bob's stuff:";
    for (auto item_id : bob->inventory.get_items()) {
      qDebug() << main_story->get_items().value(item_id)->get_name();
    }
  }
  catch (const std::out_of_range& e) {
    qDebug() << "out_of_range exception: " << e.what();
  }

  Character* herman = new Character(attr_map, 10, main_story);
  main_story->add_character(herman);
  herman->set_name("Herr Man");

  rs->add_skill(new Skill("Break those cuffs"));
  rs->add_skill(new Skill("Eat horse"));
  rs->get_skills().at(0)->set_modifier("int", 10);
  rs->get_skills().at(0)->set_modifier("str", 11);
  rs->get_skills().at(1)->set_modifier("int" , 5);
  rs->get_skills().at(1)->set_modifier("str", 25);
  bob->add_skill(rs->get_skills().at(0));
  bob->add_skill(rs->get_skills().at(1));

  herman->add_skill(rs->get_skills().at(1));

//  qDebug() << "testing save-load";

//  GameSave* save = new GameSave();

//  qDebug() << "saving...";
//  save->save(main_story,"/home/olgittmar/Documents/TDDC76/roll-e/Savegames");
//  qDebug() << "loading...";
//  save->load("/home/olgittmar/Documents/TDDC76/roll-e/Savegames",main_story);

  QApplication a(argc, argv);
  ServerWindow w(main_story);
  
  w.show();
  return a.exec();
}
