#include <ClientConnection.h>
#include "Character.h"

ClientConnection::ClientConnection(QTcpSocket* connection, QObject* parent) : QObject(parent) {
  clientSocket = connection;
  connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect(clientSocket, SIGNAL(connected()), this, SLOT(connected()));
  connect(clientSocket, SIGNAL(disconnected()), this, SLOT(remote_disconnected()));
}

void ClientConnection::disconnect(){
    clientSocket->close();
}

void ClientConnection::remote_disconnected(){
  clientSocket->close();
  emit disconnected(this);
}

void ClientConnection::readyRead(){
  QChar token;
  QDataStream in_stream(clientSocket);
  // Are there more messages to recieve?
  while(!clientSocket->atEnd()){
      in_stream >> token;
      // What kind of message did we recieve?
      // To add a new kind of packet, just add another char.
      if (token == QChar('m')) {
          Message msg;
          in_stream >> msg;
          message_buffer.push_back(new Message(msg));
      }
      else if (token == QChar('r')) {
          Request req;
          in_stream >> req;
      request_buffer.push_back(new Request(req));
      }
  }
  emit got_something(this);
}


void ClientConnection::connected(){
  // Since the server only acts in response to events there is no need for Nadle's algorithm.
  // We might still need a slight delay on the clientside to prevent missahps though.
  clientSocket->setSocketOption(QAbstractSocket::LowDelayOption,1);
}

void ClientConnection::send_message(Message msg) {
  QDataStream out{clientSocket};
  out << QChar('m') << msg;
}

void ClientConnection::push_data(Character* cha){
    //behöver veta hur storys och klientens information kommer se ut för att göra klart den här,
    // eg, blir nog bäst att lämna till efter merge.
    QMutex mutex;
    mutex.lock();

    QDataStream out(clientSocket);
    out << QChar('p') << cha;
    mutex.unlock();
}

QDataStream& operator<<(QDataStream& out, Message& msg) {
  out << msg.sender << msg.receiver << msg.message;
  return out;
}

QDataStream& operator>>(QDataStream& in, Message& msg) {
  in >> msg.sender >> msg.receiver >> msg.message;
  return in;
}

QDataStream& operator>>(QDataStream& in, Request& req) {
  in >> req.type >> req.intention >> req.id;
  return in;
}

Message* ClientConnection::get_message_from_buffer(){
    if(!message_buffer.empty())
        return message_buffer.takeFirst();
    else
        return nullptr;
}

Request* ClientConnection::get_request_from_buffer(){
    if(!request_buffer.empty())
        return request_buffer.takeFirst();
    else
      return nullptr;
}

QHostAddress ClientConnection::get_address()
{
  return clientSocket->peerAddress();
}
