#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller),
      size_handler_(std::make_shared<SizeHandler>()) {
  setMinimumSize(640, 360);

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

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  // Example of work

  Coordinate label_position = size_handler_->GameToWindowCoordinate({300, 10});
  wave_status_label_->move(label_position.x, label_position.y);

  if (window_type == WindowType::kMainMenu) {
    Coordinate start_game_button_position =
        size_handler_->GameToWindowCoordinate({0, 0});
    start_game_button_->move(start_game_button_position.x,
                             start_game_button_position.y);

    painter.setBrush(QColor("#000080"));
    painter.drawRect(0, 0, width(), height());

    painter.setBrush(QColor("#ffffff"));
    Coordinate top_corner = size_handler_->GameToWindowCoordinate({0, 0});
    Size size = size_handler_->GameToWindowSize({1920, 1080});
    painter.drawRect(top_corner.x, top_corner.y, size.width_, size.height_);
  }
  if (window_type == WindowType::kGame) {
    Coordinate return_menu_button_position =
        size_handler_->GameToWindowCoordinate({0, 0});
    return_menu_button_->move(return_menu_button_position.x,
                              return_menu_button_position.y);

    DrawBackground(&painter);

    auto enemies_list = controller_->GetEnemies();
    for (auto& enemy : enemies_list) {
      enemy->Draw(&painter, size_handler_);
    }
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
  Coordinate top_corner =
      size_handler_->GameToWindowCoordinate(Coordinate(0, 0));
  Size rect_size = size_handler_->GameToWindowSize({1920, 1080});
  p->drawRect(top_corner.x, top_corner.y, rect_size.width_, rect_size.height_);

  p->setPen(QPen(Qt::black, 5));
  const auto& roads = controller_->GetRoads();
  for (const auto& road : roads) {
    for (int i = 0; !road.IsEnd(i + 1); i++) {
      Coordinate start_point =
          size_handler_->GameToWindowCoordinate(road.GetNode(i));
      Coordinate end_point =
          size_handler_->GameToWindowCoordinate(road.GetNode(i + 1));
      p->drawLine(start_point.x, start_point.y, end_point.x, end_point.y);
    }
  }
  p->restore();
}

void View::resizeEvent(QResizeEvent*) {
  size_handler_->ChangeSystem(this->width(), this->height());
  repaint();
}
