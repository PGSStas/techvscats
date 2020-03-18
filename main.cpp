#include <QApplication>
#include "Controller/Controller.h"
#include "memory"
int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  std::unique_ptr<Controller> controller(new Controller());
  return a.exec();
}
