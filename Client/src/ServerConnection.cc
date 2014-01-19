#include "ServerConnection.h"
#include "Character.h"
#include "clientwindow.h"


ServerConnection::ServerConnection(QObject* parent) : QObject(parent) {
    clientSocket = new QTcpSocket{this};
    // Just in case the buffer isn't already empty
    clientSocket->flush();
    controlledChar = new Character(*(new QMap<QString,qint16>),0);
    controlledChar->set_name("Legion");
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(clientSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

Character* ServerConnection::get_controlledChar(){
    return controlledChar;
}

void ServerConnection::set_clientwindow(ClientWindow* new_window) {
  clientwindow = new_window;
}

void ServerConnection::send_request(Request req) const {
    QDataStream out_stream(clientSocket);
    out_stream << QChar('r') << req;
}

void ServerConnection::join(QString address, QString cha){
    qDebug() << "connecting to host...";
    clientSocket->connectToHost(QHostAddress(address),14449);
    if(!clientSocket->waitForConnected(1000)){
        qDebug() << "connection timed out!"; // error throw?
    } else {
        qDebug() << "requesting to join as character: " << cha;
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
    QChar token;
    QDataStream in_stream(clientSocket);
    do {
    in_stream >> token;
    if (token == QChar('m')) {
        Message msg;
        in_stream >> msg;
        qDebug() << msg.sender << " says "<< msg.message;
    }
    else if (token == QChar('r')) {
        Request req;
        in_stream >> req;
        qDebug() << req.type;
    }
    else if (token == QChar('p')) {
        in_stream >> controlledChar;
    }
    else
        qDebug() << "Uknown message-type."; // error throw
    } while (!in_stream.atEnd());
    clientwindow->refresh_fields();
}

void ServerConnection::send_message(QString receiver, QString message) const {
    QDataStream out_stream(clientSocket);
    Message msg{controlledChar->get_name(),receiver,message};
    out_stream << QChar('m') << msg;
}

QDataStream& operator<<(QDataStream& out, Message& msg) {
    out << msg.sender << msg.receiver << msg.message;
    return out;
}

QDataStream& operator<<(QDataStream& out, Request& req) {
    out << req.type << req.intention << req.id;
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
