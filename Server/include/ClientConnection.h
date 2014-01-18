#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H
#include <QString>
#include <vector>
#include <QtNetwork/QtNetwork>

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

class Story; //Forward declartion, remember to include in .cc file.

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
    void push_data(Story*);
    Request* get_request_from_buffer();
    QHostAddress get_address();

signals:
    void disconnected();
    void got_something(ClientConnection*);

public slots:
    void push_data(Character *);
    void connected();
    void remote_disconnected();
    void readyRead();

};

QDataStream& operator<<(QDataStream& out, Message& msg);

QDataStream& operator>>(QDataStream& in, Message& msg);

QDataStream& operator>>(QDataStream& in, Request& req);



#endif
