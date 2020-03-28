#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller) {

  start_game_button_ = new QPushButton(this);
  start_game_button_->setText(tr("Начать"));
  auto start_game_button_click = [&]() {
    controller_->StartGame(1);
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
  controller_timer_id_ = startTimer(time_between_ticks_);
  EnableMenuUi();
  DisableGameUi();
}

void View::timerEvent(QTimerEvent* event) {
  if (event->timerId() == controller_timer_id_) {
    controller_->Tick(game_time_.elapsed());
    repaint();
  }
}

void View::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  // Example of work
  if (window_type == WindowType::kMainMenu) {
    painter.setBrush(Qt::green);
    painter.drawRect(20, 20, 40, 40);
  }

  if (window_type == WindowType::kGame) {
    DrawBackground(&painter);
    auto enemies_list = controller_->GetEnemies();
    for (auto& enemy : enemies_list) {
      enemy->Draw(&painter);
    }
  }
}

void View::EnableGameUi()   {
  return_menu_button_->show();
  wave_status_label_->show();
}

void View::DisableGameUi()   {
  return_menu_button_->hide();
  wave_status_label_->hide();
}

void View::EnableMenuUi() {
  window_type = WindowType::kMainMenu;
  start_game_button_->show();
}

void View::DisableMenuWindow() {
  window_type = WindowType::kGame;
  start_game_button_->hide();
}

void View::UpdateRounds(int current_round_nubmer, int number_of_rounds) {
  wave_status_label_->setText(
      "Rounds " + QString::number(current_round_nubmer) + "/"
          + QString::number(number_of_rounds));
}

void View::DrawBackground(QPainter* p) {
  // Test realization. Will be changed.
  p->save();

  p->setBrush(QColor("#53a661"));
  p->drawRect(0, 0, width(), height());

  p->setPen(QPen(Qt::black, 5));
  const auto& roads = controller_->GetRoads();
  for (const auto& road : roads) {
    for (int i = 0; !road.IsEnd(i + 1); i++) {
      p->drawLine(road.GetNode(i).x, road.GetNode(i).y,
                  road.GetNode(i + 1).x,
                  road.GetNode(i + 1).y);
    }
  }

  p->restore();
}
