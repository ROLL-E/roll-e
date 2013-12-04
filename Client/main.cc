#include "clientwindow.h"
#include "ServerConnection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ClientWindow w;
  w.show();
  ServerConnection testie{};
  testie.join(QHostAddress::LocalHost);
  testie.clientSocket->waitForReadyRead(1000);
  testie.send_message(Message{"me", "rut", "hail mary christmas"});
  return a.exec();
}
