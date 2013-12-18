#include "ServerConnection.h"


ServerConnection::ServerConnection(QObject* parent) : QObject(parent) {
  clientSocket = new QTcpSocket{this};
  joined = false;
  connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect(clientSocket, SIGNAL(connected()), this, SLOT(connected()));
  connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void ServerConnection::send_message(QString receiver, QString message) const {
  QDataStream out_stream(clientSocket);
  Message msg{controlledChar,receiver,message};
  out_stream << QChar('m') << msg;

}

void ServerConnection::send_request(Request req) const {
  QDataStream out_stream(clientSocket);
  out_stream << QChar('r') << req;
}

void ServerConnection::join(QString address, QString cha){
  clientSocket->connectToHost(QHostAddress(address),14449);
  if(!clientSocket->waitForConnected(1000)){
      qDebug() << "connection timed out!";
  } else {
      send_request(Request{"Join",cha,0});
  }

}

void ServerConnection::connected(){
    qDebug() << "Connection established!";
}

void ServerConnection::disconnected(){
  qDebug() << "Server disconnected!";
  clientSocket->close();
}

void ServerConnection::readyRead(){
  qDebug("readyRead called!");
  QChar token;
  QDataStream in_stream(clientSocket);
  in_stream >> token;
  if (token == QChar('m')) {
      Message msg;
      in_stream >> msg;
      if(msg.message == QString("Welcome!") and msg.sender == QString("System")){
          joined = true;
          controlledChar = msg.receiver;
      } else
          qDebug() << msg.message;
    }
  else if (token == QChar('r')) {
      Request req;
      in_stream >> req;
      qDebug() << req.type;
    }
  else
    qDebug() << "Fuck all";
}

bool ServerConnection::has_joined(){
    return joined;
}

QDataStream& operator<<(QDataStream& out, Message& msg) {
  qDebug() << "sent to server:" << msg.sender << msg.receiver << msg.message;
  out << msg.sender << msg.receiver << msg.message;
  return out;
}

QDataStream& operator<<(QDataStream& out, Request& req) {
  out << req.type << req.intention << req.id;
  return out;
}

QDataStream& operator>>(QDataStream& in, Message& msg) {
  in >> msg.sender >> msg.receiver >> msg.message;
  qDebug() << "got from server:" << msg.sender << msg.receiver << msg.message;
  return in;
}

QDataStream& operator>>(QDataStream& in, Request& req) {
  in >> req.type >> req.intention >> req.id;
  return in;
}
