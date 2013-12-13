#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H
#include <string>
#include <vector>
#include <QDebug>
#include <QtNetwork/QtNetwork>
#include <QObject>
#include <QPair>

class Story;

struct Message {
  Message() = default;
  Message(const Message&) = default;
  QString sender;
  QString recevier;
  QString message;

};

struct Request {
  Request() = default;
  Request(const Request&) = default;
  QString type;
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
    QTcpSocket* clientSocket; // private?
    explicit ClientConnection(QTcpSocket*,QObject* parent = 0);//uncertain about this constructor...
    void send_message(Message) const;
    void push_data(Story*);
    Message* get_message_from_buffer();
    Request* get_request_from_buffer();

signals:
    void disconnected();
//    void got_message(Message&);
//    void got_request(Request&);

public slots:
    void connected();
    void remote_disconnected();
    void readyRead();

};

#endif
