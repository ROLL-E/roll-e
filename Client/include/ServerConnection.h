#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <chrono>
#include <thread>
#include <QtNetwork>
#include <QObject>

class Character;
class ClientWindow;

struct Message {
    QString sender;
    QString receiver;
    QString message;
};

struct Request {
    QString type;
    QString intention;
    quint16 id;
};

class ServerConnection : public QObject{

  Q_OBJECT
  
private:

  Character* controlledChar;
  bool joined;
  ClientWindow* clientwindow;

public:
  QTcpSocket* clientSocket; //private?
  ServerConnection(QObject* parent = 0);
  void send_message(QString,QString) const;
  void send_request(Request) const;
  void join(QString,QString);
  bool has_joined();
  Character* get_controlledChar();
  void set_clientwindow(ClientWindow*);

public slots:
  void connected();
  void disconnected();
  void readyRead();
};

QDataStream& operator<<(QDataStream& out, Message& msg);

QDataStream& operator<<(QDataStream& out, Request& req);

QDataStream& operator>>(QDataStream& in, Message& msg);

QDataStream& operator>>(QDataStream& in, Request& req);


#endif
