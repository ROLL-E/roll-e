#include "serverwindow.h"
#include <QApplication>
#include <stdexcept>
#include <iostream>
#include <QDebug>
#include <QString>
#include <QMap>
#include <QFile>

#include "Story.h"
#include "GameSave.h"
#include "Character.h"
#include "Item.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ServerWindow w;

  std::list<std::string> attr_list{"health", "armor", "strength"};
  Ruleset rs(attr_list);

  Story main_story(rs);

  QMap<QString, qint16> attr_map{{"health", 10}, {"armor", 2}, {"strength", 5}};
  main_story.add_character(new Character(attr_map, 50, &main_story));

  Character* bob = main_story.get_characters().front();



  try {
    Item* hammer1 = new Item("Hammer of doom");
    main_story.add_item(hammer1);
    hammer1->set_attribute("Weight", 20);

    Item* hammer2 = new Item("nicer hammah");
    main_story.add_item(hammer2);
    hammer2->set_attribute("Weight", 20);

    bob->add_item(hammer1->get_id());
    bob->add_item(hammer2->get_id());





    qDebug() << "Bob's stuff:";
    for (auto item_id : bob->inventory.get_items()) {
      qDebug() << main_story.get_items().value(item_id)->get_name();
    }
  }
  catch (const std::out_of_range& e) {
    qDebug() << "out_of_range exception: " << e.what();
  }


//  main_story.get_items().value(0)->set_modifier("Strength", -7);
//  main_story.get_items().value(1)->set_modifier("Intelligence", -42);
//  main_story.get_items().value(0)->set_attribute("Damage", 1000);

//  qDebug() << "saving and loading! ";
//  GameSave::save(&main_story, "F:\\Projekt\\save.dat");
//  main_story.remove_item(0);
//  main_story.remove_item(1);

//  qDebug() << "saved";
//  GameSave::load("F:\\Projekt\\save.dat", &main_story);
//  qDebug() << "loaded";
//  for (auto item : main_story.get_items())  {
//    qDebug() << "id: " << item->get_id();
//    qDebug() << item->get_name();
//    for (auto key : item->get_modifiers().keys()) {
//      qDebug() << key << ": " << item->get_modifiers().value(key);
//    }
//    for (auto key : item->get_attributes().keys()) {
//      qDebug() << key << ": " << item->get_attributes().value(key);
//    }
//  }


  w.show();

  return a.exec();
}
