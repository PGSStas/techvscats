#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller) {
  setMouseTracking(true);

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
  controller_timer_id_ = startTimer(kTimeBetweenTicks_);
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
  if (window_type_ == WindowType::kMainMenu) {
    painter.setBrush(Qt::green);
    painter.drawRect(20, 20, 40, 40);
  }

  if (window_type_ == WindowType::kGame) {
    DrawBackground(&painter);
    DrawEnemies(&painter);
    if (is_tower_menu_enabled_) {
      tower_menu_->Draw(&painter, controller_->GetCurrentTime());
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

void View::EnableMenuUi() {
  window_type_ = WindowType::kMainMenu;
  start_game_button_->show();
}

void View::DisableMenuWindow() {
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

  painter->setBrush(QColor("#53a661"));
  painter->drawRect(0, 0, width(), height());

  painter->setPen(QPen(Qt::black, 5));
  const auto& roads = controller_->GetRoads();
  for (const auto& road : roads) {
    for (int i = 0; !road.IsEnd(i + 1); i++) {
      painter->drawLine(road.GetNode(i).x, road.GetNode(i).y,
                        road.GetNode(i + 1).x,
                        road.GetNode(i + 1).y);
    }
  }

  painter->restore();
}

void View::DrawTowers(QPainter* painter) {
  const auto& buildings = controller_->GetBuildings();
  for (const auto& building : buildings) {
    building->Draw(painter);
  }
}

void View::DrawEnemies(QPainter* painter) {
  const auto enemies_list = controller_->GetEnemies();
  for (const auto& enemy : enemies_list) {
    enemy->Draw(painter);
  }
}

void View::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    controller_->MousePress(Coordinate(event->x(), event->y()));
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
    controller_->MouseMove(Coordinate(event->x(), event->y()));
  }
}
