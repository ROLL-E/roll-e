#include "clientwindow.h"
#include "ServerConnection.h"
#include "Character.h"
#include "Item.h"
#include "Skill.h"
#include "ClientInventory.h"
#include <QApplication>
#include <QList>
#include <QString>
#include <QMap>
#include <QDebug>
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWindow w;
    w.show();
    ServerConnection testie{};
    testie.join("130.236.76.64","fredrik"); // ("192.168.1.35")
    testie.clientSocket->waitForConnected();
    testie.send_message("fredrik","Hej fredrik!");

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

    qDebug() << testie.has_joined();

    w.show();
    return a.exec();
}
