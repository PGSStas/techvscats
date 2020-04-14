#include "button_handler.h"

ButtonHandler::ButtonHandler(QMainWindow* main_window) : main_window_(
    main_window) {}

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

WindowType ButtonHandler::GetWindowType() {
  return window_type_;
}

void ButtonHandler::CreateMainMenuButtons(AbstractController* controller) {
  controller_ = controller;

  // main_menu buttons
  start_game_button_ = new QPushButton(main_window_);
  start_game_button_->setIcon(QIcon(
      ":resources/buttons_images/start_game_button.png"));
  auto start_game_button_click = [&]() {
    controller_->StartGame(level_number_);
  };
  connect(start_game_button_, &QPushButton::clicked, start_game_button_click);

  settings_button_ = new QPushButton(main_window_);
  settings_button_->setIcon(QIcon(
      ":resources/buttons_images/settings_button.png"));
  auto settings_button_click = [&]() {
    window_type_ = WindowType::kSettings;
    main_window_->repaint();
  };
  connect(settings_button_, &QPushButton::clicked, settings_button_click);

  exit_button_ = new QPushButton(main_window_);
  exit_button_->setIcon(QIcon(":resources/buttons_images/exit_button.png"));
  connect(exit_button_,
          &QPushButton::clicked,
          main_window_,
          &QMainWindow::close);

  choose_level_number_ = new QPushButton(main_window_);
  choose_level_number_->setIcon(QIcon(
      ":resources/buttons_images/choose_level_number_1.png"));

  inc_level_button_ = new QPushButton(main_window_);
  inc_level_button_->setIcon(QIcon(
      ":resources/buttons_images/inc_level_button.png"));
  auto inc_level_button_click = [&]() {
    if (level_number_ < 3) {
      level_number_++;
    }
    choose_level_number_->setIcon(QIcon(
        ":resources/buttons_images/choose_level_number_"
            + QString::number(level_number_) + ".png"));
  };
  connect(inc_level_button_, &QPushButton::clicked, inc_level_button_click);

  dec_level_button_ = new QPushButton(main_window_);
  dec_level_button_->setIcon(QIcon(
      ":resources/buttons_images/dec_level_button.png"));
  auto dec_level_button_click = [&]() {
    if (level_number_ > 1) {
      level_number_--;
    }
    choose_level_number_->setIcon(QIcon(
        ":resources/buttons_images/choose_level_number_"
            + QString::number(level_number_) + ".png"));
  };
  connect(dec_level_button_, &QPushButton::clicked, dec_level_button_click);
}

void ButtonHandler::MoveMainMenuButtons(SizeHandler size_handler) {
  QSize long_button_size =
      QSize(size_handler.GameToWindowSize(long_button_size_).width,
            size_handler.GameToWindowSize(long_button_size_).height);
  QSize short_button_size =
      QSize(size_handler.GameToWindowSize(short_button_size_).width,
            size_handler.GameToWindowSize(short_button_size_).height);
  Size shift =
      size_handler.GameToWindowSize({0, long_button_size_.height + shift_});

  Coordinate start_game_button_position =
      size_handler.GameToWindowCoordinate(first_button_coordinate_);
  start_game_button_->move(start_game_button_position.x,
                           start_game_button_position.y);
  start_game_button_->resize(long_button_size);
  start_game_button_->setIconSize(long_button_size);

  Coordinate dec_level_button_position = start_game_button_position + shift;
  dec_level_button_->move(dec_level_button_position.x,
                          dec_level_button_position.y);
  dec_level_button_->resize(short_button_size);
  dec_level_button_->setIconSize(short_button_size);

  Coordinate level_number_position =
      dec_level_button_position + Size(shift.height, 0);
  choose_level_number_->move(level_number_position.x, level_number_position.y);
  QSize level_number_size = long_button_size - QSize(shift.height, 0) * 2;
  choose_level_number_->resize(level_number_size);
  choose_level_number_->setIconSize(long_button_size);

  Coordinate inc_level_button_position =
      dec_level_button_position + Size(long_button_size.width(), 0) - Size(short_button_size.height(), 0);
  inc_level_button_->move(inc_level_button_position.x,
                          inc_level_button_position.y);
  inc_level_button_->resize(short_button_size);
  inc_level_button_->setIconSize(short_button_size);

  Coordinate settings_button_position = dec_level_button_position + shift;
  settings_button_->move(settings_button_position.x,
                         settings_button_position.y);
  settings_button_->resize(long_button_size);
  settings_button_->setIconSize(long_button_size);

  Coordinate exit_button_position = settings_button_position + shift;
  exit_button_->move(exit_button_position.x, exit_button_position.y);
  exit_button_->resize(long_button_size);
  exit_button_->setIconSize(long_button_size);
}

void ButtonHandler::CreateSettingsButtons(AbstractController* controller) {
  language_button_ = new QPushButton(main_window_);
  language_button_->setIcon(QIcon(
      ":resources/buttons_images/language_button_eng.png"));
  auto language_button_click = [&]() {
    // changing language
    if (is_language_rus_) {
      language_button_->setIcon(QIcon(
          ":resources/buttons_images/language_button_rus.png"));
    } else {
      language_button_->setIcon(QIcon(
          ":resources/buttons_images/language_button_eng.png"));
    }
    is_language_rus_ = 1 - is_language_rus_;
  };
  connect(language_button_, &QPushButton::clicked, language_button_click);

  sound_button_ = new QPushButton(main_window_);
  sound_button_->setIcon(QIcon(
      ":resources/buttons_images/sound_button_on.png"));
  auto sound_button_click = [&]() {
    // changing sound
    if (is_sound_on) {
      sound_button_->setIcon(QIcon(
          ":resources/buttons_images/sound_button_off.png"));
    } else {
      sound_button_->setIcon(QIcon(
          ":resources/buttons_images/sound_button_on.png"));
    }
    is_sound_on = 1 - is_sound_on;
  };
  connect(sound_button_, &QPushButton::clicked, sound_button_click);

  reset_game_button_ = new QPushButton(main_window_);
  reset_game_button_->setIcon(QIcon(
      ":resources/buttons_images/reset_game_button.png"));
  auto reset_game_click = [&]() {
    // reseting game, will be updated when saving is done
  };
  connect(reset_game_button_, &QPushButton::clicked, reset_game_click);

  to_main_menu_button_ = new QPushButton(main_window_);
  to_main_menu_button_->setIcon(QIcon(
      ":resources/buttons_images/to_main_menu_button.png"));
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
  QSize long_button_size =
      QSize(size_handler.GameToWindowSize(long_button_size_).width,
            size_handler.GameToWindowSize(long_button_size_).height);
  QSize short_button_size =
      QSize(size_handler.GameToWindowSize(short_button_size_).width,
            size_handler.GameToWindowSize(short_button_size_).height);
  Size shift =
      size_handler.GameToWindowSize({0, long_button_size_.height + shift_});

  Coordinate sound_button_position =
      size_handler.GameToWindowCoordinate(first_button_coordinate_)
          + Size(long_button_size.width(), 0) / 2
          - Size(short_button_size.width(), 0);
  sound_button_->move(sound_button_position.x, sound_button_position.y);
  sound_button_->resize(short_button_size);
  sound_button_->setIconSize(short_button_size);

  Coordinate language_button_position = sound_button_position
      + Size(shift.height, 0);
  language_button_->move(language_button_position.x,
                         language_button_position.y);
  language_button_->resize(short_button_size);
  language_button_->setIconSize(short_button_size);

  Coordinate reset_game_button_position =
      size_handler.GameToWindowCoordinate(first_button_coordinate_) + shift;
  reset_game_button_->move(reset_game_button_position.x,
                           reset_game_button_position.y);
  reset_game_button_->resize(long_button_size);
  reset_game_button_->setIconSize(long_button_size);

  Coordinate to_main_menu_button_position = reset_game_button_position + shift;
  to_main_menu_button_->move(to_main_menu_button_position.x,
                             to_main_menu_button_position.y);
  to_main_menu_button_->resize(long_button_size);
  to_main_menu_button_->setIconSize(long_button_size);
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

void ButtonHandler::CreateGameButtons(AbstractController* controller) {
  pause_button_ = new QPushButton(main_window_);
  pause_button_->setIcon(QIcon(
      ":resources/buttons_images/pause_button.png"));
  auto pause_button_click = [&]() {
    // pause
    window_type_ = WindowType::kPauseMenu;
  };
  connect(pause_button_, &QPushButton::clicked, pause_button_click);

  zero_speed_button_ = new QPushButton(main_window_);
  zero_speed_button_->setIcon(QIcon(
      ":resources/buttons_images/zero_speed_button.png"));
  auto zero_speed_button_click = [&]() {
    // zero speed
  };
  connect(zero_speed_button_, &QPushButton::clicked, zero_speed_button_click);

  normal_speed_button_ = new QPushButton(main_window_);
  normal_speed_button_->setIcon(QIcon(
      ":resources/buttons_images/normal_speed_button.png"));
  auto normal_speed_button_click = [&]() {
    // normal speed
  };
  connect(normal_speed_button_,
          &QPushButton::clicked,
          normal_speed_button_click);

  double_speed_button_ = new QPushButton(main_window_);
  double_speed_button_->setIcon(QIcon(
      ":resources/buttons_images/double_speed_button.png"));
  auto double_speed_button_click = [&]() {
    // double speed
  };
  connect(double_speed_button_,
          &QPushButton::clicked,
          double_speed_button_click);
}

void ButtonHandler::MoveGameButtons(SizeHandler size_handler) {
  QSize short_button_size =
      QSize(size_handler.GameToWindowSize(short_button_size_).width,
            size_handler.GameToWindowSize(short_button_size_).height);
  Size shift =
      size_handler.GameToWindowSize({short_button_size_.width + shift_, 0});
  Coordinate
      pause_button_position = size_handler.GameToWindowCoordinate({0, 0});
  pause_button_->move(pause_button_position.x,
                      pause_button_position.y);
  pause_button_->resize(short_button_size);
  pause_button_->setIconSize(short_button_size);

  Coordinate zero_speed_button_position =
      size_handler.GameToWindowCoordinate({kGameWidth, 0}) - shift * 2
          - Size(short_button_size.width(), 0);
  zero_speed_button_->move(zero_speed_button_position.x,
                           zero_speed_button_position.y);
  zero_speed_button_->resize(short_button_size);
  zero_speed_button_->setIconSize(short_button_size);

  Coordinate normal_speed_button_position = zero_speed_button_position + shift;
  normal_speed_button_->move(normal_speed_button_position.x,
                           normal_speed_button_position.y);
  normal_speed_button_->resize(short_button_size);
  normal_speed_button_->setIconSize(short_button_size);

  Coordinate double_speed_button_position = normal_speed_button_position + shift;
  double_speed_button_->move(double_speed_button_position.x,
                             double_speed_button_position.y);
  double_speed_button_->resize(short_button_size);
  double_speed_button_->setIconSize(short_button_size);
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

void ButtonHandler::CreatePauseMenuButtons(AbstractController* controller) {
  restart_button_ = new QPushButton(main_window_);
  restart_button_->setIcon(QIcon(":resources/buttons_images/restart_button.png"));
  auto restart_button_click = [&]() {
    controller_->EndGame(Exit::kLose);
    controller_->StartGame(level_number_);
    window_type_ = WindowType::kGame;
    DisablePauseMenuUi();
    main_window_->repaint();
  };
  connect(restart_button_, &QPushButton::clicked, restart_button_click);

  continue_button_ = new QPushButton(main_window_);
  continue_button_->setIcon(QIcon(
      ":resources/buttons_images/continue_button.png"));
  auto continue_button_click = [&]() {
    // continue timer
    window_type_ = WindowType::kGame;
    DisablePauseMenuUi();
    main_window_->repaint();
  };
  connect(continue_button_, &QPushButton::clicked, continue_button_click);
}

void ButtonHandler::MovePauseMenuButtons(SizeHandler size_handler) {
  QSize long_button_size =
      QSize(size_handler.GameToWindowSize(long_button_size_).width,
            size_handler.GameToWindowSize(long_button_size_).height);
  Size shift =
      size_handler.GameToWindowSize({0, long_button_size_.height + shift_,});
  Coordinate continue_button_position =
      size_handler.GameToWindowCoordinate(first_button_coordinate_);
  continue_button_->move(continue_button_position.x,
                         continue_button_position.y);
  continue_button_->resize(long_button_size);
  continue_button_->setIconSize(long_button_size);

  Coordinate restart_button_position = continue_button_position + shift;
  restart_button_->move(restart_button_position.x, restart_button_position.y);
  restart_button_->resize(long_button_size);
  restart_button_->setIconSize(long_button_size);
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
