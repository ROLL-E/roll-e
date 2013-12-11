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
  connect(clients.first(), SIGNAL(got_message(Message*)), this, SLOT(incoming_message(Message*)));
  connect(clients.first(), SIGNAL(got_request(Request*)), this, SLOT(incoming_request(Request*)));
  //remember to keep listening/waitfornewConnection
}

void Server::incoming_message(Message* msg){
    message_buffer.push_back(msg);

    //for testing reasons
    process_messages();
}

void Server::incoming_request(Request* req){
    request_buffer.push_back(req);

    //same as above
    process_requests();
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

void Server::process_messages(){
    for(int i=0; i <= message_buffer.count(); i++){
        Message* msg = get_message_from_buffer();
        if(msg != nullptr)
        qDebug() << msg->sender << " says: " << msg->message << " to " << msg->recevier;
    }
}

void Server::process_requests(){
    for(int i=0; i <= request_buffer.count(); i++){
        Request* req = get_request_from_buffer();
        if(req != nullptr)
        qDebug() << "got request of type " << req->type << " with ID " << req->id;
    }
}
