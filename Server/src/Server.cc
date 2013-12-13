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
    clients.prepend(QPair<QPointer<ClientConnection>,QThread*>(new ClientConnection(server->nextPendingConnection()),
                                                               new QThread(this)));
    clients.first().first->moveToThread(clients.first().second);
    // Meaty because we need the actual pointers located in the list.
    connect(clients.first().first, SIGNAL(got_message(ClientConnection*)), this, SLOT(put_message_in_buffer(ClientConnection*)));
    connect(clients.first().first, SIGNAL(got_request(ClientConnection*)), this, SLOT(put_request_in_buffer(ClientConnection*)));
    connect(clients.first().first, SIGNAL(disconnected()), this, SLOT(client_disconnected()));
    connect(clients.first().first,SIGNAL(disconnected()),clients.first().first,SLOT(deleteLater()));
    connect(clients.first().first,SIGNAL(disconnected()), clients.first().second,SLOT(quit()));
    connect(clients.first().second,SIGNAL(finished()),clients.first().second,SLOT(deleteLater()));
    clients.first().second->start();
}

void Server::client_disconnected(){
    qDebug() << "A client has disconnected!";
}


Message* Server::get_message_from_buffer(){
    if( 0 > message_buffer.size()){
        return message_buffer.takeFirst();
    }else
        return nullptr;
}

Request* Server::get_request_from_buffer(){
    if(0 > message_buffer.size()){
        return request_buffer.takeFirst();
    }else
        return nullptr;
}

void Server::put_message_in_buffer(ClientConnection* client){
    Message* msg = client->get_message_from_buffer();
    if(msg != nullptr)
        qDebug() << msg->message;
}

void Server::put_request_in_buffer(ClientConnection* client){
    Request* req = client->get_request_from_buffer();
    if(req != nullptr)
        qDebug() << req->id;
}


void Server::start(){
    if(!server->listen(QHostAddress::Any,14449)){
        qDebug() << "Server could not listen...";
        throw(std::runtime_error{"Fatal error: could not initiate server."});
    }else
    {
        qDebug() << "Server is listening.";
        //      while(server->isListening()){
        //          serverUpdate();
        //          if(!clients.empty()){
        //          for(int i=0;i < message_buffer.size();i++){
        //              for(int j=0;i<clients.size();j++){
        //                  clients.at(j).first->send_message(*(message_buffer.takeFirst()));
        //              }
        //          }
        //          for(int i=0;i < request_buffer.size();i++){
        //              for(int j=0;i<clients.size();j++){
        //                  clients.at(j).first->send_request(*(request_buffer.takeFirst()));
        //              }
        //          }
    }
}


