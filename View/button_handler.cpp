#include "button_handler.h"

ButtonHandler::ButtonHandler(QMainWindow* main_window) : main_window_(
    main_window) {}

void ButtonHandler::EnableMainMenuUi() {
  window_type_ = WindowType::kMainMenu;
  start_game_button_.Show();
  settings_button_.Show();
  choose_level_number_.Show();
  inc_level_button_.Show();
  dec_level_button_.Show();
  exit_button_.Show();
}

void ButtonHandler::DisableMainMenuUi() {
  start_game_button_.Hide();
  settings_button_.Hide();
  choose_level_number_.Hide();
  inc_level_button_.Hide();
  dec_level_button_.Hide();
  exit_button_.Hide();
}

WindowType ButtonHandler::GetWindowType() {
  return window_type_;
}

void ButtonHandler::CreateMainMenuButtons(AbstractController* controller) {
  controller_ = controller;

  start_game_button_ = MenuButton(
      "НАЧАТЬ ИГРУ", long_button_size_, main_window_);
  auto start_game_button_click = [&]() {
    controller_->StartGame(level_number_);
  };
  connect(start_game_button_.GetQPushButton(), &QPushButton::clicked,
          start_game_button_click);

  settings_button_ = MenuButton(
      "НАСТРОЙКИ", long_button_size_, main_window_);
  auto settings_button_click = [&]() {
    window_type_ = WindowType::kSettings;
    main_window_->repaint();
  };
  connect(settings_button_.GetQPushButton(), &QPushButton::clicked,
          settings_button_click);

  exit_button_ = MenuButton(
      "ВЫЙТИ ИЗ ИГРЫ", long_button_size_, main_window_);
  connect(exit_button_.GetQPushButton(), &QPushButton::clicked, main_window_,
          &QMainWindow::close);

  Size choose_level_number_size =
      Size(long_button_size_.width - short_button_size_.width * 2 - shift_ * 2,
           long_button_size_.height);
  choose_level_number_ = MenuButton(
      "УРОВЕНЬ 1", choose_level_number_size, main_window_);

  inc_level_button_ = MenuButton(
      "", short_button_size_,
      main_window_,":resources/buttons_images/inc_level_button.png");
  auto inc_level_button_click = [&]() {
    if (level_number_ < 3) {
      level_number_++;
    }
    if (is_language_rus_) {
      choose_level_number_.SetText("УРОВЕНЬ " + QString::number(level_number_));
    } else {
      choose_level_number_.SetText("LEVEL " + QString::number(level_number_));
    }
  };
  connect(inc_level_button_.GetQPushButton(), &QPushButton::clicked,
          inc_level_button_click);

  dec_level_button_ = MenuButton("",short_button_size_,
      main_window_,":resources/buttons_images/dec_level_button.png");
  auto dec_level_button_click = [&]() {
    if (level_number_ > 1) {
      level_number_--;
    }
    if (is_language_rus_) {
      choose_level_number_.SetText("УРОВЕНЬ " + QString::number(level_number_));
    } else {
      choose_level_number_.SetText("LEVEL " + QString::number(level_number_));
    }
  };
  connect(dec_level_button_.GetQPushButton(), &QPushButton::clicked,
          dec_level_button_click);
}

void ButtonHandler::MoveMainMenuButtons(std::shared_ptr<SizeHandler> size_handler) {
  Size shift = Size({0, long_button_size_.height + shift_});

  start_game_button_.Move(first_button_coordinate_, size_handler);
  dec_level_button_.Move(first_button_coordinate_ + shift, size_handler);
  choose_level_number_.Move(
      first_button_coordinate_ + shift + Size(shift.height, 0), size_handler);
  inc_level_button_.Move(
      first_button_coordinate_ + shift + Size(long_button_size_.width, 0)
          - Size(short_button_size_.height, 0), size_handler);
  settings_button_.Move(first_button_coordinate_ + shift * 2, size_handler);
  exit_button_.Move(first_button_coordinate_ + shift * 3, size_handler);
}

void ButtonHandler::CreateSettingsButtons(AbstractController* controller) {
  language_button_ = MenuButton( "", short_button_size_,
      main_window_,":resources/buttons_images/language_button_eng.png");
  auto language_button_click = [&]() {
    ChangeLanguage();
    if (is_language_rus_) {
      language_button_.SetIcon(
          ":resources/buttons_images/language_button_rus.png");
    } else {
      language_button_.SetIcon(
          ":resources/buttons_images/language_button_eng.png");
    }
    is_language_rus_ = !is_language_rus_;
  };
  connect(language_button_.GetQPushButton(), &QPushButton::clicked,
          language_button_click);

  sound_button_ = MenuButton( "", short_button_size_,
      main_window_,":resources/buttons_images/sound_button_on.png");
  auto sound_button_click = [&]() {
    // changing sound
    if (is_sound_on) {
      sound_button_.SetIcon(":resources/buttons_images/sound_button_off.png");
    } else {
      sound_button_.SetIcon(":resources/buttons_images/sound_button_on.png");
    }
    is_sound_on = 1 - is_sound_on;
  };
  connect(sound_button_.GetQPushButton(), &QPushButton::clicked,
          sound_button_click);

  reset_game_button_ = MenuButton(
      "СБРОСИТЬ ПРОГРЕСС", long_button_size_, main_window_);
  auto reset_game_click = [&]() {
    // reseting game, will be updated when saving is done
  };
  connect(reset_game_button_.GetQPushButton(), &QPushButton::clicked,
          reset_game_click);

  to_main_menu_button_ = MenuButton(
      "ВЕРНУТЬСЯ В МЕНЮ", long_button_size_, main_window_);
  auto back_to_main_menu_click = [&]() {
    if (window_type_ == WindowType::kPauseMenu) {
      controller_->EndGame(Exit::kMenu);
    }
    window_type_ = WindowType::kMainMenu;
    main_window_->repaint();
  };
  connect(to_main_menu_button_.GetQPushButton(), &QPushButton::clicked,
          back_to_main_menu_click);
}

void ButtonHandler::MoveSettingsButtons(std::shared_ptr<SizeHandler> size_handler) {
  Size shift = Size({0, long_button_size_.height + shift_});

  sound_button_.Move(
      first_button_coordinate_ + Size(long_button_size_.width / 2, 0)
          - Size(short_button_size_.width, 0), size_handler);
  language_button_.Move(
      first_button_coordinate_ + Size(long_button_size_.width / 2, 0)
          - Size(short_button_size_.width, 0) + Size(shift.height, 0),
      size_handler);

  reset_game_button_.Move(first_button_coordinate_ + shift, size_handler);
  to_main_menu_button_.Move(first_button_coordinate_ + shift * 2, size_handler);
}

void ButtonHandler::EnableSettingsUi() {
  window_type_ = WindowType::kSettings;
  language_button_.Show();
  sound_button_.Show();
  reset_game_button_.Show();
  to_main_menu_button_.Show();
}

void ButtonHandler::DisableSettingsUi() {
  language_button_.Hide();
  sound_button_.Hide();
  reset_game_button_.Hide();
  to_main_menu_button_.Hide();
}

void ButtonHandler::CreateGameButtons(AbstractController* controller) {
  pause_button_ = MenuButton( "", short_button_size_,
      main_window_, ":resources/buttons_images/pause_button.png");
  auto pause_button_click = [&]() {
    // pause
    window_type_ = WindowType::kPauseMenu;
  };
  connect(pause_button_.GetQPushButton(), &QPushButton::clicked,
          pause_button_click);

  zero_speed_button_ = MenuButton( "", short_button_size_,
      main_window_, ":resources/buttons_images/zero_speed_button.png");
  auto zero_speed_button_click = [&]() {
    // zero speed
  };
  connect(zero_speed_button_.GetQPushButton(), &QPushButton::clicked,
          zero_speed_button_click);

  normal_speed_button_ = MenuButton("", short_button_size_,
      main_window_, ":resources/buttons_images/normal_speed_button.png");
  auto normal_speed_button_click = [&]() {
    // normal speed
  };
  connect(normal_speed_button_.GetQPushButton(), &QPushButton::clicked,
          normal_speed_button_click);

  double_speed_button_ = MenuButton("", short_button_size_,
      main_window_, ":resources/buttons_images/double_speed_button.png");
  auto double_speed_button_click = [&]() {
    // double speed
  };
  connect(double_speed_button_.GetQPushButton(), &QPushButton::clicked,
          double_speed_button_click);
}

void ButtonHandler::MoveGameButtons(std::shared_ptr<SizeHandler> size_handler) {
  Size shift = Size({short_button_size_.width + shift_, 0});
  pause_button_.Move({0, 0}, size_handler);
  Coordinate
      zero_speed_button_coordinate = Coordinate(kGameWidth, 0) - shift * 2
      - Size(short_button_size_.width, 0);
  zero_speed_button_.Move(zero_speed_button_coordinate, size_handler);
  normal_speed_button_.Move(zero_speed_button_coordinate + shift, size_handler);
  double_speed_button_.Move(zero_speed_button_coordinate + shift * 2,
                            size_handler);
}

void ButtonHandler::EnableGameUi() {
  window_type_ = WindowType::kGame;
  pause_button_.Show();
  zero_speed_button_.Show();
  normal_speed_button_.Show();
  double_speed_button_.Show();
}

void ButtonHandler::DisableGameUi() {
  pause_button_.Hide();
  zero_speed_button_.Hide();
  normal_speed_button_.Hide();
  double_speed_button_.Hide();
}

void ButtonHandler::CreatePauseMenuButtons(AbstractController* controller) {
  restart_button_ = MenuButton(
      "НАЧАТЬ УРОВЕНЬ ЗАНОВО", long_button_size_, main_window_);
  auto restart_button_click = [&]() {
    controller_->EndGame(Exit::kLose);
    controller_->StartGame(level_number_);
    window_type_ = WindowType::kGame;
    DisablePauseMenuUi();
    main_window_->repaint();
  };
  connect(restart_button_.GetQPushButton(), &QPushButton::clicked,
          restart_button_click);

  continue_button_ = MenuButton(
      "ПРОДОЛЖИТЬ", long_button_size_, main_window_);
  auto continue_button_click = [&]() {
    // continue timer
    window_type_ = WindowType::kGame;
    DisablePauseMenuUi();
    main_window_->repaint();
  };
  connect(continue_button_.GetQPushButton(), &QPushButton::clicked,
          continue_button_click);
}

void ButtonHandler::MovePauseMenuButtons(std::shared_ptr<SizeHandler> size_handler) {
  Size shift = Size({0, long_button_size_.height + shift_,});
  continue_button_.Move(first_button_coordinate_, size_handler);
  restart_button_.Move(first_button_coordinate_ + shift, size_handler);
}

void ButtonHandler::EnablePauseMenuUi() {
  window_type_ = WindowType::kPauseMenu;
  continue_button_.Show();
  restart_button_.Show();
  to_main_menu_button_.Show();
}

void ButtonHandler::DisablePauseMenuUi() {
  continue_button_.Hide();
  restart_button_.Hide();
  to_main_menu_button_.Hide();
}

void ButtonHandler::CreateButtons(AbstractController* controller) {
  CreateMainMenuButtons(controller);
  CreateSettingsButtons(controller);
  CreateGameButtons(controller);
  CreatePauseMenuButtons(controller);
}

void ButtonHandler::MoveButtons(std::shared_ptr<SizeHandler> size_handler) {
  MoveMainMenuButtons(size_handler);
  MoveSettingsButtons(size_handler);
  MoveGameButtons(size_handler);
  MovePauseMenuButtons(size_handler);
}

void ButtonHandler::ChangeLanguage() {
  if (is_language_rus_) {
    start_game_button_.SetText("START GAME");
    choose_level_number_.SetText("LEVEL " + QString::number(level_number_));
    settings_button_.SetText("SETTINGS");
    exit_button_.SetText("EXIT");
    reset_game_button_.SetText("RESET PROGRESS");
    to_main_menu_button_.SetText("BACK TO MAIN MENU");
    continue_button_.SetText("CONTINUE");
    restart_button_.SetText("RESTART");
  } else {
    start_game_button_.SetText("НАЧАТЬ ИГРУ");
    choose_level_number_.SetText("УРОВЕНЬ " + QString::number(level_number_));
    settings_button_.SetText("НАСТРОЙКИ");
    exit_button_.SetText("ВЫЙТИ ИЗ ИГРЫ");
    reset_game_button_.SetText("СБРОСИТЬ ПРОГРЕСС");
    to_main_menu_button_.SetText("ВЕРНУТЬСЯ В МЕНЮ");
    continue_button_.SetText("ПРОДОЛЖИТЬ");
    restart_button_.SetText("НАЧАТЬ УРОВЕНЬ ЗАНОВО");
  }
}
