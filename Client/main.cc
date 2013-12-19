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
    testie.join("130.236.76.64","BOB!"); // ("192.168.1.35")
    testie.clientSocket->waitForConnected();
    testie.send_message("BOB!","Hej fredrik!");

    //    qDebug() << testie.get_controlledChar()->get_name();

    //    qDebug() << testie.get_controlledChar()->get_name() + "'s health" << testie.get_controlledChar()->get_attribute("health");

    //    Item* item1(new Item("Hammer of doom"));
    //    testie.get_controlledChar()->add_item(item1);

    //    Item* item2(new Item("nicer hammah"));
    //    testie.get_controlledChar()->add_item(item2);


    //    qDebug() << testie.get_controlledChar()->has_item(item1);
    //    qDebug() << item1->get_name();
    //    qDebug() << item2->get_name();

    //    qDebug() << testie.has_joined();

    w.show();
    return a.exec();
}
