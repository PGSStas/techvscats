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
  } else {
    DrawBackground(&painter);
    DrawTowers(&painter);
    DrawEnemies(&painter);
    if(is_tower_menu_enabled) {
      tower_menu_->Draw(&painter);
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

void View::DrawTowers(QPainter* p) {
  for(const auto& b : controller_->GetBuildings()) {
    b->Draw(p);
  }
}

void View::DrawEnemies(QPainter* p) {
  auto enemies_list = controller_->GetEnemies();
  for (auto& enemy : enemies_list) {
    enemy->Draw(p);
  }
}

void View::mousePressEvent(QMouseEvent* event) {
  controller_->MousePress(Coordinate(event->x(), event->y()));
}

void View::ShowTowerMenu(std::shared_ptr<TowerMenu> menu) {
  tower_menu_ = menu;
  is_tower_menu_enabled = true;
}

bool View::IsTowerMenuEnabled() {
  return is_tower_menu_enabled;
}

void View::DisableTowerMenu() {
  is_tower_menu_enabled = false;
}

std::shared_ptr<TowerMenu> View::GetTowerMenu() {
  return tower_menu_;
}

