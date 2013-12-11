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
      message_buffer.push_back(new Message{msg});
//      emit got_message(msg);
    }
  else if (token == QChar('r')) {
      Request req;
      in_stream >> req;
      request_buffer.push_back(new Request{req});
//      emit got_request(req);
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

QDataStream& operator<<(QDataStream& out, Message& msg) {
  out << msg.sender << msg.recevier << msg.message;
  return out;
}

QDataStream& operator>>(QDataStream& in, Message& msg) {
  in >> msg.sender >> msg.recevier >> msg.message;
  return in;
}

QDataStream& operator>>(QDataStream& in, Request& req) {
  in >> req.type >> req.id;
  return in;
}

Message* ClientConnection::get_message_from_buffer(){
    if(!message_buffer.empty())
        return message_buffer.takeFirst();
    else
        return nullptr;
}
