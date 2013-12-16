#include "serverwindow.h"
#include <QApplication>
#include <iostream>
#include "LogicBlock.h"
#include "ModifierBlock.h"
#include "WaitBlock.h"
#include "ValueBlock.h"
#include "DamageBlock.h"
#include "CompareBlock.h"
#include <stdexcept>
#include <QDebug>
#include <QString>
#include "Story.h"
#include "GameSave.h"
#include "Character.h"
#include "Item.h"
#include "Fight.h"
#include "Server.h"

using namespace std;



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
    qDebug() << bob->has_item(1) << " " << bob->has_item(2);
    qDebug() << main_story.get_items().value(0)->get_name();
    qDebug() << main_story.get_items().value(1)->get_name();


  }
  catch (const std::out_of_range& e) {
    std::cerr << "out_of_range exception: " << e.what() << std::endl;
  }

  /*GameSave::save(&main_story, "F:\\Projekt\\save.dat");
  main_story.remove_item(0);

  GameSave::load("F:\\Projekt\\save.dat", &main_story);*/

  for (auto item : main_story.get_items())  {
    qDebug() << item->get_id();
    qDebug() << item->get_name();
    qDebug() << "End_Item";
  }
  //std::cout << main_story.get_items().value(0)->get_name().toStdString() <<std::endl;

  WaitBlock* block1(new WaitBlock);

 // ModifierBlock* block2(new ModifierBlock);

  LogicBlock* next_block;

  block1->set_wait_turns(2);
  next_block = block1;

  do {
      cout << "väntar" << endl;
      next_block = next_block->execute();
  }
  while(next_block != nullptr);

  ValueBlock* block3(new ValueBlock);

try {
      block3->add_to_attributes("first");
      block3->add_to_attributes("second");
      block3->add_to_attributes("first");
  }
  catch (const exception& e) {
      cout << e.what() << endl;
  }

  try {
        block3->add_to_applicable_skills("first");
        block3->add_to_applicable_skills("second");
        block3->add_to_applicable_skills("first");
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
  try {
        block3->add_to_applicable_items(1);
        block3->add_to_applicable_items(2);
        block3->add_to_applicable_items(1);
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

  list<int> new_list = block3->get_applicable_items();

  for (list<int>::iterator it = new_list.begin(); it != new_list.end(); ++it)
      cout << *it << endl;

  block3->remove_applicable_item(2);

  try {
      block3->remove_applicable_item(2);
  }
  catch (const exception& e) {
      cout << e.what() << endl;
  }

  list<int> new_list2 = block3->get_applicable_items();

  for (list<int>::iterator it = new_list2.begin(); it != new_list2.end(); ++it)
      cout << *it << endl;

  DamageBlock* block4(new DamageBlock);

  cout << "DamageBlock test" << endl;

  block4->set_valueblock(block3);

  try {
    block4->execute();
  }

  catch (const exception& e) {
      cout << e.what() << endl;
  }

  cout << "CompareBlock test" << endl;

  CompareBlock* block5(new CompareBlock);
  ValueBlock* block6(new ValueBlock);
  ValueBlock* block7(new ValueBlock);

  block6->set_value(5);
  block7->set_value(4);
  block5->set_lhs(block6);
  block5->set_rhs(block7);

  block5->set_alternate(block4);

  block5->set_next(block1);

  ModifierBlock* block8(new ModifierBlock);

  block8->set_next(block5->execute());

  if (dynamic_cast<DamageBlock*>(block8->get_next()) == nullptr)
      cout << "Inte ett DamageBlock" << endl;

  if (dynamic_cast<WaitBlock*>(block8->get_next()) == nullptr)
      cout << "Inte ett WaitBlock" << endl;

  //Take damage test
  ValueBlock* block10(new ValueBlock);
  DamageBlock* block11(new DamageBlock);

  block10->set_value(2);
  block11->set_valueblock(block10);
  block11->set_target(bob);

  cout << "Bobs current health: " << bob->get_attribute("health") << endl;
  cout << "Damage to bob: " << block10->get_value() << endl;
  block11->execute();
  cout << "Bobs current health: " << bob->get_attribute("health") << endl;


  ModifierBlock* block12(new ModifierBlock);

  block12->set_target(bob);
  block12->set_modifier("strength",2);
  block12->set_modifier("armor", -1);

  cout << "Bobs strength: " << bob->get_attribute("strength") << endl;
  cout << "Bobs armor: " << bob->get_attribute("armor") << endl;
  block12->execute();
  cout << "Bobs strength: " << bob->get_attribute("strength") << endl;
  cout << "Bobs armor: " << bob->get_attribute("armor") << endl;


  cout << "Testing ValueBlock" << endl;

  ValueBlock* block13(new ValueBlock);
  block13->set_number(1);
  block13->set_sides(10);
  block13->set_intention('a');
  block13->set_target(bob);
  block13->add_to_attributes("health");
  block13->execute();
  cout << "Health + random is: " << block13->get_value() << endl;


  cout << "Testing Scenario" << endl;

  Scenario* scenario1(new Scenario);

  scenario1->set_flag("blunt", true);
  scenario1->set_flag("critical", false);

  cout << "Blunt? " << scenario1->get_flag("blunt") << endl;
  cout << "Critical? " << scenario1->get_flag("critical") << endl;
  cout << "Random? " << scenario1->get_flag("random") << endl;

  scenario1->set_head(block10);
  scenario1->set_next_block(block10);
  block10->set_next(block11);
  block11->set_next(block12);
  block12->set_next(block13);
  block10->set_last(false);
  block11->set_last(true);
  block12->set_last(true);
  block13->set_last(false);

  cout << "Depth: " << scenario1->find_turn_depth() << endl;


  qDebug() <<  (bob->get_attribute("health") == 7) << endl;
  scenario1->run();
  qDebug() << (bob->get_attribute("health") == 5) << endl;
  qDebug() << (bob->get_attribute("strength") == 7) << endl;
  qDebug() << (bob->get_attribute("armor") == 1) << endl;
  scenario1->run();
  qDebug() << (bob->get_attribute("strength") == 9) << endl;
  qDebug() << (bob->get_attribute("armor") == 0) << endl;
  qDebug() << "Health + random is: " << block13->get_value() << endl;
  scenario1->run();
  qDebug() << "Health + random is: " << block13->get_value() << endl;

  cout << "Testing fight" << endl;

  Fight* fight1(new Fight);

  Character* fredrik(new Character(attr_map, 40));

  Scenario* scen1(new Scenario);
  Scenario* scen2(new Scenario);
  ModifierBlock* block14(new ModifierBlock);
  block14->set_last(true);
  ModifierBlock* block15(new ModifierBlock);
  block15->set_last(true);

  block14->set_next(block15);

  scen2->set_head(block14);
  scen2->set_next_block((block14));

  fight1->add_character(bob);
  fight1->add_character(fredrik);

  fight1->add_scenario(bob,scen1);
  fight1->add_scenario(bob,scen2);

  scen1->set_next_block(block14);
  scen2->set_next_block(block15);

  fight1->run_next_turn();

  w.show();
  return a.exec();
}
