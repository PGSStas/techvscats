#include <QApplication>

#include <memory>

#include "Controller/controller.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  auto controller = std::make_shared<Controller>();
  return a.exec();
}
