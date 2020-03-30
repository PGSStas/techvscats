#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller),
      size_handler_(std::make_shared<SizeHandler>(this)) {
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

  Coordinate label_pos = size_handler_->ToWindow(300, 10);
  wave_status_label_->move(label_pos.x, label_pos.y);

  if (window_type == WindowType::kMainMenu) {
    Coordinate start_game_button_pos = size_handler_->ToWindow(0, 0);
    start_game_button_->move(start_game_button_pos.x, start_game_button_pos.y);

    painter.setBrush(QColor("#000080"));
    painter.drawRect(0, 0, width(), height());

    painter.setBrush(QColor("#ffffff"));
    Coordinate top_corner = size_handler_->ToWindow(0, 0);
    Coordinate size = size_handler_->SizeToWindowSize(1920, 1080);
    painter.drawRect(top_corner.x,
                     top_corner.y,
                     size.x,
                     size.y);

    painter.setBrush(Qt::green);
    painter.drawRect(size_handler_->ToWindow(20, 20).x,
                     size_handler_->ToWindow(20, 20).y,
                     size_handler_->SizeToWindowSize(20, 20).x,
                     size_handler_->SizeToWindowSize(20, 20).y);
  }
  if (window_type == WindowType::kGame) {
    Coordinate return_menu_button_pos = size_handler_->ToWindow(0, 0);
    return_menu_button_->move(return_menu_button_pos.x,
                              return_menu_button_pos.y);

    DrawBackground(&painter);

    auto enemies_list = controller_->GetEnemies();
    for (auto& enemy : enemies_list) {
      enemy->Draw(&painter, size_handler_);
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

  p->setBrush(QColor("#000080"));
  p->drawRect(0, 0, width(), height());
  p->setBrush(QColor("#53a661"));
  Coordinate top_corner = size_handler_->ToWindow(Coordinate(0, 0));
  Coordinate rect_size = size_handler_->SizeToWindowSize(1920, 1080);
  p->drawRect(top_corner.x, top_corner.y, rect_size.x, rect_size.y);

  p->setPen(QPen(Qt::black, 5));
  const auto& roads = controller_->GetRoads();
  for (const auto& road : roads) {
    for (int i = 0; !road.IsEnd(i + 1); i++) {
      Coordinate point_1 = size_handler_->ToWindow(road.GetNode(i));
      Coordinate point_2 = size_handler_->ToWindow(road.GetNode(i + 1));
      p->drawLine(point_1.x, point_1.y, point_2.x, point_2.y);
    }
  }
  p->restore();
}

void View::resizeEvent(QResizeEvent* event) {
  size_handler_->ChangeSystem();
  this->repaint();
}
