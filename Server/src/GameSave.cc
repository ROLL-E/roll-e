#include "GameSave.h"
#include <QFile>
#include <QDataStream>
#include <QMap>
#include <iostream>
#include <QDebug>
#include <stdexcept>

#include "Skill.h"
#include "Story.h"
#include "Item.h"
#include "Character.h"
#include "Ruleset.h"
#include "Scenario.h"

#include "LogicBlock.h"
#include "WaitBlock.h"


int GameSave::load(QString filename, Story*& story) {
  QFile input_file(filename);
  if (!input_file.open(QIODevice::ReadOnly))
    return 1;

  QDataStream in_stream(&input_file);

  QString tag;
  in_stream >> tag;

  if (story != nullptr)
    delete story; // emits serverStop

  try {
    if (tag == QString("Rules")) {
      QList<QString> attr;
      in_stream >> attr;
      story = new Story(new Ruleset(attr));

      in_stream >> tag;
    }

    Item* current_item;

    while (tag == QString("Item")) {
      quint16 id;
      in_stream >> id;
      current_item = new Item(id);
      in_stream >> current_item;
      story->add_item(current_item);

      in_stream >> tag;
    }

    Character* current_character;

    while (tag == QString("Char")) {
      in_stream >> current_character;
      current_character->set_story(story);
      story->add_character(current_character);

      in_stream >> tag;
    }

    Skill* current_skill;

    while (tag == QString("Skill")) {
      in_stream >> current_skill;
      story->get_ruleset()->add_skill(current_skill);

      in_stream >> tag;
    }

    Scenario* current_scenario = new Scenario();

    while (tag == QString("Scen")) {
      in_stream >> current_scenario;
      story->get_ruleset()->add_scenario(current_scenario);

      current_scenario->set_head(current_scenario->all_blocks.value(current_scenario->head_id));
      current_scenario->set_next_block(current_scenario->all_blocks.value(current_scenario->next_block_id));
      current_scenario->get_head()->populate_pointer_fields(current_scenario->all_blocks, story->get_characters());

      in_stream >> tag;
    }

    for (Character* character : story->get_characters()) {
      for (quint16 i : character->skill_ids) {
        character->add_skill(story->get_ruleset()->get_skills().at(i));
      }
    }
  }
  catch (logicblock_error e) {
    qDebug() << e.what();
    delete story;  // ?
  }



  input_file.close();
  return 0;
}

int GameSave::save(Story* story, QString filename) {

  for (Character* character : story->get_characters()) {
    quint16 i{0};
    character->skill_ids.clear();
    for (Skill* skill : story->get_ruleset()->get_skills()) {
      if (character->get_skills().indexOf(skill) != -1)
        character->skill_ids.append(i);
      ++i;
    }
  }

  QFile output_file(filename);
  if (!output_file.open(QIODevice::WriteOnly))
    return 1;
  QDataStream out_stream(&output_file);

  out_stream << QString("Rules");
  out_stream << story->get_ruleset()->get_attributes();

  for (Item* item : story->get_items())  {
    out_stream << QString("Item");
    out_stream << item->get_id();
    out_stream << item;
  }

  for (Character* character : story->get_characters()) {
    out_stream << QString("Char");
    out_stream << character;
  }


  for (Skill* skill : story->get_ruleset()->get_skills()) {
    out_stream << QString("Skill");
    out_stream << skill;
  }

  for (Scenario* scenario : story->get_ruleset()->get_scenarios()) {
    out_stream << QString("Scen");

    scenario->get_head()->add_to_list(scenario->all_blocks);

    scenario->head_id = scenario->all_blocks.indexOf(scenario->get_head());
    scenario->next_block_id = scenario->all_blocks.indexOf(scenario->get_next_block());
    scenario->get_head()->populate_id_fields(scenario->all_blocks, story->get_characters());
    out_stream << scenario;
  }


  out_stream << QString("End");
  output_file.close();
  return 0;
}

