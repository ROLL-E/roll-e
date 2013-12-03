#include "GameSave.h"
#include <QFile>
#include <QDataStream>
#include <QMap>
#include <iostream>
#include "Item.h"
#include "Story.h"


void GameSave::load(QString filename, Story* story) {
  QFile input_file(filename);
  input_file.open(QIODevice::ReadOnly);

  QDataStream in_stream(&input_file);

  QString tag;
  Item* current_item;

  in_stream >> tag;

  if (tag == QString("Start")) {

    while (tag != QString("End")) {
      quint16 id;
      in_stream >> id;
      current_item = new Item(id);
      in_stream >> current_item;
      story->add_item(current_item);
      in_stream >> tag;

    }
  }
  input_file.close();

}

void GameSave::save(Story* story, QString filename) {
  QFile output_file(filename);
  output_file.open(QIODevice::WriteOnly);
  QDataStream out_stream(&output_file);

  out_stream << QString("Start");
  for (Item* item : story->get_items())  {
    out_stream << item->get_id();
    out_stream << item;
    out_stream << QString("End_Item");
  }
  out_stream << QString("End");
  output_file.close();
}
