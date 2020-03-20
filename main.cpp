#include <QApplication>
#include "Controller/controller.h"
#include "memory"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  auto controller = std::make_shared<Controller>();
  controller->StartGame(0);
  return a.exec();
}
