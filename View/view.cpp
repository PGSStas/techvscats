#include "view.h"
#include <QPushButton>
#include "QDebug"
View::View(AbstractController* controller)
    : controller_(controller) {
  start_game_button_ = new QPushButton(this);
  start_game_button_->setText(tr("Начать"));
  connect(start_game_button_, SIGNAL(clicked()),
          this, SLOT(StartGameButtonClick()));

  return_menu_button_ = new QPushButton(this);
  return_menu_button_->setText(tr("Вернуться"));
  connect(return_menu_button_, SIGNAL(clicked()),
          this, SLOT(ReturnMenuButtonClick()));

  wave_status_label = new QLabel(this);
  wave_status_label->move(100, 10);
  wave_status_label->setText(tr("Rounds 0 / 0"));
  show();

  EnableMenuWindow();
  DisableGameWindow();

}

void View::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  // Example of work
  if (is_menu_window) {
    painter.setBrush(Qt::green);
    painter.drawRect(20, 20, 40, 40);
    return;
  }
  painter.setBrush(Qt::red);
  painter.drawRect(20, 20, 40, 40);
}

void View::EnableGameWindow() {
  return_menu_button_->show();
  wave_status_label->show();
}

void View::DisableGameWindow() {
  return_menu_button_->hide();
  wave_status_label->hide();
}

void View::EnableMenuWindow() {
  is_menu_window = true;
  start_game_button_->show();
}

void View::DisableMenuWindow() {
  is_menu_window = false;
  start_game_button_->hide();
}

void View::StartGameButtonClick() {
  controller_->StartGame(0);
}

void View::ReturnMenuButtonClick() {
  controller_->EndGame(1);
}
void View::UpdateRounds(int current_round_nubmer, int rounds_size) {
  wave_status_label->setText(
      "Rounds " + QString::number(current_round_nubmer) + "/"
          + QString::number(rounds_size));
}

