#include <QApplication>
#include "Controller/controller.h"
#include "memory"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  std::shared_ptr<Controller> controller = std::make_shared<Controller>();
  return a.exec();
}
