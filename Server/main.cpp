#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include "server.h"

const int port = 1234;
int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  Server* server = new Server(port);
  QObject::connect(server, &Server::closed, &a, &QCoreApplication::quit);

  return a.exec();
}
