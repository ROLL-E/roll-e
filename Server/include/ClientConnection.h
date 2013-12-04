#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H
#include <string>
#include <vector>
#include <QDebug>
#include <QtNetwork/QtNetwork>
#include <QObject>

class Story; //Forward declartion, remember to include in .cc file.

struct Message {
    QString sender;
    QString recevier;
    QString message;
};

struct Request {
    QString type;
    quint16 id;
};

QDataStream& operator<<(QDataStream&, Message);
QDataStream& operator<<(QDataStream&, Request);

QDataStream& operator>>(QDataStream&, Message);
QDataStream& operator>>(QDataStream&, Request);



class ClientConnection : public QObject {

    Q_OBJECT

private:

    std::vector<Message*> message_buffer;
    std::vector<Request*> request_buffer;
public:
    QTcpSocket* clientSocket; // private?
    explicit ClientConnection(QTcpSocket*,QObject* parent = 0);//uncertain about this constructor...
    bool isConnected();
    void send_message(Message) const;
    Message* get_message_from_buffer();
    void push_data(Story*);
    Request* get_request_from_buffer();

public slots:
    void connected();
    void disconnected();
    void readyRead();

};

#endif
