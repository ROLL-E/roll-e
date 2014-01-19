#include "Server.h"
#include <iostream>


Server::Server(Story* main_story, QObject *parent) : QTcpServer(parent){
    story = main_story;
    connect(this,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

void Server::stopServer(){
    for(ClientConnection* client : clients){
        client->disconnect();
        client->deleteLater();
    }
    close();
    for(Message* msg : message_buffer){
        delete msg;
    }
    for(Request* req: request_buffer){
        delete req;
    }
    emit finished();
}


void Server::newConnection() {
    //prompt gamemaster for permission?
    qDebug() << "New connection!";
    clients.prepend(new ClientConnection(nextPendingConnection()));

    connect(clients.first(), SIGNAL(got_something(ClientConnection*)), this, SLOT(update_messages_and_requests(ClientConnection*)));
    connect(this,SIGNAL(got_join_request()),this,SLOT(join_request()));
    connect(this, SIGNAL(got_message()),this,SLOT(redirect_messages()));
    connect(clients.first(), SIGNAL(disconnected(ClientConnection*)), this, SLOT(client_disconnected(ClientConnection*)));
}

void Server::closeConnection(ClientConnection* connection){
    connection->disconnect();

}

void Server::client_disconnected(ClientConnection* connection){
    qDebug() << "A client has disconnected!";

    clients.removeOne(connection);
    delete connection;
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
    if(!listen(QHostAddress::Any,14449)){
        qDebug() << "Server could not listen...";
        throw(std::runtime_error{"Fatal error: could not initiate server."});
    } else {
        qDebug() << "Server is listening.";
    }
}

void Server::redirect_messages(){
    // This should just redirect the message to intendet reciever based on
    // the reciever-field in msg.
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
                qDebug()  << "Legion has taken control of " << requested_char->get_name();
                emit client_took_control();
            } else
                joiner.first->send_message(Message{"System",requested_char->get_name(), " is not available."});
        }
    }
    servermutex.unlock();
}
