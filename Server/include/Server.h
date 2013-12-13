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
  void serverUpdate();
  
signals:
  void finished();

public slots:
  void newConnection();
  void client_disconnected();
  void start();
};

#endif // SERVER_H
