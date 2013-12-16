#ifndef SERVER_H
#define SERVER_H

#include "ClientConnection.h"
#include "Story.h"
#include <QList>

class Client;
class Story;

class Server : public QObject
{
    Q_OBJECT

private:
    QList<Message*> message_buffer;
    QList<Request*> request_buffer;
    Message* get_message_from_buffer();
    Request* get_request_from_buffer();

public:
  explicit Server(QObject* parent = 0);
  QTcpServer* server; //private?
  QList<QPair<QPointer<ClientConnection>,QThread*>> clients;
  
signals:
  void finished();
  void got_message();
  void got_request();

public slots:
  void newConnection();
  void client_disconnected();
  void start();
  void update_messages_and_requests(ClientConnection*);
  void push_data(Story*);
  void redirect_messages(Story*);

};

#endif // SERVER_H
