#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include "echoserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int port = 1234;

    EchoServer *server = new EchoServer(port);
    QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);
    return a.exec();
}
