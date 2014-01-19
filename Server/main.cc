#include "serverwindow.h"
#include <QApplication>
#include <iostream>
#include <QDebug>
#include <QString>
#include <QMap>
#include <QFile>
#include <QDir>
#include <stdexcept>
#include "startdialog.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  ServerWindow* w = new ServerWindow();

  StartDialog* dlg = new StartDialog(w);
  dlg->exec();
  if (w->get_story() == nullptr)
    return 0;


  w->show();







  return a.exec();
}
