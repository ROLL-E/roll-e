#include "clientwindow.h"
#include "startdialog.h"
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


    ClientWindow* main_window = new ClientWindow();

    StartDialog* start_window = new StartDialog(main_window);

    start_window->exec();
    if (main_window->get_serverconnection() == nullptr)
      return 0;

    main_window->show();

    return a.exec();
}
