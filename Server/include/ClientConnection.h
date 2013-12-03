#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H
#include <string>
#include <vector>
#include <QDebug>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QHostAddress>
#include <QObject>

class Story; //Forward declartion, remember to include in .cc file.

struct Message {
    std::string sender;
    std::string recevier;
    std::string message;
};

struct Request {
    std::string type;
    std::string id;
};

class ClientConnection : public QObject {

    Q_OBJECT

private:
    QTcpSocket* clientSocket;
    std::vector<std::string> message_buffer;
    std::vector<std::string> request_buffer;
public:
    explicit ClientConnection(QTcpSocket*,QObject* parent = 0);//uncertain about this constructor...
    bool isConnected();
    void send_message(Message) const;
    Message* get_message_from_buffer();
    void push_data(Story*);
    Request* get_request_from_buffer();
    void connectToHost(QHostAddress);

public slots:
    void connected();
    void disconnected();
    void readyRead();

};

#endif
