#ifndef SERVER_H
#define SERVER_H

#include "ClientConnection.h"

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
  QList<ClientConnection*> clients;
  void process_messages();
  void process_requests();
  
signals:

public slots:
  void newConnection();
  void incoming_message(Message*);
  void incoming_request(Request*);
};

#endif // SERVER_H
