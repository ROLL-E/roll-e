#include "Server.h"
#include <QList>

Server::Server(QObject *parent) :
  QObject(parent)
{
  server = new QTcpServer(this);
  connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

  if(!server->listen(QHostAddress::Any,14449))
  {
      qDebug() << "Server could not listen...";
  }else
  {
      qDebug() << "Server is listening.";
  }
}

void Server::newConnection() {
  //prompt gamemaster for permission?
  clients.insert(clients.begin(), new ClientConnection{server->nextPendingConnection()});
  connect(clients.first(), SIGNAL(got_message(Message&)), this, SLOT(incoming_message(Message&)));
  connect(clients.first(), SIGNAL(got_request(Request&)), this, SLOT(incoming_request(Request&)));
  connect(clients.first(), SIGNAL(disconnected()), this, SLOT(client_disconnected()));
  //remember to keep listening/waitfornewConnection
}



Message* Server::get_message_from_buffer(){
    if( 0 > message_buffer.count()){
        return message_buffer.takeFirst();
    }else
        return nullptr;
}

Request* Server::get_request_from_buffer(){
    if(0 > message_buffer.count()){
        return request_buffer.takeFirst();
    }else
        return nullptr;
}

void Server::update_messages(){
    foreach(ClientConnection* c, clients){
        Message* msg = c->get_message_from_buffer();
        if(msg != nullptr)
        message_buffer.push_back(new Message{msg});
    }
}

void Server::update_requests(){
    foreach(ClientConnection* c, clients){
        Request* req = c->get_request_from_buffer();
        if(req != nullptr)
        request_buffer.push_back(new Request{req});
    }
}

void Server::client_disconnected(std::iterator pos){
    clients.erase(pos)
}
