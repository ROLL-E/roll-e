#include "clientwindow.h"
#include "ServerConnection.h"
#include <QApplication>
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientWindow w;
    w.show();
    ServerConnection testie{};
    testie.join(QHostAddress("192.168.1.35")); // ("192.168.1.35")
    if(testie.clientSocket->isValid()){
        testie.send_message(Message{"client","server","Hiya!"});
        //testie.send_request(Request{"join","fredrik",1});
    }
    return a.exec();
}
