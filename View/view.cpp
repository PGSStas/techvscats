#include "view.h"
#include <QPushButton>

View::View(AbstractController* controller)
    : controller_(controller) {
  show();
}

void View::paintEvent(QPaintEvent* event) {
  // Example of work
  QPainter painter(this);
  painter.setBrush(Qt::red);
  painter.drawRect(0, 0, 500, 500);
  //
}

void View::EnableGameWindow() {
  is_game_window = true;
  wave_status_label = new QLabel(this);
  wave_status_label->move(10, 10);
  wave_status_label->setText(tr("Rounds : "));
}
void View::DisableGameWindow() {
  is_game_window=false;
  delete wave_status_label;
}



