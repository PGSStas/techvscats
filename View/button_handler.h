#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QPixmap>
#include <QString>
#include "Controller/abstract_controller.h"
#include "menu_button.h"
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

  void CreateButtons(AbstractController* controller);
  void MoveButtons(std::shared_ptr<SizeHandler> size_handler);

  WindowType GetWindowType();

 private:
  // creating main menu
  void CreateMainMenuButtons(AbstractController* controller);
  void MoveMainMenuButtons(std::shared_ptr<SizeHandler> size_handler);
  // creating settings
  void CreateSettingsButtons(AbstractController* controller);
  void MoveSettingsButtons(std::shared_ptr<SizeHandler> size_handler);
  // creating game window
  void CreateGameButtons(AbstractController* controller);
  void MoveGameButtons(std::shared_ptr<SizeHandler> size_handler);
  // creating pause menu
  void CreatePauseMenuButtons(AbstractController* controller);
  void MovePauseMenuButtons(std::shared_ptr<SizeHandler> size_handler);

 private:
  QMainWindow* main_window_;
  WindowType window_type_;
  AbstractController* controller_;

  // main_menu
  MenuButton start_game_button_;
  MenuButton choose_level_number_;
  MenuButton inc_level_button_;
  MenuButton dec_level_button_;
  MenuButton settings_button_;
  MenuButton exit_button_;

  // Game window
  MenuButton pause_button_;
  MenuButton zero_speed_button_;
  MenuButton normal_speed_button_;
  MenuButton double_speed_button_;

  // Settings window
  MenuButton language_button_;
  MenuButton sound_button_;
  MenuButton reset_game_button_;
  MenuButton to_main_menu_button_;

  // pause menu button
  MenuButton continue_button_;
  MenuButton restart_button_;
  // to_main_menu_button_ is also here

  void ChangeLanguage();

  int level_number_ = 1;
  Size long_button_size_ = Size(640, 72);
  Size short_button_size_ = Size(72, 72);
  Coordinate first_button_coordinate_ = Coordinate(640, 360);
  int shift_ = 8;
  bool is_language_rus_ = true;
  bool is_sound_on = true;
};

#endif //BUTTON_HANDLER_H
