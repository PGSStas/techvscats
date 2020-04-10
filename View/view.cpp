#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller) {
  setMinimumSize(640, 360);
  setMouseTracking(true);

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

  pause_button_ = new QPushButton(this);
  pause_button_->setText("Пауза");
  connect(pause_button_, &QPushButton::clicked, &View::GamePause);

  wave_status_label_ = new QLabel(this);
  wave_status_label_->setText(tr("Rounds 0 / 0"));
  show();

  game_time_.start();
  controller_timer_id_ = startTimer(kTimeBetweenTicks_);
  EnableMainMenuUi();
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

  Coordinate label_position = size_handler_.GameToWindowCoordinate({300, 10});
  wave_status_label_->move(label_position.x, label_position.y);

  if (window_type_ == WindowType::kMainMenu) {
    Coordinate start_game_button_position =
        size_handler_.GameToWindowCoordinate({0, 0});
    start_game_button_->move(start_game_button_position.x,
                             start_game_button_position.y);

    DrawWindow(&painter, QColor("#ffffff"));
  }
  if (window_type_ == WindowType::kGame) {
    Coordinate return_menu_button_position =
        size_handler_.GameToWindowCoordinate({0, 0});
    return_menu_button_->move(return_menu_button_position.x,
                              return_menu_button_position.y);

    DrawWindow(&painter, QColor("#53a661"));
    DrawBackground(&painter);
    DrawEnemies(&painter);
    DrawProjectiles(&painter);
    if (is_tower_menu_enabled_) {
      tower_menu_->Draw(&painter, size_handler_, game_time_.elapsed());
    }
    DrawTowers(&painter);
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

void View::EnableMainMenuUi() {
  window_type_ = WindowType::kMainMenu;
  start_game_button_->show();
}

void View::DisableMainMenuUi() {
  window_type_ = WindowType::kGame;
  start_game_button_->hide();
}

void View::UpdateRounds(int current_round_nubmer, int number_of_rounds) {
  wave_status_label_->setText(
      "Rounds " + QString::number(current_round_nubmer) + "/"
          + QString::number(number_of_rounds));
}

void View::DrawBackground(QPainter* painter) {
  // Test realization. Will be changed.
  painter->save();

  painter->setPen(QPen(Qt::black, 5));
  const auto& roads = controller_->GetRoads();
  for (const auto& road : roads) {
    for (int i = 0; !road.IsEnd(i + 1); i++) {
      Coordinate start_point =
          size_handler_.GameToWindowCoordinate(road.GetNode(i));
      Coordinate end_point =
          size_handler_.GameToWindowCoordinate(road.GetNode(i + 1));
      painter->drawLine(start_point.x, start_point.y, end_point.x, end_point.y);
    }
  }

  painter->restore();
}

void View::DrawTowers(QPainter* painter) {
  const auto& buildings = controller_->GetBuildings();
  for (const auto& building : buildings) {
    building->Draw(painter, size_handler_);
  }
}

void View::DrawEnemies(QPainter* painter) {
  auto enemies_list = controller_->GetEnemies();
  for (const auto& enemy : enemies_list) {
    enemy->Draw(painter, size_handler_);
  }
}

void View::DrawProjectiles(QPainter* painter) {
  auto projectiles_list = controller_->GetProjectiles();
  for (auto& projectile : projectiles_list) {
    projectile->Draw(painter, size_handler_);
  }
}

void View::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    controller_->MousePress(size_handler_.WindowToGameCoordinate(
        Coordinate(event->x(), event->y())));
  }
}

void View::ShowTowerMenu(const std::shared_ptr<TowerMenu>& menu) {
  tower_menu_ = menu;
  is_tower_menu_enabled_ = true;
}

bool View::IsTowerMenuEnabled() const {
  return is_tower_menu_enabled_;
}

void View::DisableTowerMenu() {
  is_tower_menu_enabled_ = false;
}

std::shared_ptr<TowerMenu> View::GetTowerMenu() {
  return tower_menu_;
}

void View::mouseMoveEvent(QMouseEvent* event) {
  if (window_type_ == WindowType::kGame) {
    controller_->MouseMove(size_handler_.WindowToGameCoordinate(
        Coordinate(event->x(), event->y())));
  }
}

void View::resizeEvent(QResizeEvent*) {
  size_handler_.ChangeSystem(this->width(), this->height());
  repaint();
}

void View::DrawWindow(QPainter* painter, const QBrush& brush) {
  painter->save();

  painter->setBrush(QColor("#000080"));
  painter->drawRect(0, 0, width(), height());
  painter->setBrush(brush);
  Coordinate top_corner =
      size_handler_.GameToWindowCoordinate(Coordinate(0, 0));
  Size rect_size = size_handler_.GameToWindowSize({1920, 1080});
  painter->drawRect(top_corner.x, top_corner.y,
                    rect_size.width, rect_size.height);

  painter->restore();
}

void View::GamePause() {

}
