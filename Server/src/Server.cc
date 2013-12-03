#include "Server.h"

Server::Server(QObject *parent) :
  QObject(parent)
{
  server = new QTcpServer(this);
  connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

void Server::newConnection() {
  //prompt gamemaster for permission?
  clients.insert(clients.begin(), new ClientConnection{server->nextPendingConnection()});
  //remember to keep listening/waitfornewConnection
}

void Server::start(){
  server->listen(QHostAddress::Any,14449);
}
