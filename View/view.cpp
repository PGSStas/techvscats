#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller),
      size_handler_(),
      button_handler_(ButtonHandler(this, controller, 0)),
      tower_menu_(this) {
  setMinimumSize(1280, 720);
  setMouseTracking(true);
  show();

  view_timer_.start();
  time_between_ticks_.start();
  controller_timer_id_ = startTimer(constants::kTimeBetweenTicks);
  button_handler_.SetGameUiVisible(false);
  button_handler_.SetPauseMenuUiVisible(false);
  button_handler_.SetSettingsUiVisible(false);
  button_handler_.SetMainMenuUiVisible(true);
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  Coordinate origin = size_handler_.GameToWindowCoordinate({0, 0});
  painter.drawImage(
      origin.x, origin.y, controller_->GetBackground(
          button_handler_.GetWindowType()).GetCurrentFrame());

  auto window_type = button_handler_.GetWindowType();
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
  button_handler_.SetSettingsUiVisible(false);
  button_handler_.SetPauseMenuUiVisible(false);
  button_handler_.SetMainMenuUiVisible(true);
}

void View::DrawGame(QPainter* painter) {
  DrawEnemies(painter);
  DrawProjectiles(painter);
  DrawTowers(painter);
  DrawAdditionalInfo(painter);
  DrawEndgameMessage(painter);

  button_handler_.SetMainMenuUiVisible(false);
  button_handler_.SetPauseMenuUiVisible(false);
  button_handler_.SetGameUiVisible(true);
}

void View::DrawSettings(QPainter*) {
  button_handler_.SetMainMenuUiVisible(false);
  button_handler_.SetSettingsUiVisible(true);
}

void View::DrawPauseMenu(QPainter*) {
  button_handler_.SetGameUiVisible(false);
  button_handler_.SetPauseMenuUiVisible(true);
}

void View::DrawEndgameMessage(QPainter* painter) {
  if (controller_->GetCurrentStatus() != Exit::kPlay) {
    painter->save();

    alpha_channel_ += delta_alpha_;
    if (alpha_channel_ < 0 || alpha_channel_ > 255) {
      delta_alpha_ *= -1;
      alpha_channel_ += 2 * delta_alpha_;
    }
    QColor color = Qt::white;
    color.setAlpha(alpha_channel_);
    painter->setPen(color);

    auto font = painter->font();
    font.setPixelSize(size_handler_.GameToWindowLength(constants::kFontSize));
    font.setFamily(QFontDatabase::applicationFontFamilies(0).at(0));
    painter->setFont(font);

    Coordinate point = size_handler_.GameToWindowCoordinate(
        {message_position_.x - endgame_message_.size() * constants::kFontSize,
         message_position_.y});
    painter->drawText(point.x, point.y, endgame_message_);

    painter->restore();
  }
}

void View::DrawTowers(QPainter* painter) {
  controller_->GetBase().Draw(painter, size_handler_);

  const auto& buildings = controller_->GetBuildings();
  for (const auto& building : buildings) {
    building->Draw(painter, size_handler_);
  }
}

const SizeHandler& View::GetSizeHandler() const {
  return size_handler_;
}

bool View::IsTowerMenuEnabled() const {
  return tower_menu_.IsEnable();
}

int View::GetRealTime() const {
  return view_timer_.elapsed();
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

void View::ReplaceTowerMenu(Coordinate position, int carrier_building_index,
                            const std::vector<int>& possible_buildings_id,
                            int carrier_id) {
  tower_menu_.Recreate(position, carrier_building_index,
                       possible_buildings_id, carrier_id, size_handler_);
}

void View::DisableTowerMenu() {
  tower_menu_.Disable(false);
}

void View::mouseReleaseEvent(QMouseEvent* event) {
  if (button_handler_.GetWindowType() == WindowType::kGame) {
    controller_->MouseEvent(size_handler_.WindowToGameCoordinate(
        Coordinate(event->x(), event->y())), false);
  }
}

void View::mousePressEvent(QMouseEvent* event) {
  if (button_handler_.GetWindowType() == WindowType::kGame) {
    controller_->MouseEvent(size_handler_.WindowToGameCoordinate(
        Coordinate(event->x(), event->y())), true);
  }
}

void View::resizeEvent(QResizeEvent*) {
  size_handler_.ChangeSystem(this->width(), this->height());
  button_handler_.RescaleButtons(size_handler_);
  tower_menu_.RescaleButtons(size_handler_);
  controller_->RescaleObjects(size_handler_);
}

void View::EnableGameUi() {
  controller_->RescaleObjects(size_handler_);
  DisableTowerMenu();
  button_handler_.SetGameUiVisible(true);
}

void View::DisableGameUi() {
  button_handler_.SetGameUiVisible(false);
}

void View::EnableMainMenuUi() {
  button_handler_.SetMainMenuUiVisible(true);
}

void View::DrawAdditionalInfo(QPainter* painter) {
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

  const auto& text_notifications = controller_->GetTextNotifications();
  for (auto& notification : text_notifications) {
    notification.Draw(painter, size_handler_);
  }

  if (tower_menu_.IsEnable()) {
    tower_menu_.DrawAdditionalInfo(painter, size_handler_,
                                   controller_->GetBuildingById(
                                       tower_menu_.GetSellectedTowerId()));
  }
}

void View::DisableMainMenuUi() {
  button_handler_.SetMainMenuUiVisible(false);
}

void View::timerEvent(QTimerEvent* event) {
  if (event->timerId() == controller_timer_id_) {
    int delta_time = time_between_ticks_.elapsed();
    time_between_ticks_.restart();
    controller_->Tick(controller_->GetCurrentTime()
                          + delta_time * game_speed_coefficient_);
    tower_menu_.Tick(size_handler_, delta_time);
    if (tower_menu_.IsWantToReplace()) {
      controller_->SetBuilding(
          tower_menu_.GetCarrierIndex(),
          tower_menu_.GetSellectedTowerId());
      tower_menu_.SetIsWantToReplaceToFalse();
    }
    repaint();
  }
}

void View::UpdateRounds(int, int) {
  // Here will be some kind of round indicator.
}

void View::ChangeGameSpeed(Speed speed) {
  game_speed_coefficient_ = static_cast<int>(speed);
}
