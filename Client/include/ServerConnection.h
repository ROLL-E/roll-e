#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H
#include <string>
#include <vector>

struct Message {
    std::string sender;
    std::string recevier;
    std::string message;
};

struct Request {
    std::string type;
    std::string id;
};

class ServerConnection {

private:
    //socket
    std::vector<std::string> message_buffer;

public:
    void send_message(Message) const;
    void send_request(Request) const;
};

#endif
