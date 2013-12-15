#include "Server.h"


Server::Server(QObject *parent) : QObject(parent){
    server = new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

void Server::newConnection() {
    //prompt gamemaster for permission?
    clients.prepend(QPair<QPointer<ClientConnection>,QThread*>(new ClientConnection(server->nextPendingConnection()), new QThread(this)));
    clients.first().first->moveToThread(clients.first().second);
    // Meaty because we need the actual pointers of the clientconnection and its thread located in the list to setup the connection.
    // Not sure how QObject sets up the connection, might be possible to clean this up.
    connect(clients.first().first, SIGNAL(got_something(ClientConnection*)), this, SLOT(update_messages_and_requests(ClientConnection*)));
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
    if( 0 > message_buffer.size()){
        return message_buffer.takeFirst();
    }else
        return nullptr;
}
// Gets the first request from the Servers request_buffer.
Request* Server::get_request_from_buffer(){
    if(0 > message_buffer.size()){
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
        if(req != nullptr)
            request_buffer.append(req);
    }
    emit got_request();
}


void Server::start(){
    if(!server->listen(QHostAddress::Any,14449)){
        qDebug() << "Server could not listen...";
        throw(std::runtime_error{"Fatal error: could not initiate server."}); // This should never happen.
    } else {
        qDebug() << "Server is listening.";
    }
}

void Server::push_data(Story* story){ // Might need story* here.
    // we need to implement character and story for this
    while(0 < request_buffer.size()){
        Request* req = request_buffer.takeFirst();
        qDebug() << req->type << req->id;
    }
}

void Server::redirect_messages(Story* story){
    // This should just redirect the message to intendet reciever based on
    // the reciever-field in msg.
    try{
        while(0 < message_buffer.size()){
            Message* msg = message_buffer.takeFirst();
            QList::const_iterator it = story->get_characters().cbegin();
            // Find the character whom the message is for
            while((*it)->get_name() != msg->recevier){
                it++;
                if(it = story->get_characters().cend()){
                    it = story->get_characters().cbegin();
                    // Reciever not found, return to sender
                    while((*it)->get_name() != msg->sender){
                        it++;
                        if(it = story->get_characters().cend())
                            // Neither sender nor receiver found, wtf?!
                            throw(std::out_of_range("could not find receiver, this should be impossible."));
                    }
                }
            }
            (*it)->get_client().send_message(msg);
        }
    }catch(std::out_of_range e){
        qDebug << e.what();
    }
}
