#include "button_handler.h"

ButtonHandler::ButtonHandler(QMainWindow* main_window,
                             AbstractController* controller) :
    main_window_(main_window), controller_(controller) {
  CreateButtons(controller_);
}

void ButtonHandler::CreateButtons(AbstractController* controller) {
  controller_ = controller;
  CreateMainMenuButtons();
  CreateSettingsButtons();
  CreateGameButtons();
  CreatePauseMenuButtons();
}

void ButtonHandler::MoveButtons(SizeHandler size_handler) {
  MoveMainMenuButtons(size_handler);
  MoveSettingsButtons(size_handler);
  MoveGameButtons(size_handler);
  MovePauseMenuButtons(size_handler);
}

void ButtonHandler::EnableMainMenuUi() {
  window_type_ = WindowType::kMainMenu;
  start_game_button_->show();
  settings_button_->show();
  choose_level_number_->show();
  inc_level_button_->show();
  dec_level_button_->show();
  exit_button_->show();
}

void ButtonHandler::DisableMainMenuUi() {
  start_game_button_->hide();
  settings_button_->hide();
  choose_level_number_->hide();
  inc_level_button_->hide();
  dec_level_button_->hide();
  exit_button_->hide();
}

void ButtonHandler::EnableSettingsUi() {
  window_type_ = WindowType::kSettings;
  language_button_->show();
  sound_button_->show();
  reset_game_button_->show();
  to_main_menu_button_->show();
}

void ButtonHandler::DisableSettingsUi() {
  language_button_->hide();
  sound_button_->hide();
  reset_game_button_->hide();
  to_main_menu_button_->hide();
}

void ButtonHandler::EnableGameUi() {
  window_type_ = WindowType::kGame;
  pause_button_->show();
  zero_speed_button_->show();
  normal_speed_button_->show();
  double_speed_button_->show();
}

void ButtonHandler::DisableGameUi() {
  pause_button_->hide();
  zero_speed_button_->hide();
  normal_speed_button_->hide();
  double_speed_button_->hide();
}

void ButtonHandler::EnablePauseMenuUi() {
  window_type_ = WindowType::kPauseMenu;
  continue_button_->show();
  restart_button_->show();
  to_main_menu_button_->show();
}

void ButtonHandler::DisablePauseMenuUi() {
  continue_button_->hide();
  restart_button_->hide();
  to_main_menu_button_->hide();
}

WindowType ButtonHandler::GetWindowType() const {
  return window_type_;
}

void ButtonHandler::CreateMainMenuButtons() {
  start_game_button_ = new MenuButton(
      tr("НАЧАТЬ ИГРУ"), long_button_size_, main_window_);
  auto start_game_button_click = [&]() {
    controller_->StartGame(level_number_);
  };
  connect(start_game_button_, &QPushButton::clicked, start_game_button_click);

  settings_button_ = new MenuButton(
      tr("НАСТРОЙКИ"), long_button_size_, main_window_);
  auto settings_button_click = [&]() {
    window_type_ = WindowType::kSettings;
    main_window_->repaint();
  };
  connect(settings_button_, &QPushButton::clicked, settings_button_click);

  exit_button_ = new MenuButton(
      tr("ВЫЙТИ ИЗ ИГРЫ"), long_button_size_, main_window_);
  connect(exit_button_,
          &QPushButton::clicked,
          main_window_,
          &QMainWindow::close);

  Size choose_level_number_size =
      Size(long_button_size_.width - short_button_size_.width * 2 - shift_ * 2,
           long_button_size_.height);
  choose_level_number_ = new MenuButton(
      tr("УРОВЕНЬ 1"), choose_level_number_size, main_window_);

  inc_level_button_ = new MenuButton("", short_button_size_,
      main_window_, ":resources/buttons_resources/inc_level_button.png");
  auto inc_level_button_click = [&]() {
    if (level_number_ < 3) {
      level_number_++;
    }
    choose_level_number_->setText(
          "УРОВЕНЬ " + QString::number(level_number_));
  };
  connect(inc_level_button_, &QPushButton::clicked, inc_level_button_click);

  dec_level_button_ = new MenuButton("", short_button_size_,
      main_window_, ":resources/buttons_resources/dec_level_button.png");
  auto dec_level_button_click = [&]() {
    if (level_number_ > 1) {
      level_number_--;
    }
    choose_level_number_->setText(
          "УРОВЕНЬ " + QString::number(level_number_));
  };
  connect(dec_level_button_, &QPushButton::clicked, dec_level_button_click);
}

void ButtonHandler::MoveMainMenuButtons(SizeHandler size_handler) {
  Size shift = Size({0, long_button_size_.height + shift_});

  start_game_button_->Move(first_button_coordinate_, size_handler);
  dec_level_button_->Move(first_button_coordinate_ + shift, size_handler);
  choose_level_number_->Move(
      first_button_coordinate_ + shift + Size(shift.height, 0), size_handler);
  inc_level_button_->Move(
      first_button_coordinate_ + shift + Size(long_button_size_.width, 0)
          - Size(short_button_size_.height, 0), size_handler);
  settings_button_->Move(first_button_coordinate_ + shift * 2, size_handler);
  exit_button_->Move(first_button_coordinate_ + shift * 3, size_handler);
}

void ButtonHandler::CreateSettingsButtons() {
  language_button_ = new MenuButton("", short_button_size_,
      main_window_, ":resources/buttons_resources/language_button_eng.png");
  auto language_button_click = [&]() {
    // changing language
  };
  connect(language_button_, &QPushButton::clicked, language_button_click);

  sound_button_ = new MenuButton("", short_button_size_,
      main_window_, ":resources/buttons_resources/sound_button_on.png");
  auto sound_button_click = [&]() {
    // changing sound
    if (is_sound_on_) {
      sound_button_->setIcon(QIcon(
          ":resources/buttons_resources/sound_button_off.png"));
    } else {
      sound_button_->setIcon(QIcon(
          ":resources/buttons_resources/sound_button_on.png"));
    }
    is_sound_on_ = 1 - is_sound_on_;
  };
  connect(sound_button_, &QPushButton::clicked, sound_button_click);

  reset_game_button_ = new MenuButton(
      tr("СБРОСИТЬ ПРОГРЕСС"), long_button_size_, main_window_);
  auto reset_game_click = [&]() {
    // reseting game, will be updated when saving is done
  };
  connect(reset_game_button_, &QPushButton::clicked, reset_game_click);

  to_main_menu_button_ = new MenuButton(
      tr("ВЕРНУТЬСЯ В МЕНЮ"), long_button_size_, main_window_);
  auto back_to_main_menu_click = [&]() {
    if (window_type_ == WindowType::kPauseMenu) {
      controller_->EndGame(Exit::kMenu);
    }
    window_type_ = WindowType::kMainMenu;
    main_window_->repaint();
  };
  connect(to_main_menu_button_, &QPushButton::clicked, back_to_main_menu_click);
}

void ButtonHandler::MoveSettingsButtons(SizeHandler size_handler) {
  Size shift = Size({0, long_button_size_.height + shift_});

  sound_button_->Move(
      first_button_coordinate_ + Size(long_button_size_.width / 2, 0)
          - Size(short_button_size_.width, 0), size_handler);
  language_button_->Move(
      first_button_coordinate_ + Size(long_button_size_.width / 2, 0)
          - Size(short_button_size_.width, 0) + Size(shift.height, 0),
      size_handler);

  reset_game_button_->Move(first_button_coordinate_ + shift, size_handler);
  to_main_menu_button_->Move(first_button_coordinate_ + shift * 2,
                             size_handler);
}

void ButtonHandler::CreateGameButtons() {
  pause_button_ = new MenuButton("", short_button_size_,
      main_window_, ":resources/buttons_resources/pause_button.png");
  auto pause_button_click = [&]() {
    controller_->SetSpeedCoefficient(Speed::kZeroSpeed);
    window_type_ = WindowType::kPauseMenu;
  };
  connect(pause_button_, &QPushButton::clicked, pause_button_click);

  zero_speed_button_ = new MenuButton("", short_button_size_,
      main_window_, ":resources/buttons_resources/zero_speed_button.png");
  auto zero_speed_button_click = [&]() {
    controller_->SetSpeedCoefficient(Speed::kZeroSpeed);
  };
  connect(zero_speed_button_, &QPushButton::clicked, zero_speed_button_click);

  normal_speed_button_ = new MenuButton("", short_button_size_,
      main_window_, ":resources/buttons_resources/normal_speed_button.png");
  auto normal_speed_button_click = [&]() {
    controller_->SetSpeedCoefficient(Speed::kNormalSpeed);
  };
  connect(normal_speed_button_,
          &QPushButton::clicked,
          normal_speed_button_click);

  double_speed_button_ = new MenuButton("", short_button_size_,
      main_window_, ":resources/buttons_resources/double_speed_button.png");
  auto double_speed_button_click = [&]() {
    controller_->SetSpeedCoefficient(Speed::kDoubleSpeed);
  };
  connect(double_speed_button_,
          &QPushButton::clicked,
          double_speed_button_click);
}

void ButtonHandler::MoveGameButtons(SizeHandler size_handler) {
  Size shift = Size({short_button_size_.width + shift_, 0});
  pause_button_->Move({0, 0}, size_handler);
  Coordinate
      zero_speed_button_coordinate = Coordinate(kGameWidth, 0) - shift * 2
      - Size(short_button_size_.width, 0);
  zero_speed_button_->Move(zero_speed_button_coordinate, size_handler);
  normal_speed_button_->Move(zero_speed_button_coordinate + shift,
                             size_handler);
  double_speed_button_->Move(zero_speed_button_coordinate + shift * 2,
                             size_handler);
}


void ButtonHandler::CreatePauseMenuButtons() {
  restart_button_ = new MenuButton(
      tr("НАЧАТЬ УРОВЕНЬ ЗАНОВО"), long_button_size_, main_window_);
  auto restart_button_click = [&]() {
    controller_->EndGame(Exit::kLose);
    controller_->StartGame(level_number_);
    controller_->SetSpeedCoefficient(Speed::kNormalSpeed);
    window_type_ = WindowType::kGame;
    DisablePauseMenuUi();
  };
  connect(restart_button_, &QPushButton::clicked, restart_button_click);

  continue_button_ = new MenuButton(
      tr("ПРОДОЛЖИТЬ"), long_button_size_, main_window_);
  auto continue_button_click = [&]() {
    controller_->SetSpeedCoefficient(Speed::kNormalSpeed);
    window_type_ = WindowType::kGame;
    DisablePauseMenuUi();
  };
  connect(continue_button_, &QPushButton::clicked, continue_button_click);
}

void ButtonHandler::MovePauseMenuButtons(SizeHandler size_handler) {
  Size shift = Size({0, long_button_size_.height + shift_});
  continue_button_->Move(first_button_coordinate_, size_handler);
  restart_button_->Move(first_button_coordinate_ + shift, size_handler);
}
