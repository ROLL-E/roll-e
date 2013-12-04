#ifndef SERVER_H
#define SERVER_H

#include "ClientConnection.h"

class Server : public QObject
{
  Q_OBJECT

private:



public:
  explicit Server(QObject* parent = 0);
  QTcpServer* server; //private?
  std::list<ClientConnection*> clients;
  
signals:

public slots:
    void newConnection();
  
};

#endif // SERVER_H
