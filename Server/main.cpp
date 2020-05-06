#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include "echoserver.h"

const int port = 1234;
int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  EchoServer* server = new EchoServer(port);
  QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);

  return a.exec();
}
