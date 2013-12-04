#include <ClientConnection.h>
class Story;

ClientConnection::ClientConnection(QTcpSocket* connection, QObject* parent) : QObject(parent) {
  clientSocket = connection;
  connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect(clientSocket, SIGNAL(connected()), this, SLOT(connected()));
  connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void ClientConnection::disconnected(){
  clientSocket->close();
}

void ClientConnection::readyRead(){
  QChar token;
  QDataStream in_stream(clientSocket);
  in_stream >> token;
  if (token == QChar('m')) {
      Message msg;
      in_stream >> msg;
      qDebug() << msg.message;
      message_buffer.push_back(new Message(msg));
    }
  else if (token == QChar('r')) {
      Request req;
      in_stream >> req;
      request_buffer.push_back(new Request(req));
    }
}


void ClientConnection::connected(){
  qDebug() << "Connection!\n";
}

bool ClientConnection::isConnected(){
  return clientSocket->isValid();
}

void ClientConnection::send_message(Message msg) const{
  QDataStream out_stream(clientSocket);
  out_stream << QChar('m') << msg;
}

void ClientConnection::push_data(Story*){
  qDebug() << clientSocket->write("push_data() not yet implemented.");
}

Message* ClientConnection::get_message_from_buffer(){
  return message_buffer.front();
}

Request* ClientConnection::get_request_from_buffer(){
  return request_buffer.front();
}

QDataStream& operator<<(QDataStream& out, Message& msg) {
  qDebug() << "sent to client:" << msg.sender << msg.recevier << msg.message;
  out << msg.sender << msg.recevier << msg.message;
  return out;
}

QDataStream& operator>>(QDataStream& in, Message& msg) {
  in >> msg.sender >> msg.recevier >> msg.message;
  qDebug() << "got from client:" << msg.sender << msg.recevier << msg.message;
  return in;
}

QDataStream& operator>>(QDataStream& in, Request& req) {
  in >> req.type >> req.id;
  return in;
}
