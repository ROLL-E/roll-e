#include <ClientConnection.h>

bool ClientConnection::isConnected(){
  return clientSocket->isValid();
}

void ClientConnection::send_message(Message) const{
  clientSocket->write("send_message() not yet implemented.");
  clientSocket->flush();
  clientSocket->waitForBytesWritten(1000); //maybe a bit overkill
}

Message* ClientConnection::get_message_from_buffer(){
  qDebug() << clientSocket->readAll(); //consider serialization? otherwise just send the message's individual parts.
  return nullptr; //remember to change this
}

void ClientConnection::push_data(Story*){
  qDebug() << clientSocket->write("push_data() not yet implemented.");
}

Request* ClientConnection::get_request_from_buffer(){
  qDebug() << clientSocket->readAll();
  return nullptr; //remember to change this
}
