#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller),
      size_handler_(),
      button_handler_(std::make_unique<ButtonHandler>(this, controller, 0)) {
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
  painter.drawImage(
      origin.x, origin.y, controller_->GetBackground(
          button_handler_->GetWindowType()).GetCurrentFrame());

  auto window_type = button_handler_->GetWindowType();
  switch (window_type) {
    case WindowType::kMainMenu:DrawMainMenu(&painter);
      break;
    case WindowType::kGame:DrawGame(&painter);
      break;
    case WindowType::kSettings:DrawSettings(&painter);
      break;
    case WindowType::kPauseMenu:DrawPauseMenu(&painter);
      break;
  }
  DrawEmptyZones(&painter);
}

void View::DrawEmptyZones(QPainter* painter) {
  painter->save();
  Size horizontal_zone =
      Size(width(), size_handler_.GameToWindowCoordinate({0, 0}).y);
  painter->fillRect(
      0, 0, horizontal_zone.width, horizontal_zone.height, QColor("#ffffff"));
  painter->fillRect(
      0,
      size_handler_.GameToWindowCoordinate({0, constants::kGameHeight}).y - 1,
      horizontal_zone.width + 2, horizontal_zone.height + 2, QColor("#ffffff"));
  Size vertical_zone =
      Size(size_handler_.GameToWindowCoordinate({0, 0}).x, height());
  painter->fillRect(
      0, 0, vertical_zone.width, vertical_zone.height, QColor("#ffffff"));
  painter->fillRect(
      size_handler_.GameToWindowCoordinate({constants::kGameWidth, 0}).x,
      0, vertical_zone.width + 2, vertical_zone.height + 2, QColor("#ffffff"));

  painter->restore();
}

void View::DrawMainMenu(QPainter*) {
  button_handler_->SetSettingsUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
  button_handler_->SetMainMenuUiVisible(true);
}

void View::DrawGame(QPainter* painter) {
  DrawEnemies(painter);
  DrawProjectiles(painter);
  DrawTowers(painter);
  controller_->GetBase().Draw(painter, size_handler_);
  DrawAdditionalInfo(painter);

  button_handler_->SetMainMenuUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
  button_handler_->SetGameUiVisible(true);
}

void View::DrawSettings(QPainter*) {
  button_handler_->SetMainMenuUiVisible(false);
  button_handler_->SetSettingsUiVisible(true);
}

void View::DrawPauseMenu(QPainter*) {
  button_handler_->SetGameUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(true);
}

void View::DrawTowers(QPainter* painter) {
  const auto& buildings = controller_->GetBuildings();
  for (const auto& building : buildings) {
    building->Draw(painter, size_handler_);
  }
}

const SizeHandler& View::GetSizeHandler() const {
  return size_handler_;
}

bool View::IsTowerMenuEnabled() const {
  return is_tower_menu_enabled_;
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

void View::ShowTowerMenu(const std::shared_ptr<TowerMenu>& menu) {
  tower_menu_ = menu;
  is_tower_menu_enabled_ = true;
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
  button_handler_->RescaleButtons(size_handler_);
  controller_->RescaleObjects(size_handler_);
}

void View::EnableGameUi() {
  controller_->RescaleObjects(size_handler_);
  DisableTowerMenu();
  button_handler_->SetGameUiVisible(true);
}

void View::DisableGameUi() {
  button_handler_->SetGameUiVisible(false);
}

void View::EnableMainMenuUi() {
  button_handler_->SetMainMenuUiVisible(true);
}

void View::DrawAdditionalInfo(QPainter* painter) {
  painter->save();

  const auto& enemies_list = controller_->GetEnemies();
  for (auto& enemy : enemies_list) {
    enemy->DrawHealthBar(painter, size_handler_);
    enemy->GetAppliedEffect()->DrawEffectsIcons(painter, size_handler_,
                                                enemy->GetPosition(),
                                                enemy->GetSize());
  }

  const auto& buildings_list = controller_->GetBuildings();
  for (const auto& building : buildings_list) {
    building->GetAppliedEffect()->DrawEffectsIcons(painter, size_handler_,
                                                   building->GetPosition(),
                                                   building->GetSize());
  }

  controller_->GetBase().DrawUI(painter, size_handler_);

  if (is_tower_menu_enabled_) {
    tower_menu_->Draw(painter, size_handler_, controller_->GetCurrentTime());
  }

  Coordinate origin = size_handler_.GameToWindowCoordinate({0, 0});
  painter->drawImage(origin.x, origin.y,
                     controller_->GetInterface().GetCurrentFrame());

  DrawRoundInfo(painter);

  const auto& text_notifications = controller_->GetTextNotifications();
  for (auto& notification : text_notifications) {
    notification.Draw(painter, size_handler_);
  }

  painter->restore();
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

void View::UpdateRounds(int current_round_number, int number_of_rounds) {
  // Here will be some kind of round indicator.
}

void View::ChangeGameSpeed(Speed speed) {
  game_speed_coefficient_ = static_cast<int>(speed);
}

void View::DrawRoundInfo(QPainter* painter) {
  auto font = painter->font();
  font.setPixelSize(size_handler_.GameToWindowLength(constants::kFontSize));
  font.setFamily(QFontDatabase::applicationFontFamilies(0).at(0));
  painter->setFont(font);
  painter->setPen(Qt::white);

  Coordinate round_info_position = size_handler_.GameToWindowCoordinate(
      kRoundPosition);
  Size round_info_size = size_handler_.GameToWindowSize(kRoundSize);
  QString round_info = tr("Раунд") + " " +
      QString::number(controller_->GetCurrentRoundNumber()) + " " + tr("из") +
      " " + QString::number(controller_->GetRoundsCount());
  painter->drawText(round_info_position.x, round_info_position.y,
                    round_info_size.width, round_info_size.height,
                    Qt::AlignCenter, round_info);
}
