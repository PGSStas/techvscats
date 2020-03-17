#include "mainwindow.h"
#include <Controller/controller.h>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {

  Controller* controller = new Controller(this);
  controller->StartGame();
}

MainWindow::~MainWindow() {

}
