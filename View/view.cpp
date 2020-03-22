#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller) {

  start_game_button_ = new QPushButton(this);
  start_game_button_->setText(tr("Начать"));
  auto start_game_button_click = [&]() {
    controller_->StartGame(0);
  };
  connect(start_game_button_, &QPushButton::clicked, start_game_button_click);

  return_menu_button_ = new QPushButton(this);
  return_menu_button_->setText(tr("Вернуться"));
  auto return_menu_button_click = [&]() {
    controller_->EndGame(Exit::kLose);
  };
  connect(return_menu_button_, &QPushButton::clicked, return_menu_button_click);

  wave_status_label_ = new QLabel(this);
  wave_status_label_->move(100, 10);
  wave_status_label_->setText(tr("Rounds 0 / 0"));
  show();

  game_time_.start();
  timer_controller_id_ = startTimer(time_between_ticks_);
  EnableMenuUi();
  DisableGameUi();
}

void View::timerEvent(QTimerEvent* event) {
  if (event->timerId()) {
    controller_->Tick(game_time_.elapsed());
    repaint();
  }
}

void View::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  // Example of work
  if (is_menu_window_enabled) {
    painter.setBrush(Qt::green);
    painter.drawRect(20, 20, 40, 40);
    return;
  }
  painter.setBrush(Qt::red);
  painter.drawRect(20, 20, 40, 40);
  auto* enemyes_list = controller_->GetEnemies();
  for (auto& enemy : *enemyes_list) {
    enemy->Draw(&painter);
  }
}

void View::EnableGameUi() {
  return_menu_button_->show();
  wave_status_label_->show();
}

void View::DisableGameUi() {
  return_menu_button_->hide();
  wave_status_label_->hide();
}

void View::EnableMenuUi() {
  is_menu_window_enabled = true;
  start_game_button_->show();
}

void View::DisableMenuWindow() {
  is_menu_window_enabled = false;
  start_game_button_->hide();
}

void View::UpdateRounds(int current_round_nubmer, int rounds_size) {
  wave_status_label_->setText(
      "Rounds " + QString::number(current_round_nubmer) + "/"
          + QString::number(rounds_size));
}

