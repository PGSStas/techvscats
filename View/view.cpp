#include "view.h"

View::View(AbstractController* controller)
    : controller_(controller),
      size_handler_(),
      tower_menu_(this) {
  setWindowIcon(QIcon(":resources/images/icon.png"));
  setWindowTitle("Tech vs Cats");
  setMinimumSize(960, 540);

  QSettings settings(constants::kCompanyName, constants::kApplicationName);
#ifdef Q_OS_ANDROID
  showFullScreen();
#else
  if (settings.value("fullscreen", true).toBool()) {
    showFullScreen();
  } else {
    showNormal();
  }
#endif
  setWindowTitle("Tech vs Cats");
  setWindowIcon(QIcon(":resources/images/icon.png"));

  size_handler_.ChangeSystem(width(), height());
  setMouseTracking(true);
  setFocusPolicy(Qt::ClickFocus);

  view_timer_.start();
  time_between_ticks_.start();
  controller_timer_id_ = startTimer(constants::kTimeBetweenTicks);

  connect(qApp, &QApplication::applicationStateChanged, [this] {
    if (qApp->applicationState() == Qt::ApplicationActive) {
      controller_->ResumeMusic();
    }
    if (qApp->applicationState() == Qt::ApplicationHidden ||
        qApp->applicationState() == Qt::ApplicationSuspended) {
      controller_->PauseMusic();
    }
  });
}

void View::SecondConstructorPart() {
  button_handler_ = std::make_shared<ButtonHandler>(this, controller_, 0);
  global_chat_ = std::make_shared<GlobalChat>(this);
  Resize();
  button_handler_->SetGameUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
  button_handler_->SetSettingsUiVisible(false);
  button_handler_->SetMainMenuUiVisible(false);
  button_handler_->SetTitlesVisible(false);
  global_chat_->SetVisible(false);
  is_model_loaded_ = true;
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  if (!is_model_loaded_) {
    double coefficient = std::min(width() / 16, height() / 9);
    Size size = {16 * coefficient, 9 * coefficient};
    Coordinate origin = {(width() - 16 * coefficient) / 2,
                         (height() - 9 * coefficient) / 2};
    painter.fillRect(0, 0, width(), height(), Qt::white);
    painter.drawPixmap(origin.x, origin.y, logo_.scaled(size.width,
                                                        size.height));
    return;
  }

  Coordinate origin = size_handler_.GameToWindowCoordinate({0, 0});
  painter.drawPixmap(origin.x, origin.y, controller_->GetBackground(
      button_handler_->GetWindowType()).GetCurrentFrame());

  window_type_ = button_handler_->GetWindowType();
  switch (window_type_) {
    case WindowType::kMainMenu: {
      DrawMainMenu(&painter);
      break;
    }
    case WindowType::kGame: {
      DrawGame(&painter);
      break;
    }
    case WindowType::kSettings: {
      DrawSettings(&painter);
      break;
    }
    case WindowType::kPauseMenu: {
      DrawPauseMenu(&painter);
      break;
    }
    default: break;
  }
  DrawTextNotification(&painter);
  DrawEmptyZones(&painter);
}

void View::Resize() {
  size_handler_.ChangeSystem(this->width(), this->height());
  button_handler_->RescaleButtons(size_handler_);
  tower_menu_.RescaleButtons(size_handler_);
  global_chat_->RescaleChat(size_handler_);
  controller_->RescaleObjects(size_handler_);
}

void View::DrawEmptyZones(QPainter* painter) {
  painter->save();
  const QPixmap& image = controller_->GetEmptyZoneTexture(
      button_handler_->GetWindowType());
  Size horizontal_zone =
      Size(width(), size_handler_.GameToWindowCoordinate({0, 0}).y);
  painter->fillRect(0, 0, horizontal_zone.width, horizontal_zone.height, image);
  painter->fillRect(
      0, size_handler_.GameToWindowCoordinate(
          {0, constants::kGameHeight}).y + 1,
      horizontal_zone.width + 2, horizontal_zone.height + 2, image);
  Size vertical_zone =
      Size(size_handler_.GameToWindowCoordinate({0, 0}).x, height());
  painter->fillRect(0, 0, vertical_zone.width, vertical_zone.height, image);
  painter->fillRect(
      size_handler_.GameToWindowCoordinate({constants::kGameWidth, 0}).x,
      0, vertical_zone.width + 2, vertical_zone.height + 2, image);

  painter->restore();
}

void View::DrawMainMenu(QPainter*) {
  button_handler_->SetSettingsUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
  button_handler_->SetMainMenuUiVisible(true);
  global_chat_->SetVisible(true);
}

void View::DrawGame(QPainter* painter) {
  controller_->RescaleObjects(size_handler_);
  DrawTowersAuraAndRange(painter);
  DrawGameObjects(painter);
  DrawProjectiles(painter);
  DrawBars(painter);
  controller_->GetBase().Draw(painter, size_handler_);
  DrawParticles(painter);
  DrawAdditionalInfo(painter);
  DrawEndgameMessage(painter);

  button_handler_->SetMainMenuUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
  button_handler_->SetGameUiVisible(true);
}

void View::DrawSettings(QPainter*) {
  button_handler_->SetTitlesVisible(false);
  button_handler_->SetSettingsUiVisible(true);
  button_handler_->SetMainMenuUiVisible(false);
}

void View::DrawPauseMenu(QPainter*) {
  button_handler_->SetGameUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(true);
  tower_menu_.Hide(true);
}

void View::DrawEndgameMessage(QPainter* painter) {
  if (controller_->GetCurrentStatus() == GameStatus::kLose) {
    tower_menu_.Hide(true);
    painter->save();

    alpha_channel_ += delta_alpha_;
    // Change the way, that text blinks. From solid to
    // transparent or vice versa.
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

    QFontMetrics metrics(font);

    Coordinate point = size_handler_.GameToWindowCoordinate(
        {message_position_.x - metrics.boundingRect(
            0, 0,
            constants::kGameWidth, constants::kGameHeight,
            Qt::AlignLeft, kEndgameMessage).width() / 2,
         message_position_.y});
    painter->drawText(point.x, point.y, kEndgameMessage);

    painter->restore();
  } else {
    tower_menu_.Hide(false);
  }
}

void View::DrawTextNotification(QPainter* painter) {
  const auto& text_notifications = controller_->GetTextNotifications();
  for (auto& notification : text_notifications) {
    notification.Draw(painter, size_handler_);
  }
}

void View::DrawGameObjects(QPainter* painter) {
  std::list<GameObject*> objects;
  const auto& buildings = controller_->GetBuildings();
  for (const auto& building : buildings) {
    objects.push_back(building.get());
  }

  const auto& enemies_list = controller_->GetEnemies();
  for (const auto& enemy : enemies_list) {
    objects.push_back(enemy.get());
  }

  objects.sort([](GameObject* a, GameObject* b) {
    return a->GetPosition().y < b->GetPosition().y;
  });

  for (auto object : objects) {
    object->Draw(painter, size_handler_);
  }
}

bool View::IsTowerMenuEnabled() const {
  return tower_menu_.IsEnable();
}

int View::GetRealTime() const {
  return view_timer_.elapsed();
}

void View::DrawTowersAuraAndRange(QPainter* painter) {
  if (tower_menu_.IsEnable()) {
    if (tower_menu_.GetChosenButtonId() != -1) {
      tower_menu_.DrawTowersAuraAndRange(painter, size_handler_,
                                         controller_->GetBuildingById(
                                             tower_menu_.GetChosenButtonId()));
    } else {
      tower_menu_.DrawTowersAuraAndRange(painter, size_handler_,
                                         *controller_->GetBuildings()[
                                             tower_menu_.GetTownerIndex()]);
    }
  }
}

void View::DrawProjectiles(QPainter* painter) {
  auto projectiles_list = controller_->GetProjectiles();
  for (auto& projectile : projectiles_list) {
    projectile->Draw(painter, size_handler_);
  }
}

void View::DrawParticles(QPainter* painter) {
  const auto& particles = controller_->GetParticles();
  for (auto particle = particles.rbegin(); particle != particles.rend();
       particle++) {
    particle->Draw(painter, size_handler_);
  }
}

void View::ReplaceTowerMenu(Coordinate position, int carrier_building_index,
                            const std::vector<int>& possible_buildings_id,
                            int carrier_id, int total_cost) {
  tower_menu_.Recreate(position, carrier_building_index,
                       possible_buildings_id, carrier_id,
                       size_handler_, total_cost);
}

void View::DisableTowerMenu(bool is_fast_disable) {
  tower_menu_.Close(is_fast_disable);
}

void View::mouseReleaseEvent(QMouseEvent* event) {
  if (!is_model_loaded_) {
    return;
  }
  if (button_handler_->GetWindowType() == WindowType::kGame) {
    controller_->MouseEvent(size_handler_.WindowToGameCoordinate(
        Coordinate(event->x(), event->y())), false);
  }
}

void View::mousePressEvent(QMouseEvent* event) {
  if (!is_model_loaded_) {
    return;
  }
  if (button_handler_->GetWindowType() == WindowType::kGame) {
    controller_->MouseEvent(size_handler_.WindowToGameCoordinate(
        Coordinate(event->x(), event->y())), true);
  }
}
void View::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Space) {
    if (game_speed_coefficient_ == 0 && previous_game_speed_coefficient == 1) {
      button_handler_->SetSpeed(static_cast<int>(Speed::kNormalSpeed));
    } else if (game_speed_coefficient_ == 0
        && previous_game_speed_coefficient == 2) {
      button_handler_->SetSpeed(static_cast<int>(Speed::kDoubleSpeed));
    } else {
      button_handler_->SetSpeed(static_cast<int>(Speed::kZeroSpeed));
    }
  }
  if (event->key() == Qt::Key_Escape &&
      button_handler_->GetWindowType() == WindowType::kTitles) {
    button_handler_->SetWindowType(WindowType::kMainMenu);
    controller_->EndTitles();
  }
}

void View::resizeEvent(QResizeEvent*) {
  if (!is_model_loaded_) {
    return;
  }
  Resize();
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

  controller_->GetBase().DrawUI(painter, size_handler_);

  Coordinate origin = size_handler_.GameToWindowCoordinate({0, 0});
  painter->drawPixmap(origin.x, origin.y,
                      controller_->GetInterface().GetCurrentFrame());
  DrawRoundInfo(painter);

  if (tower_menu_.IsEnable()) {
    int button_id = tower_menu_.GetChosenButtonId();
    if (button_id != -1) {
      tower_menu_.DrawInfoField(painter, size_handler_,
                                controller_->GetBuildingById(button_id));
    } else {
      button_id = tower_menu_.GetTownerIndex();
      tower_menu_.DrawInfoField(painter, size_handler_,
                                *controller_->GetBuildings()[button_id]);
    }
  }

  painter->restore();
}

void View::DisableMainMenuUi() {
  button_handler_->SetMainMenuUiVisible(false);
}

void View::ChangeChatStyle() {
  global_chat_->ChangeStyle();
  if (controller_->GetClient()->IsOnline()) {
    global_chat_->Clear();
  }
}

void View::AddGlobalChatMessage(const QStringList& message) {
  global_chat_->ReceiveNewMessages(message);
}

void View::timerEvent(QTimerEvent* event) {
  if (event->timerId() == controller_timer_id_) {
    if (!is_model_loaded_) {
      repaint();
      controller_->SecondConstructorPart();
      return;
    }
    int delta_time_ = time_between_ticks_.elapsed();
    time_between_ticks_.restart();
    controller_->Tick(controller_->GetCurrentTime()
                          + delta_time_ * game_speed_coefficient_);
    // TowerMenu tick
    tower_menu_.Tick(size_handler_);
    if (tower_menu_.IsWantToReplace()) {
      controller_->SetBuilding(
          tower_menu_.GetTownerIndex(),
          tower_menu_.GetSellectedTowerId());
      tower_menu_.SetIsWantToReplaceToFalse();
    }
    // Global ChatTick
    global_chat_->Tick(size_handler_, delta_time_);
    if (!global_chat_->IsMessagesQueueEmpty()) {
      controller_->GetClient()->NewClientMessage(
          global_chat_->GetMessageToSend());
      global_chat_->PopMessageQueue();
    }

    button_handler_->UpdateButtonsStatus(
        controller_->GetClient()->IsOnline(),
        controller_->GetClient()->IsRegistered());

    repaint();
  }
}

void View::ChangeGameSpeed(Speed speed, bool notify_button_handler) {
  previous_game_speed_coefficient = game_speed_coefficient_;
  game_speed_coefficient_ = static_cast<int>(speed);
  if (!notify_button_handler) {
    button_handler_->SetSpeed(static_cast<int>(speed));
  }
}

void View::ClearChat() {
  global_chat_->Clear();
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
  QString round_info = tr(" ") +
      QString::number(controller_->GetCurrentRoundNumber()) + " " + tr("/") +
      " " + QString::number(controller_->GetRoundsCount());
  painter->drawText(round_info_position.x, round_info_position.y,
                    round_info_size.width, round_info_size.height,
                    Qt::AlignCenter, round_info);
}

void View::DrawBars(QPainter* painter) {
  const auto& enemies_list = controller_->GetEnemies();
  for (auto& enemy : enemies_list) {
    enemy->DrawHealthBar(painter, size_handler_);
    if (button_handler_->IsEffectToggleActive()) {
      enemy->GetAppliedEffect()->DrawEffectsIcons(painter, size_handler_,
                                                  enemy->GetPosition(),
                                                  enemy->GetSize());
    }
  }

  if (button_handler_->IsEffectToggleActive()) {
    const auto& buildings_list = controller_->GetBuildings();
    for (const auto& building : buildings_list) {
      building->GetAppliedEffect()->DrawEffectsIcons(painter, size_handler_,
                                                     building->GetPosition(),
                                                     building->GetSize());
    }
  }
}

int View::GetChosenLevel() const {
  return button_handler_->GetCurrentLevel();
}

void View::UnlockLevels() {
  QSettings settings;
  settings.setValue("levels_passed", button_handler_->GetMaxLevel());
  button_handler_->SetCurrentLevel(button_handler_->GetMaxLevel());
}

void View::StartTitles() {
  button_handler_->SetSettingsUiVisible(false);
  global_chat_->SetVisible(false);
  tower_menu_.Close(true);
}

void View::EndTitles() {
  button_handler_->SetTitlesVisible(false);
  button_handler_->SetMainMenuUiVisible(true);
  global_chat_->SetVisible(true);
}

void View::ShowSettingsButton() {
  button_handler_->SetTitlesVisible(true);
}

void View::ShowNextLevelButton() {
  button_handler_->SetNextLevelButtonVisible(true);
}

void View::BeginNextLevel() {
  controller_->EndGame();
  controller_->StartGame(button_handler_->GetCurrentLevel());
  button_handler_->SetNextLevelButtonVisible(false);
  button_handler_->SetSpeedButtonsState(Speed::kNormalSpeed);
}
