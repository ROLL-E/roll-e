#include "Server.h"
#include <QList>

Server::Server(QObject *parent) :
  QObject(parent)
{
  server = new QTcpServer(this);
  connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

void Server::newConnection() {
  //prompt gamemaster for permission?
  clients.prepend(QPair<ClientConnection*,QThread*>(new ClientConnection(server->nextPendingConnection()),
                           new QThread(this)));
  clients.first().first->moveToThread(clients.first().second); // Meaty because we need the actual pointers located in the list.
  connect(clients.first().first, SIGNAL(disconnected()), this, SLOT(client_disconnected()));
  connect(clients.first().second,SIGNAL(started()),clients.first().first,SLOT(thread_started()));
  connect(clients.first().first,SIGNAL(finished()),clients.first().first,SLOT(deleteLater()));
  connect(clients.first().first,SIGNAL(finished()), clients.first().second,SLOT(quit()));
  connect(clients.first().second,SIGNAL(finished()),clients.first().second,SLOT(deleteLater()));
  clients.first().second->start();
}

void Server::client_disconnected(){
    qDebug() << "This isn't supposed to happen...yet";
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
    // gör om till vanlig for-loop
    for(int i = 0; i < clients.count();i++){
        Message* msg = clients.at(i).first->get_message_from_buffer();
        Request* req = clients.at(i).first->get_request_from_buffer();
        if(msg != nullptr)
        message_buffer.push_back(new Message(*msg));
        if(req != nullptr)
        request_buffer.push_back(new Request(*req));
    }
}

void Server::start(){
  if(!server->listen(QHostAddress::Any,14449)){
      qDebug() << "Server could not listen...";
      throw(std::runtime_error{"Fatal error: could not initiate server."});
    }else
    {
      qDebug() << "Server is listening.";
    }
}
