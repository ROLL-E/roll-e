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
    testie.join("192.168.1.35","fredrik"); // ("192.168.1.35")
    testie.clientSocket->waitForConnected();
    testie.send_message(Message{});

    qDebug() << testie.has_joined();
    return a.exec();
}
