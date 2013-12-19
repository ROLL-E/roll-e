#include "Server.h"
#include <iostream>


Server::Server(Story* main_story, QObject *parent) : QObject(parent){
    server = new QTcpServer(this);
    story = main_story;
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

void Server::newConnection() {
    //prompt gamemaster for permission?
    qDebug() << "New connection!";
    clients.prepend(QPair<QPointer<ClientConnection>,QThread*>(new ClientConnection(server->nextPendingConnection()), new QThread(this)));
    clients.first().first->moveToThread(clients.first().second);

    // Not sure how QObject sets up the connection, might be possible to clean this up.
    connect(clients.first().first, SIGNAL(got_something(ClientConnection*)), this, SLOT(update_messages_and_requests(ClientConnection*)));
    connect(this,SIGNAL(got_join_request()),this,SLOT(join_request()));
    connect(this, SIGNAL(got_message()),this,SLOT(redirect_messages()));
    connect(clients.first().first, SIGNAL(disconnected()), this, SLOT(client_disconnected()));
    connect(clients.first().first,SIGNAL(disconnected()),clients.first().first,SLOT(deleteLater()));
    connect(clients.first().first,SIGNAL(disconnected()), clients.first().second,SLOT(quit()));
    connect(clients.first().second,SIGNAL(finished()),clients.first().second,SLOT(deleteLater()));
    clients.first().second->start();
}

void Server::client_disconnected(){
    qDebug() << "A client has disconnected!";
}

// Gets the first message from the Servers message_buffer.
Message* Server::get_message_from_buffer(){
    if(!message_buffer.isEmpty()){
        return message_buffer.takeFirst();
    }else
        return nullptr;
}
// Gets the first request from the Servers request_buffer.
Request* Server::get_request_from_buffer(){
    if(!message_buffer.isEmpty()){
        return request_buffer.takeFirst();
    }else
        return nullptr;
}

void Server::update_messages_and_requests(ClientConnection* client){
   // If the client has any messages to get, then get them.
    while(0 < client->message_buffer.size()){
        Message* msg = client->get_message_from_buffer();
        if(msg != nullptr)
            message_buffer.append(msg);
    }
    emit got_message();

    // If the client has any pending requests, then get them.
    while(0 < client->request_buffer.size()){
        Request* req = client->get_request_from_buffer();
        if(req != nullptr){
            if(req->type == QString("Join")){
                join_requests.append(QPair<ClientConnection*, Request*>(client, req));
                emit got_join_request();
            }else
                request_buffer.append(req);
        }
    }
    emit got_request();
}



void Server::start(){
    if(!server->listen(QHostAddress::Any,14449)){
        qDebug() << "Server could not listen...";
        throw(std::runtime_error{"Fatal error: could not initiate server."});
    } else {
        qDebug() << "Server is listening.";
    }
}

void Server::redirect_messages(){
    // This should just redirect the message to intendet reciever based on
    // the reciever-field in msg.
    QMutex servermutex;
    servermutex.lock(); // OBS! This must be unlocked afterwards
    while(!message_buffer.isEmpty()){
        Message* msg = message_buffer.takeFirst();
        Character* receiver = story->get_character(msg->receiver);
        if(receiver != nullptr){
            ClientConnection* reconnection = receiver->get_connection();
            if(reconnection != nullptr)
                reconnection->send_message(*msg);
            else
                qDebug() << msg->sender << " says " << msg->message << " to " << msg->receiver;
        }
    }
    servermutex.unlock();
}

void Server::join_request(){
    QMutex servermutex;
    servermutex.lock();
    while(!join_requests.isEmpty()){
        QPair<ClientConnection*,Request*> joiner = join_requests.takeFirst();
        Character* requested_char = story->get_character(joiner.second->intention);
        // prompt gamemaster
        if(requested_char != nullptr){
            if(requested_char->get_connection() == nullptr){
                requested_char->set_connection(joiner.first);
                requested_char->get_connection()->send_message(Message{"System",requested_char->get_name(),"Welcome!"});
                requested_char->get_connection()->send_message(Message{"System",requested_char->get_name(),"du är ful!"});
                requested_char->get_connection()->send_message(Message{"System",requested_char->get_name(),"fisk!"});
                requested_char->get_connection()->send_message(Message{"System",requested_char->get_name(),"HALLO!"});
                qDebug()  << "Legion has taken control of " << requested_char->get_name();
            } else
                joiner.first->send_message(Message{"System",requested_char->get_name(), " is not available."});
        }
    }
    servermutex.unlock();
}
