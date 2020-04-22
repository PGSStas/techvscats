#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller),
      size_handler_(),
      button_handler_(std::make_unique<ButtonHandler>(this, controller)) {
  setMinimumSize(1080, 720);
  setMouseTracking(true);
  show();

  view_timer_.start();
  time_between_ticks_.start();
  controller_timer_id_ = startTimer(constants::kTimeBetweenTicks);
  button_handler_->SetGameUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
  button_handler_->SetSettingsUiVisible(false);
  button_handler_->SetMainMenuUiVisible(true);
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);

  Coordinate origin = size_handler_.GameToWindowCoordinate({0, 0});
  Size window_size =
      size_handler_.GameToWindowSize(size_handler_.GetGameSize());
  painter.setBrush(QColor("#ffffff"));
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

void View::DrawMainMenu(QPainter* painter) {
  Coordinate top_corner =
      size_handler_.GameToWindowCoordinate(Coordinate(0, 0));
  Size rect_size = size_handler_.GameToWindowSize({1920, 1080});
  painter->drawImage(QRect(top_corner.x, top_corner.y,
                           rect_size.width, rect_size.height),
                     QImage(":resources/background/main_background.png"));
  button_handler_->SetSettingsUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
  button_handler_->SetMainMenuUiVisible(true);
}

void View::DrawGame(QPainter* painter) {
  DrawAuras(painter);
  DrawEnemies(painter);
  DrawProjectiles(painter);
  DrawTowers(painter);

  Coordinate origin = size_handler_.GameToWindowCoordinate({0, 0});
  painter->drawImage(origin.x, origin.y,
                    controller_->GetMap().GetCurrentFrame());
  DrawInterface(painter);

  button_handler_->SetMainMenuUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
  button_handler_->SetGameUiVisible(true);
}

void View::DrawSettings(QPainter* painter) {
  Coordinate top_corner =
      size_handler_.GameToWindowCoordinate(Coordinate(0, 0));
  Size rect_size = size_handler_.GameToWindowSize({1920, 1080});
  painter->drawImage(QRect(top_corner.x, top_corner.y,
                           rect_size.width, rect_size.height),
                     QImage(":resources/background/settings_background.png"));
  button_handler_->SetMainMenuUiVisible(false);
  button_handler_->SetSettingsUiVisible(true);
}

void View::DrawPauseMenu(QPainter* painter) {
  Coordinate top_corner =
      size_handler_.GameToWindowCoordinate(Coordinate(0, 0));
  Size rect_size = size_handler_.GameToWindowSize({1920, 1080});
  painter->drawImage(QRect(top_corner.x, top_corner.y,
                           rect_size.width, rect_size.height),
                     QImage(":resources/background/pause_menu_background.png"));
  button_handler_->SetGameUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(true);
}

void View::DrawTowers(QPainter* painter) {
  controller_->GetBase().Draw(painter, size_handler_);

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

void View::DrawProjectiles(QPainter* painter) {
  auto projectiles_list = controller_->GetProjectiles();
  for (auto& projectile : projectiles_list) {
    projectile->Draw(painter, size_handler_);
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
    controller_->MousePress(size_handler_.WindowToGameCoordinate(
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
  size_handler_.ChangeSystem(this->width(), this->height());
  button_handler_->SetButtonsGeometry(size_handler_);
  if (button_handler_->GetWindowType() == WindowType::kGame) {
    controller_->RescaleObjects(size_handler_);
  }
}

void View::EnableGameUi() {
  button_handler_->SetGameUiVisible(true);
}

void View::DisableGameUi() {
  button_handler_->SetGameUiVisible(false);
}

void View::EnableMainMenuUi() {
  button_handler_->SetMainMenuUiVisible(true);
}

void View::DisableMainMenuUi() {
  button_handler_->SetMainMenuUiVisible(false);
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

void View::UpdateRounds(int current_round_nubmer, int number_of_rounds) {
  // here will be some kind of round indicator
}

void View::ChangeGameSpeed(Speed speed) {
  game_speed_coefficient_ = static_cast<int>(speed);
}
