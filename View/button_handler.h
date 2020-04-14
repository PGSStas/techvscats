#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QPixmap>
#include <QString>
#include "Controller/abstract_controller.h"
#include "size_handler.h"

enum class WindowType {
  kMainMenu,
  kGame,
  kSettings,
  kPauseMenu
};

class ButtonHandler : QObject {

 public:
  ButtonHandler(QMainWindow* main_window);

  void EnableMainMenuUi();
  void DisableMainMenuUi();
  void EnableSettingsUi();
  void DisableSettingsUi();
  void EnableGameUi();
  void DisableGameUi();
  void EnablePauseMenuUi();
  void DisablePauseMenuUi();

  // creating main menu
  void CreateMainMenuButtons(AbstractController* controller);
  void MoveMainMenuButtons(SizeHandler size_handler);
  // creating settings
  void CreateSettingsButtons(AbstractController* controller);
  void MoveSettingsButtons(SizeHandler size_handler);
  // creating game window
  void CreateGameButtons(AbstractController* controller);
  void MoveGameButtons(SizeHandler size_handler);
  // creating pause menu
  void CreatePauseMenuButtons(AbstractController* controller);
  void MovePauseMenuButtons(SizeHandler size_handler);
  WindowType GetWindowType();

 private:
  QMainWindow* main_window_;
  WindowType window_type_;
  AbstractController* controller_;

  // main_menu
  QPushButton* start_game_button_;
  QPushButton* choose_level_number_;
  QPushButton* inc_level_button_;
  QPushButton* dec_level_button_;
  QPushButton* settings_button_;
  QPushButton* exit_button_;

  // Game window
  QPushButton* pause_button_;
  QPushButton* zero_speed_button_;
  QPushButton* normal_speed_button_;
  QPushButton* double_speed_button_;

  // Settings window
  QPushButton* language_button_;
  QPushButton* sound_button_;
  QPushButton* reset_game_button_;
  QPushButton* to_main_menu_button_;

  // pause menu button
  QPushButton* continue_button_;
  QPushButton* restart_button_;
  // to_main_menu_button_ is also here

  int level_number_ = 1;
  Size long_button_size_ = Size(640, 72);
  Size short_button_size_ = Size(72, 72);
  Coordinate first_button_coordinate_ = Coordinate(640, 360);
  int shift_ = 8;
  bool is_language_rus_ = true;
  bool is_sound_on = true;
};

#endif //BUTTON_HANDLER_H
