#ifndef VIEW_BUTTON_HANDLER_H_
#define VIEW_BUTTON_HANDLER_H_

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

enum class Language {
  kRussian,
  kEnglish
};

class ButtonHandler : QObject {
 public:
  explicit ButtonHandler(QMainWindow* main_window);

  void EnableMainMenuUi();
  void DisableMainMenuUi();
  void EnableSettingsUi();
  void DisableSettingsUi();
  void EnableGameUi();
  void DisableGameUi();
  void EnablePauseMenuUi();
  void DisablePauseMenuUi();

  void CreateButtons(AbstractController* controller);
  void MoveButtons(SizeHandler size_handler);

  WindowType GetWindowType();

 private:
  // creating main menu
  void CreateMainMenuButtons();
  void MoveMainMenuButtons(SizeHandler size_handler);
  // creating settings
  void CreateSettingsButtons();
  void MoveSettingsButtons(SizeHandler size_handler);
  // creating game window
  void CreateGameButtons();
  void MoveGameButtons(SizeHandler size_handler);
  // creating pause menu
  void CreatePauseMenuButtons();
  void MovePauseMenuButtons(SizeHandler size_handler);

  void ChangeLanguage();

 private:
  QMainWindow* main_window_;
  WindowType window_type_;
  AbstractController* controller_;

  // main_menu
  MenuButton* start_game_button_;
  MenuButton* choose_level_number_;
  MenuButton* inc_level_button_;
  MenuButton* dec_level_button_;
  MenuButton* settings_button_;
  MenuButton* exit_button_;

  // Game window
  MenuButton* pause_button_;
  MenuButton* zero_speed_button_;
  MenuButton* normal_speed_button_;
  MenuButton* double_speed_button_;

  // Settings window
  MenuButton* language_button_;
  MenuButton* sound_button_;
  MenuButton* reset_game_button_;
  MenuButton* to_main_menu_button_;

  // pause menu button
  MenuButton* continue_button_;
  MenuButton* restart_button_;
  // to_main_menu_button_ is also here

  int level_number_ = 1;
  Size long_button_size_ = Size(kLongButtonWidth, kLongButtonHeight);
  Size short_button_size_ = Size(kShortButtonSize, kShortButtonSize);
  Coordinate first_button_coordinate_ =
      Coordinate(kFirstButtonCoordinateX, kFirstButtonCoordinateY);
  int shift_ = kShift;
  Language language_;
  bool is_sound_on_ = true;
};

#endif  // VIEW_BUTTON_HANDLER_H_
