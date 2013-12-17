#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <QtNetwork>
#include <QObject>

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

QDataStream& operator<<(QDataStream&, Message&);
QDataStream& operator<<(QDataStream&, Request&);

QDataStream& operator>>(QDataStream&, Message&);
QDataStream& operator>>(QDataStream&, Request&);

class ServerConnection : public QObject{

  Q_OBJECT
private:

  std::vector<std::string> message_buffer;
  QString controlledChar{"Legion"};
  bool joined;

public:
  QTcpSocket* clientSocket; //private?
  ServerConnection(QObject* parent = 0);
  void send_message(QString,QString) const;
  void send_request(Request) const;
  void join(QString,QString);
  bool has_joined();

public slots:
  void connected();
  void disconnected();
  void readyRead();
};

#endif
