#include "clientwindow.h"
#include <QApplication>
#include <QList>
#include <QString>
#include <QMap>
#include <iostream>
#include <QDebug>
#include "Character.h"
#include "Item.h"
#include "Skill.h"
#include "ClientInventory.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ClientWindow w;

  QMap<QString, qint16> attr_map{{"health", 10}, {"armor", 2}, {"strength", 5}};

  Character* bob(new Character(attr_map, 50));

  bob->set_name("Bob");
  qDebug() << bob->get_name();

  qDebug() << "bob's health" << bob->get_attribute("health");

  Item* item1(new Item("Hammer of doom"));
  bob->add_item(item1);

  Item* item2(new Item("nicer hammah"));
  bob->add_item(item2);


  qDebug() << bob->has_item(item1);
  qDebug() << item1->get_name();
  qDebug() << item2->get_name();



  w.show();

  return a.exec();
}
