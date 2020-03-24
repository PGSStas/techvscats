#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller),
      size_handler_(std::make_unique<SizeHandler>(this)) {
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
  if (event->timerId() == timer_controller_id_) {
    controller_->Tick(game_time_.elapsed());
    repaint();
  }
}

void View::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  // Example of work
  if (window_type == WindowType::kMainMenu) {
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
    DrawBackground(&painter);
    auto enemies_list = controller_->GetEnemies();
    for (auto& enemy : enemies_list) {
      enemy->Draw(&painter, size_handler_);
    }
  }
  // // test part
  // painter.setBrush(QColor("#fde910"));
  // Coordinate top_corner = size_handler_->ToWindow(100, 100);
  // Coordinate bottom_corner = size_handler_->ToWindow(300, 300);
  // painter.drawRect(top_corner.x,
  //                  top_corner.y,
  //                  bottom_corner.x - top_corner.x,
  //                  bottom_corner.y - top_corner.y);
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

void View::mousePressEvent(QMouseEvent* event) {
  resize(940, 360);
  qDebug() << event->x() << " " << event->y();
  qDebug() << size_handler_->ToGame(event->x(), event->y()).x << " "
             << size_handler_->ToGame(event->x(), event->y()).y;
}
