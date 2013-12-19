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
#include "Fight.h"
#include "Ruleset.h"
#include "Scenario.h"
#include "Skill.h"

using namespace std;

int main(int argc, char *argv[])
{

/*
  QList<QString> attr_list{"health", "armor", "strength"};
  Ruleset* rs = new Ruleset(attr_list);

  Story* main_story = new Story(rs);




  QMap<QString, qint16> attr_map{{"health", 10}, {"armor", 2}, {"strength", 5}};
  main_story->add_character(new Character(attr_map, 50, main_story));

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

  qDebug() << "Testing saveload";
  qDebug();

  //Test program, compares 2 2-sided dice to the number 3 and either waits 3
  // 3 turns and heals 1 point or deals 6 damage to bob, depending on the outcome.

  ValueBlock* b1 = new ValueBlock();
  b1->set_intention('s');
  b1->set_value(3);

  ValueBlock* b2 = new ValueBlock();
  b2->set_intention('r');
  b2->set_sides(2);
  b2->set_number(2);
  b1->set_next(b2);

  CompareBlock* b3 = new CompareBlock();
  b3->set_lhs(b1);
  b3->set_rhs(b2);
  b2->set_next(b3);

  ValueBlock* b4 = new ValueBlock();
  b4->set_intention('a');
  b4->set_value(0);
  b3->set_alternate(b4);
  b4->add_to_applicable_skills(rs->get_skills().at(0),"int");
  b4->add_to_applicable_skills(rs->get_skills().at(1),"int");
  b4->execute();


  qDebug() << "Value on b4 (should be 15): " << b4->get_value();

  DamageBlock* b5 = new DamageBlock();
  b5->set_valueblock(b4);
  b5->set_target(bob);
  b5->set_type("blunt");
  b5->set_next(nullptr);
  b5->set_last(true);
  b4->set_next(b5);

  WaitBlock* b6 = new WaitBlock();
  b6->set_wait_turns(3);
  b3->set_next(b6);

  ValueBlock* b7 = new ValueBlock();
  b7->set_intention('s');
  b7->set_value(-1);
  b6->set_next(b7);



  ModifierBlock* b8 = new ModifierBlock();
  b8->set_modifier("health", 5);
  b8->set_target(bob);
  b7->set_next(b8);

  ModifierBlock* b10 = new ModifierBlock();
  b10->set_previous_modifier(b8);

  DamageBlock* b9 = new DamageBlock();
  b9->set_type("heal");
  b9->set_valueblock(b7);
  b9->set_target(bob);
  b9->set_last(true);
  b8->set_next(b9);


  Scenario* scene1 = new Scenario();
  scene1->set_head(b1);
  scene1->set_next_block(b1);
  scene1->set_story(main_story);

  main_story->get_ruleset()->add_scenario(scene1);

  //GameSave::save(main_story, "F:\\Projekt\\bigsave.dat");



  //rs = Ruleset(attr_list);
  //GameSave::load("F:\\Projekt\\bigsave.dat", main_story);

  qDebug() << "HÄR SKA DET STÅ -5!!!!";
  qDebug() << b10->get_modifier("health");
  qDebug() << "Slut";

  for (Item* i : main_story->get_items()) {
    qDebug() << i->get_id() << ": " << i->get_name();
  }

  qDebug();

  for (Character* c : main_story->get_characters()) {
    qDebug() << c->get_name();
    qDebug() << c->get_attribute("health");
    for (Skill* s : c->get_skills())
      qDebug() << s->get_name();
  }


  qDebug() << main_story->get_characters().value(0)->get_attribute("health");
  main_story->get_ruleset()->get_scenarios().front()->run();
  qDebug() << main_story->get_characters().value(0)->get_attribute("health");



  cout << "Testing fight" << endl;

  Fight* fight1(new Fight);

  Character* fredrik(new Character(attr_map, 40, main_story));

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

  fight1->run_next_turn();*/

  QApplication a(argc, argv);
  ServerWindow w(nullptr);
  w.show();



  return a.exec();
}
