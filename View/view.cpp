#include "View.h"
#include <QPushButton>

View::View(AbstractController* controller) : controller_(controller) {
  show();
  controller->StartGame(0);
}

void View::paintEvent(QPaintEvent* event) {
  // Example of work
  QPainter painter(this);
  painter.setBrush(Qt::red);
  painter.drawRect(0, 0, 500, 500);
  //
}
