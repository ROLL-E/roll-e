#include "GameSave.h"
#include <QFile>
#include <QDataStream>
#include <QMap>
#include <iostream>
#include <QDebug>

#include "Skill.h"
#include "Story.h"
#include "Item.h"
#include "Character.h"
#include "Ruleset.h"


void GameSave::load(QString filename, Story* story) {
  QFile input_file(filename);
  input_file.open(QIODevice::ReadOnly);

  QDataStream in_stream(&input_file);

  QString tag;
  Item* current_item;

  in_stream >> tag;


  while (tag == QString("Item") && tag != QString("End")) {
    quint16 id;
    in_stream >> id;
    current_item = new Item(id);
    in_stream >> current_item;
    story->add_item(current_item);

    in_stream >> tag;
  }

  Character* current_character;

  while (tag == QString("Char") && tag != QString("End")) {
    in_stream >> current_character;
    story->add_character(current_character);

    in_stream >> tag;
  }

  Skill* current_skill;

  while (tag == QString("Skill") && tag != QString("End")) {
    in_stream >> current_skill;
    story->get_ruleset().add_skill(current_skill);

    in_stream >> tag;
  }

  for (Character* character : story->get_characters()) {
    for (quint16 i : character->skill_ids) {
      qDebug() << i;
      character->add_skill(story->get_ruleset().get_skills().at(i));
    }
  }

  input_file.close();

}

void GameSave::save(Story* story, QString filename) {
  for (QList<Skill*>::Iterator iten{story->get_ruleset().get_skills().begin()};
       iten != story->get_ruleset().get_skills().end();
       ++iten) {
    for (Character* character : story->get_characters()) {

      character->skill_ids.append(story->get_ruleset().get_skills().indexOf(*iten));
    }
  }

  QFile output_file(filename);
  output_file.open(QIODevice::WriteOnly);
  QDataStream out_stream(&output_file);

  for (Item* item : story->get_items())  {
    out_stream << QString("Item");
    out_stream << item->get_id();
    out_stream << item;
  }

  for (Character* character : story->get_characters()) {
    out_stream << QString("Char");
    out_stream << character;
  }


  for (Skill* skill : story->get_ruleset().get_skills()) {
    out_stream << QString("Skill");
    out_stream << skill;
  }




  out_stream << QString("End");
  output_file.close();
}

