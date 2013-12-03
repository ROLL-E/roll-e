#ifndef SERVER_H
#define SERVER_H

#include "ClientConnection.h"
#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QAbstractSocket>
#include <QObject>

class Server : public QObject
{
  Q_OBJECT

private:
  std::list<ClientConnection*> clients;
  QTcpServer* server;

public:
  explicit Server(QObject* parent = 0);
  
signals:

public slots:
    void newConnection();
  
};

#endif // SERVER_H
