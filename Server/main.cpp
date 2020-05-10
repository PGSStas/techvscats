#include "server.h"

#include <QCoreApplication>

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  int port = 1234;
  auto server = new Server(port);
  QObject::connect(server, &Server::closed, &a, &QCoreApplication::quit);

  return a.exec();
}
