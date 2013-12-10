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
  main_story.add_character(new Character(attr_map, 50));

  Character* bob = main_story.get_characters().front();

  bob->set_name("Bob");
  qDebug() << bob->get_name();

  qDebug() << "bob's health" << bob->get_attribute("health");
  bob->take_damage("blunt", 3);
  qDebug() << "bob's health after hit" << bob->get_attribute("health");

try {
  main_story.add_item(new Item("Hammer of doom"));
  bob->add_item(0);
  main_story.add_item(new Item("nicer hammah"));
  bob->add_item(1);
  qDebug() << bob->has_item(1) << " " << bob->has_item(2);
  qDebug() << main_story.get_items().value(0)->get_name();
  qDebug() << main_story.get_items().value(1)->get_name();

  }


  catch (const std::out_of_range& e) {
    qDebug() << "out_of_range exception: " << e.what();
  }

  main_story.get_items().value(0)->set_modifier("Strength", -7);
  main_story.get_items().value(1)->set_modifier("Intelligence", -42);
  main_story.get_items().value(0)->set_attribute("Damage", 1000);

  qDebug() << "saving and loading! ";
  GameSave::save(&main_story, "F:\\Projekt\\save.dat");
  main_story.remove_item(0);
  main_story.remove_item(1);

  qDebug() << "saved";
  GameSave::load("F:\\Projekt\\save.dat", &main_story);
  qDebug() << "loaded";
  for (auto item : main_story.get_items())  {
    qDebug() << "id: " << item->get_id();
    qDebug() << item->get_name();
    for (auto key : item->get_modifiers().keys()) {
      qDebug() << key << ": " << item->get_modifiers().value(key);
    }
    for (auto key : item->get_attributes().keys()) {
      qDebug() << key << ": " << item->get_attributes().value(key);
    }
  }

  w.show();

  return a.exec();
}
