#ifndef SERVER_H
#define SERVER_H
#include "ClientConnection.h"
#include "Story.h"
#include <QPointer>
#include <QList>
#include <QtNetwork/QtNetwork>

class Client;
class Story;

class Server : public QTcpServer
{
    Q_OBJECT

friend class Story;

private:
    QList<Message*> message_buffer;
    QList<Request*> request_buffer;
    QList<QPair<ClientConnection*,Request*>> join_requests;
    QPointer<Story> story;
    Message* get_message_from_buffer();
    Request* get_request_from_buffer();

public:
    explicit Server(Story*, QObject* parent = 0);
    QList<QPointer<ClientConnection>> clients;
  
signals:
  void finished();
  void got_message();
  void got_request();
  void got_join_request();
  void client_took_control();

public slots:
  void stopServer();
  void redirect_messages();
  void newConnection();
  void client_disconnected();
  void start();
  void update_messages_and_requests(ClientConnection*);
  void join_request();
};

#endif // SERVER_H
