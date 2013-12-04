#include "ServerConnection.h"
#include <QtNetwork/QtNetwork>


ServerConnection::ServerConnection(QObject* parent) : QObject(parent) {
  clientSocket = new QTcpSocket{this};
  connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect(clientSocket, SIGNAL(connected()), this, SLOT(connected()));
  connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void ServerConnection::send_message(Message msg) const {
  QDataStream out_stream(clientSocket);
  out_stream << QChar('m') << msg;
}

void ServerConnection::send_request(Request req) const {
  QDataStream out_stream(clientSocket);
  out_stream << QChar('r') << req;
}

void ServerConnection::join(QHostAddress address){
  clientSocket->connectToHost(address,14449);
  if(!clientSocket->waitForConnected(1000)){
      qDebug() << "connection timed out!";
    }
}

void ServerConnection::connected(){
  qDebug() << "Connection established!";
}

void ServerConnection::disconnected(){
  qDebug() << "Server disconnected!";
}

void ServerConnection::readyRead(){
  QChar token;
  QDataStream in_stream(clientSocket);
  in_stream >> token;
  if (token == QChar('m')) {
      Message msg;
      in_stream >> msg;
      qDebug() << msg.message;
    }
  else if (token == QChar('r')) {
      Request req;
      in_stream >> req;
      qDebug() << req.type;
    }
}

QDataStream& operator<<(QDataStream& out, Message msg) {
  out << msg.sender << msg.recevier << msg.message;
  qDebug() << msg.message;
  return out;
}

QDataStream& operator<<(QDataStream& out, Request req) {
  out << req.type << req.id;
  return out;
}

QDataStream& operator>>(QDataStream& in, Message msg) {
  in >> msg.sender >> msg.recevier >> msg.message;
  return in;
}

QDataStream& operator>>(QDataStream& in, Request req) {
  in >> req.type >> req.id;
  return in;
}
