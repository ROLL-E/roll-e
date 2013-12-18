#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H
#include <string>
#include <vector>
#include <QDebug>
#include <QtNetwork/QtNetwork>
#include <QObject>
#include <QPair>

class Story;
class Character;

struct Message {
  Message() = default;
  Message(const Message&) = default;
  QString sender;
  QString receiver;
  QString message;

};

struct Request {
  Request() = default;
  Request(const Request&) = default;
  QString type;
  QString intention;
  quint16 id;
};

QDataStream& operator<<(QDataStream&, Message&);
QDataStream& operator<<(QDataStream&, Request&);

QDataStream& operator>>(QDataStream&, Message&);
QDataStream& operator>>(QDataStream&, Request&);



class ClientConnection : public QObject {

    Q_OBJECT

friend class Server;

private:
    QList<Message*> message_buffer;
    QList<Request*> request_buffer;

public:
    QTcpSocket* clientSocket;
    explicit ClientConnection(QTcpSocket*,QObject* parent = 0);
    void send_message(Message);
    Message* get_message_from_buffer();
    Request* get_request_from_buffer();

signals:
    void disconnected();
    void got_something(ClientConnection*);

public slots:
    void push_data(Character *);
    void connected();
    void remote_disconnected();
    void readyRead();

};

#endif
