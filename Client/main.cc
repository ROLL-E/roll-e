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
    testie.join(QHostAddress("192.168.1.35"));
    if(testie.clientSocket->isValid()){
        testie.send_message(Message{"client","server","Hiya!"});
        for(quint16 i=0; i<1000;i++){
            testie.send_request(Request{"test",i});
            testie.clientSocket->flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
        }
    }
    return a.exec();
}
