#ifndef SERVER_H
#define SERVER_H

#include "ClientConnection.h"

class Client;

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

public slots:
  void newConnection();
  void client_disconnected();
  void start();
  void put_message_in_buffer(ClientConnection*);
  void put_request_in_buffer(ClientConnection*);

};

#endif // SERVER_H
