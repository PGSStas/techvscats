#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller),
      size_handler_(std::make_shared<SizeHandler>()),
      button_handler_(std::make_unique<ButtonHandler>(this)) {
  setMinimumSize(1080, 720);
  setMouseTracking(true);
  button_handler_->CreateButtons(controller);
  show();

  view_timer_.start();
  time_between_ticks_.start();
  controller_timer_id_ = startTimer(kTimeBetweenTicks);
  button_handler_->DisableGameUi();
  button_handler_->DisablePauseMenuUi();
  button_handler_->DisableSettingsUi();
  button_handler_->EnableMainMenuUi();
}

void View::timerEvent(QTimerEvent* event) {
  if (event->timerId() == controller_timer_id_) {
    int delta_time = time_between_ticks_.elapsed();
    time_between_ticks_.restart();
    controller_->Tick(controller_->GetCurrentTime()
                          + delta_time * game_speed_coefficient_);
    repaint();
  }
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.setBrush(QColor("#000000"));
  painter.drawRect(0, 0, width(), height());

  if (button_handler_->GetWindowType() == WindowType::kMainMenu) {
    DrawMainMenu(&painter);
  }
  if (button_handler_->GetWindowType() == WindowType::kGame) {
    DrawGame(&painter);
  }
  if (button_handler_->GetWindowType() == WindowType::kSettings) {
    DrawSettings(&painter);
  }
  if (button_handler_->GetWindowType() == WindowType::kPauseMenu) {
    DrawPauseMenu(&painter);
  }
}

void View::UpdateRounds(int current_round_nubmer, int number_of_rounds) {
  // here will be some kind of round indicator
}

void View::DrawBackground(QPainter* painter) {
  // Test realization. Will be changed.
  painter->save();
  painter->setPen(QPen(Qt::black, 5));
  const auto& roads = controller_->GetRoads();
  for (const auto& road : roads) {
    for (int i = 0; !road.IsEnd(i + 1); i++) {
      Coordinate start_point =
          size_handler_->GameToWindowCoordinate(road.GetNode(i));
      Coordinate end_point =
          size_handler_->GameToWindowCoordinate(road.GetNode(i + 1));
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

void View::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    controller_->MousePress(size_handler_->WindowToGameCoordinate(
        Coordinate(event->x(), event->y())));
  }
}

void View::mouseMoveEvent(QMouseEvent* event) {
  if (button_handler_->GetWindowType() == WindowType::kGame) {
    controller_->MouseMove(size_handler_.WindowToGameCoordinate(
        Coordinate(event->x(), event->y())));
  }
}

void View::resizeEvent(QResizeEvent*) {
  size_handler_->ChangeSystem(this->width(), this->height());
  button_handler_->MoveButtons(size_handler_);
}

void View::DrawMainMenu(QPainter* painter) {
  Coordinate top_corner =
      size_handler_->GameToWindowCoordinate(Coordinate(0, 0));
  Size rect_size = size_handler_->GameToWindowSize({1920, 1080});
  painter->drawImage(QRect(top_corner.x, top_corner.y,
                           rect_size.width, rect_size.height),
                     QImage(":resources/background/main_background.png"));
  button_handler_->DisableSettingsUi();
  button_handler_->DisablePauseMenuUi();
  button_handler_->EnableMainMenuUi();
}

void View::DrawGame(QPainter* painter) {
  Coordinate top_corner =
      size_handler_->GameToWindowCoordinate(Coordinate(0, 0));
  Size rect_size = size_handler_->GameToWindowSize({1920, 1080});
  painter->drawImage(QRect(top_corner.x, top_corner.y,
                           rect_size.width, rect_size.height),
                     QImage(":resources/background/game_background.png"));
  DrawAuras(painter);
  DrawBackground(painter);
  DrawEnemies(painter);
  DrawTowers(painter);

  controller_->GetBase().Draw(painter, size_handler_);
  DrawInterface(painter);

  button_handler_->DisableMainMenuUi();
  button_handler_->DisablePauseMenuUi();
  button_handler_->EnableGameUi();
}

void View::DrawSettings(QPainter* painter) {
  Coordinate top_corner =
      size_handler_->GameToWindowCoordinate(Coordinate(0, 0));
  Size rect_size = size_handler_->GameToWindowSize({1920, 1080});
  painter->drawImage(QRect(top_corner.x, top_corner.y,
                           rect_size.width, rect_size.height),
                     QImage(":resources/background/settings_background.png"));
  button_handler_->DisableMainMenuUi();
  button_handler_->EnableSettingsUi();
}

void View::DrawPauseMenu(QPainter* painter) {
  Coordinate top_corner =
      size_handler_->GameToWindowCoordinate(Coordinate(0, 0));
  Size rect_size = size_handler_->GameToWindowSize({1920, 1080});
  painter->drawImage(QRect(top_corner.x, top_corner.y,
                           rect_size.width, rect_size.height),
                     QImage(":resources/background/pause_menu_background.png"));
  button_handler_->DisableGameUi();
  button_handler_->EnablePauseMenuUi();
}

void View::EnableGameUi() {
  button_handler_->EnableGameUi();
}

void View::DisableGameUi() {
  button_handler_->DisableGameUi();
}

void View::EnableMainMenuUi() {
  button_handler_->EnableMainMenuUi();
}

void View::DisableMainMenuUi() {
  button_handler_->DisableMainMenuUi();
}

void View::DrawAuras(QPainter* painter) {
  const auto& enemies_list = controller_->GetEnemies();
  for (const auto& enemy : enemies_list) {
    enemy->GetAuricField().Draw(painter, size_handler_);
  }

  const auto& buildings_list = controller_->GetBuildings();
  for (const auto& building : buildings_list) {
    building->GetAuricField().Draw(painter, size_handler_);
  }
}

void View::DrawInterface(QPainter* painter) {
  auto enemies_list = controller_->GetEnemies();

  for (auto& enemy : enemies_list) {
    enemy->DrawHealthBar(painter, size_handler_);
    enemy->GetAppliedEffect()->DrawEffectsIcons(painter,
                                                size_handler_,
                                                enemy->GetPosition());
  }

  const auto& buildings_list = controller_->GetBuildings();
  for (const auto& building : buildings_list) {
    building->GetAppliedEffect()->DrawEffectsIcons(painter,
                                                   size_handler_,
                                                   building->GetPosition());
  }

  if (is_tower_menu_enabled_) {
    tower_menu_->Draw(painter, size_handler_, controller_->GetCurrentTime());
  }
}
