#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H
#include <string>
#include <vector>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QHostAddress>


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

class ClientConnection {

private:
    QTcpSocket* clientSocket;
    std::vector<std::string> message_buffer;
    std::vector<std::string> request_buffer;
public:
    ClientConnection(QTcpSocket* connection){clientSocket = connection;}//uncertain about this constructor...
    bool isConnected();
    void send_message(Message) const;
    Message* get_message_from_buffer();
    void push_data(Story*);
    Request* get_request_from_buffer();

};

#endif
