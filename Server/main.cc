#include "serverwindow.h"
#include <QApplication>
#include <stdexcept>
#include <iostream>
#include "Story.h"
#include "Character.h"
#include "Item.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ServerWindow w;

  std::list<std::string> attr_list{"health", "armor", "strength"};
  Ruleset rs(attr_list);

  Story main_story(rs);

  std::map<std::string, int> attr_map{{"health", 10}, {"armor", 2}, {"strength", 5}};
  main_story.add_character(new Character(attr_map, 50));

  Character* bob = main_story.get_characters().front();

  bob->set_name("Bob");
  std::cout << bob->get_name() << std::endl;

  std::cout << "bob's health" << bob->get_attribute("health") << std::endl;
  bob->take_damage("blunt", 3);
  std::cout << "bob's health after hit" << bob->get_attribute("health") << std::endl;

  try {
    main_story.add_item(new Item("Hammer of doom"));
    bob->add_item(0);
    main_story.add_item(new Item("nicer hammah"));
    bob->add_item(1);
    std::cout << std::boolalpha << bob->has_item(1) << " " << bob->has_item(2) << std::endl;
    std::cout << main_story.get_items().at(0)->get_name() << std::endl;
    std::cout << main_story.get_items().at(1)->get_name() << std::endl;

  }
  catch (const std::out_of_range& e) {
    std::cerr << "out_of_range exception: " << e.what() << std::endl;
  }

  w.show();

  return a.exec();
}
