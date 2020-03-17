#include "mainwindow.h"
#include <Controller/controller.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), controller(new Controller(this)) {

  controller->StartGame();
  controller_id = startTimer(10);
}

void MainWindow::timerEvent(QTimerEvent*) {
  controller->Tick();
}

MainWindow::~MainWindow() {
}

