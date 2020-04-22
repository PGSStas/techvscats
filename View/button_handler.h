#ifndef VIEW_BUTTON_HANDLER_H_
#define VIEW_BUTTON_HANDLER_H_

#include <QMainWindow>
#include <QPushButton>
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
  explicit ButtonHandler(QMainWindow* main_window,
                         AbstractController* controller);
  ~ButtonHandler() override = default;

  void CreateButtons();
  void SetButtonsGeometry(SizeHandler size_handler);

  void SetMainMenuUiVisible(bool visible);
  void SetSettingsUiVisible(bool visible);
  void SetGameUiVisible(bool visible);
  void SetPauseMenuUiVisible(bool visible);

  void SetSpeedButtonsState(Speed speed);
  WindowType GetWindowType() const;

 private:
  // creating main menu
  void CreateMainMenuButtons();
  void SetMainMenuButtonsGeometry(SizeHandler size_handler);
  // creating settings
  void CreateSettingsButtons();
  void SetSettingsButtonsGeometry(SizeHandler size_handler);
  // creating game window
  void CreateGameButtons();
  void SetGameButtonsGeometry(SizeHandler size_handler);
  // creating pause menu
  void CreatePauseMenuButtons();
  void SetPauseMenuButtonsGeometry(SizeHandler size_handler);

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
  Size long_button_size_ = button_constants::kLongButtonSize;
  Size short_button_size_ = button_constants::kShortButtonSize;
  Coordinate first_button_coordinate_ =
      button_constants::kFirstButtonCoordinate;
  int shift_ = button_constants::kShift;
  bool is_sound_on_ = true;
  int font_id_;

  // left to check icons
  bool is_language_russian_ = true;
};

#endif  // VIEW_BUTTON_HANDLER_H_
