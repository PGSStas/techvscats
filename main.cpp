#include <QApplication>
#include "Controller/Controller.h"


int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  new Controller();

  return a.exec();
}
