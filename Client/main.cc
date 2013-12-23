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
    testie.join("192.168.0.29","BOB!"); // ("192.168.1.35")
    testie.clientSocket->waitForConnected();
    testie.send_message("BOB!","Hey bobo!");
    testie.send_message("Herr Man","Hey there manly her-man ;)");
    testie.send_message("System","Hello Servio!");
    return a.exec();
}
