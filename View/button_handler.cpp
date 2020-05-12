#include "button_handler.h"

ButtonHandler::ButtonHandler(QMainWindow* main_window,
                             AbstractController* controller, int font_id)
    : QObject(main_window), main_window_(main_window), controller_(controller),
      font_id_(font_id) {
  CreateButtons();
  SetLevelNumber(1);
  SetMaxLevel(1);
  window_type_ = WindowType::kMainMenu;
}

void ButtonHandler::CreateButtons() {
  CreateMainMenuButtons();
  CreateSettingsButtons();
  CreateGameButtons();
  CreatePauseMenuButtons();
}

void ButtonHandler::RescaleButtons(SizeHandler size_handler) {
  RescaleMainMenuButtons(size_handler);
  RescaleSettingsButtons(size_handler);
  RescaleGameButtons(size_handler);
  RescalePauseMenuButtons(size_handler);
}

void ButtonHandler::SetMainMenuUiVisible(bool visible) {
  start_game_button_->setVisible(visible);
  settings_button_->setVisible(visible);
  choose_level_number_->setVisible(visible);
  inc_level_button_->setVisible(visible);
  dec_level_button_->setVisible(visible);
  exit_button_->setVisible(visible);
}

void ButtonHandler::SetSettingsUiVisible(bool visible) {
  language_button_->setVisible(visible);
  sound_button_->setVisible(visible);
  reset_game_button_->setVisible(visible);
  to_main_menu_button_->setVisible(visible);
}

void ButtonHandler::SetGameUiVisible(bool visible) {
  pause_button_->setVisible(visible);
  zero_speed_button_->setVisible(visible);
  normal_speed_button_->setVisible(visible);
  double_speed_button_->setVisible(visible);
}

void ButtonHandler::SetPauseMenuUiVisible(bool visible) {
  continue_button_->setVisible(visible);
  restart_button_->setVisible(visible);
  to_main_menu_button_->setVisible(visible);
}

WindowType ButtonHandler::GetWindowType() const {
  return window_type_;
}

void ButtonHandler::CreateMainMenuButtons() {
  start_game_button_ = new MenuButton(
      tr("НАЧАТЬ ИГРУ"), long_button_size_, main_window_, font_id_);
  auto start_game_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    window_type_ = WindowType::kGame;
    controller_->StartGame(level_number_);
    SetSpeedButtonsState(Speed::kNormalSpeed);
  };
  connect(start_game_button_, &QPushButton::clicked, start_game_button_click);

  settings_button_ = new MenuButton(
      tr("НАСТРОЙКИ"), long_button_size_, main_window_, font_id_);
  auto settings_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    window_type_ = WindowType::kSettings;
    main_window_->repaint();
  };
  connect(settings_button_, &QPushButton::clicked, settings_button_click);

  exit_button_ = new MenuButton(
      tr("ВЫЙТИ ИЗ ИГРЫ"), long_button_size_, main_window_, font_id_);
  auto exit_button_click = [this]() {
    auto response = QMessageBox::question(main_window_, tr("Это ошибка..."),
                                          tr("Вы точно-точно уходите?"));
    if (response == QMessageBox::Yes) {
      main_window_->close();
    }
  };
  connect(
      exit_button_, &QPushButton::clicked, main_window_, exit_button_click);

  Size choose_level_number_size =
      Size(long_button_size_.width - short_button_size_.width * 2 - shift_ * 2,
           long_button_size_.height);
  choose_level_number_ = new MenuButton(
      tr("УРОВЕНЬ ") + QString::number(level_number_),
      choose_level_number_size, main_window_, font_id_);

  inc_level_button_ = new MenuButton(
      short_button_size_, main_window_,
      ":resources/buttons_resources/inc_level_button.png",
      ":resources/buttons_resources/inc_level_button_active.png");
  auto inc_level_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    SetLevelNumber(level_number_ + 1);
  };
  connect(inc_level_button_, &QPushButton::clicked, inc_level_button_click);

  dec_level_button_ = new MenuButton(
      short_button_size_, main_window_,
      ":resources/buttons_resources/dec_level_button.png",
      ":resources/buttons_resources/dec_level_button_active.png");
  auto dec_level_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    SetLevelNumber(level_number_ - 1);
  };
  connect(dec_level_button_, &QPushButton::clicked, dec_level_button_click);
}

void ButtonHandler::RescaleMainMenuButtons(SizeHandler size_handler) {
  Size shift = Size(0, long_button_size_.height + shift_);

  start_game_button_->SetGeometry(first_button_coordinate_, size_handler);
  dec_level_button_->SetGeometry(
      first_button_coordinate_ + shift, size_handler);
  choose_level_number_->SetGeometry(
      first_button_coordinate_ + shift + Size(shift.height, 0), size_handler);
  inc_level_button_->SetGeometry(
      first_button_coordinate_ + shift + Size(long_button_size_.width, 0)
          - Size(short_button_size_.height, 0), size_handler);
  settings_button_->SetGeometry(first_button_coordinate_ + shift * 2,
                                size_handler);
  exit_button_->SetGeometry(first_button_coordinate_ + shift * 3, size_handler);
}

void ButtonHandler::CreateSettingsButtons() {
  QSettings settings(constants::kCompanyName, constants::kApplicationName);
  QString locale = settings.value("locale", "en_US").toString();
  if (locale == "en_US") {
    is_language_russian_ = false;
    language_button_ = new MenuButton(
        short_button_size_,
        main_window_,
        ":resources/buttons_resources/language_button_eng.png",
        ":resources/buttons_resources/language_button_eng_active.png");
    language_button_->SetSecondIconPath(
        ":resources/buttons_resources/language_button_rus.png",
        ":resources/buttons_resources/language_button_rus_active.png");
  } else {
    is_language_russian_ = true;
    language_button_ = new MenuButton(
        short_button_size_,
        main_window_,
        ":resources/buttons_resources/language_button_rus.png",
        ":resources/buttons_resources/language_button_rus_active.png");
    language_button_->SetSecondIconPath(
        ":resources/buttons_resources/language_button_eng.png",
        ":resources/buttons_resources/language_button_eng_active.png");
  }

  auto language_button_click = [this]() {
    QSettings settings(constants::kCompanyName, constants::kApplicationName);
    controller_->GetMusicPlayer()->PlayButtonSound();
    auto response = QMessageBox::question(main_window_, tr("Внимание!"),
        tr("Чтобы язык приложения изменился, его необходимо перезапустить."
           " Все равно продолжить?"));
    if (response != QMessageBox::Yes) {
      return;
    }
    language_button_->EnableSecondIcon(is_language_russian_);
    is_language_russian_ = !is_language_russian_;

    if (is_language_russian_) {
      settings.setValue("locale", "ru_RU");
    } else {
      settings.setValue("locale", "en_US");
    }
    qApp->exit(constants::kApplicationRestartCode);
  };
  connect(language_button_, &QPushButton::clicked, language_button_click);

  sound_button_ = new MenuButton(
      short_button_size_,
      main_window_,
      ":resources/buttons_resources/sound_button_on.png",
      ":resources/buttons_resources/sound_button_on_active.png");
  sound_button_->SetSecondIconPath(
      ":resources/buttons_resources/sound_button_off.png",
      ":resources/buttons_resources/sound_button_off_active.png");
  auto sound_button_click = [this]() {
    QSettings settings(constants::kCompanyName, constants::kApplicationName);
    controller_->GetMusicPlayer()->PlayButtonSound();
    SetSoundOn(!is_sound_on_);
    settings.setValue("sound_on", is_sound_on_);
  };
  connect(sound_button_, &QPushButton::clicked, sound_button_click);

  reset_game_button_ = new MenuButton(
      tr("СБРОСИТЬ ПРОГРЕСС"), long_button_size_, main_window_, font_id_);
  auto reset_game_click = [this]() {
    QSettings settings(constants::kCompanyName, constants::kApplicationName);
    controller_->GetMusicPlayer()->PlayButtonSound();
    auto response = QMessageBox::question(main_window_, tr("Внимание!"),
        tr("Сброс прогресса нельзя отменить! Все равно продолжить?"));
    if (response == QMessageBox::Yes) {
      SetMaxLevel(1);
      settings.setValue("level", 0);
    }
  };
  connect(reset_game_button_, &QPushButton::clicked, reset_game_click);

  to_main_menu_button_ = new MenuButton(
      tr("ВЕРНУТЬСЯ В МЕНЮ"), long_button_size_, main_window_, font_id_);
  auto back_to_main_menu_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    if (window_type_ == WindowType::kPauseMenu) {
      controller_->EndGame();
    }
    window_type_ = WindowType::kMainMenu;
    main_window_->repaint();
  };
  connect(to_main_menu_button_, &QPushButton::clicked, back_to_main_menu_click);
}

void ButtonHandler::RescaleSettingsButtons(SizeHandler size_handler) {
  Size shift = Size(0, long_button_size_.height + shift_);

  sound_button_->SetGeometry(
      first_button_coordinate_ + Size(long_button_size_.width / 2, 0)
          - Size(short_button_size_.width, 0), size_handler);
  language_button_->SetGeometry(
      first_button_coordinate_ + Size(long_button_size_.width / 2, 0)
          - Size(short_button_size_.width, 0) + Size(shift.height, 0),
      size_handler);

  reset_game_button_->SetGeometry(first_button_coordinate_ + shift,
                                  size_handler);
  to_main_menu_button_->SetGeometry(first_button_coordinate_ + shift * 2,
                                    size_handler);
}

void ButtonHandler::CreateGameButtons() {
  pause_button_ = new MenuButton(
      short_button_size_,
      main_window_,
      ":resources/buttons_resources/pause_button.png",
      ":resources/buttons_resources/pause_button_active.png");
  auto pause_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    window_type_ = WindowType::kPauseMenu;
    controller_->SetSpeedCoefficient(Speed::kZeroSpeed);
  };
  connect(pause_button_, &QPushButton::clicked, pause_button_click);

  zero_speed_button_ = new MenuButton(
      short_button_size_,
      main_window_,
      ":resources/buttons_resources/zero_speed_button.png",
      ":resources/buttons_resources/zero_speed_button_active.png");
  auto zero_speed_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    controller_->SetSpeedCoefficient(Speed::kZeroSpeed);
    SetSpeedButtonsState(Speed::kZeroSpeed);
  };
  connect(zero_speed_button_, &QPushButton::clicked, zero_speed_button_click);

  normal_speed_button_ = new MenuButton(
      short_button_size_,
      main_window_,
      ":resources/buttons_resources/normal_speed_button.png",
      ":resources/buttons_resources/normal_speed_button_active.png");
  auto normal_speed_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    controller_->SetSpeedCoefficient(Speed::kNormalSpeed);
    SetSpeedButtonsState(Speed::kNormalSpeed);
  };
  connect(normal_speed_button_,
          &QPushButton::clicked,
          normal_speed_button_click);
  normal_speed_button_->setDisabled(true);

  double_speed_button_ = new MenuButton(
      short_button_size_,
      main_window_,
      ":resources/buttons_resources/double_speed_button.png",
      ":resources/buttons_resources/double_speed_button_active.png");
  auto double_speed_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    controller_->SetSpeedCoefficient(Speed::kDoubleSpeed);
    SetSpeedButtonsState(Speed::kDoubleSpeed);
  };
  connect(double_speed_button_,
          &QPushButton::clicked,
          double_speed_button_click);
}

void ButtonHandler::RescaleGameButtons(SizeHandler size_handler) {
  Size shift = Size(0, short_button_size_.width + shift_);
  pause_button_->SetGeometry({constants::kGameWidth - 80, 20}, size_handler);
  Coordinate zero_speed_button_coordinate =
      Coordinate(20, 480) + shift;
  zero_speed_button_->SetGeometry(zero_speed_button_coordinate, size_handler);
  normal_speed_button_->SetGeometry(zero_speed_button_coordinate + shift,
                                    size_handler);
  double_speed_button_->SetGeometry(zero_speed_button_coordinate + shift * 2,
                                    size_handler);
}

void ButtonHandler::CreatePauseMenuButtons() {
  restart_button_ = new MenuButton(
      tr("НАЧАТЬ УРОВЕНЬ ЗАНОВО"), long_button_size_, main_window_, font_id_);
  auto restart_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    window_type_ = WindowType::kGame;
    controller_->EndGame();
    controller_->StartGame(level_number_);
    SetSpeedButtonsState(Speed::kNormalSpeed);
  };
  connect(restart_button_, &QPushButton::clicked, restart_button_click);

  continue_button_ = new MenuButton(
      tr("ПРОДОЛЖИТЬ"), long_button_size_, main_window_, font_id_);
  auto continue_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    window_type_ = WindowType::kGame;
    controller_->SetSpeedCoefficient(Speed::kNormalSpeed);
    SetSpeedButtonsState(Speed::kNormalSpeed);
  };
  connect(continue_button_, &QPushButton::clicked, continue_button_click);
}

void ButtonHandler::RescalePauseMenuButtons(SizeHandler size_handler) {
  Size shift = Size({0, long_button_size_.height + shift_});
  continue_button_->SetGeometry(first_button_coordinate_, size_handler);
  restart_button_->SetGeometry(first_button_coordinate_ + shift, size_handler);
}

void ButtonHandler::SetSpeedButtonsState(Speed speed) {
  zero_speed_button_->setDisabled(speed == Speed::kZeroSpeed);
  normal_speed_button_->setDisabled(speed == Speed::kNormalSpeed);
  double_speed_button_->setDisabled(speed == Speed::kDoubleSpeed);
}

void ButtonHandler::SetLevelNumber(int level) {
  if (level >= 1 && level <= current_max_level_) {
    level_number_ = level;
  }
  inc_level_button_->setEnabled(level_number_ != current_max_level_);
  dec_level_button_->setEnabled(level_number_ != 1);
  choose_level_number_->setText(tr("УРОВЕНЬ") + " " +
    QString::number(level_number_));
}

void ButtonHandler::SetSoundOn(bool sound_on) {
  is_sound_on_ = sound_on;
  sound_button_->EnableSecondIcon(!is_sound_on_);
  controller_->GetMusicPlayer()->SetVolume(
      100 * static_cast<int>(is_sound_on_));
}

void ButtonHandler::SetMaxLevel(int max_level) {
  current_max_level_ = std::min(max_level, kMaxLevel_);
  SetLevelNumber(std::min(level_number_ + 1, current_max_level_));
}

int ButtonHandler::GetLevel() const {
  return level_number_;
}
