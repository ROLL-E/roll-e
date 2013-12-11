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
  for(quint16 i=0; i < 1000; i++){
      testie.send_request(Request{"test",i});
      testie.clientSocket->waitForBytesWritten(100);
  }
  return a.exec();
}
