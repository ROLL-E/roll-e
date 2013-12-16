#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H
#include <string>
#include <vector>
#include <QtNetwork>
#include <QObject>

struct Message {
    QString sender;
    QString recevier;
    QString message;
};

struct Request {
    QString type;
    quint16 id;
};

QDataStream& operator<<(QDataStream&, Message&);
QDataStream& operator<<(QDataStream&, Request&);

QDataStream& operator>>(QDataStream&, Message&);
QDataStream& operator>>(QDataStream&, Request&);

class ServerConnection : public QObject{

  Q_OBJECT
private:

  std::vector<std::string> message_buffer;

public:
  QTcpSocket* clientSocket; //private?
  ServerConnection(QObject* parent = 0);
  void send_message(Message) const;
  void send_request(Request) const;
  void join(QHostAddress);

public slots:
  void connected();
  void disconnected();
  void readyRead();
};

#endif
