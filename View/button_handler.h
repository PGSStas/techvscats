#ifndef VIEW_BUTTON_HANDLER_H_
#define VIEW_BUTTON_HANDLER_H_

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QString>
#include <QSettings>
#include <QTranslator>

#include <algorithm>

#include "Controller/abstract_controller.h"
#include "menu_button.h"
#include "size_handler.h"

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras>
#endif

class ButtonHandler : public QObject {
  Q_OBJECT

 public:
  ButtonHandler(QMainWindow* main_window, AbstractController* controller,
                int font_id);
  ~ButtonHandler() override = default;

  void CreateButtons();
  void UpdateButtonsStatus(bool online_status, bool register_status);
  void RescaleButtons(SizeHandler size_handler);

  void SetMainMenuUiVisible(bool visible);
  void SetSettingsUiVisible(bool visible);
  void SetGameUiVisible(bool visible);
  void SetPauseMenuUiVisible(bool visible);
  void SetSpeed(int casted_speed);

  void SetSpeedButtonsState(Speed speed);
  WindowType GetWindowType() const;

  void SetCurrentLevel(int level);
  int GetCurrentLevel() const;

 private:
  // creating main menu
  void CreateMainMenuButtons();
  void RescaleMainMenuButtons(SizeHandler size_handler);
  // creating settings
  void CreateSettingsButtons();
  void RescaleSettingsButtons(SizeHandler size_handler);
  // creating game window
  void CreateGameButtons();
  void RescaleGameButtons(SizeHandler size_handler);
  // creating pause menu
  void CreatePauseMenuButtons();
  void RescalePauseMenuButtons(SizeHandler size_handler);

  void SetSoundOn(bool sound_on);
  void SetFullscreen(bool fullscreen);

 private:
  QMainWindow* main_window_;
  WindowType window_type_ = WindowType::kMainMenu;
  AbstractController* controller_;
  MusicPlayer* music_player_;

  // main_menu
  MenuButton* start_game_button_;
  MenuButton* choose_level_number_;
  MenuButton* inc_level_button_;
  MenuButton* dec_level_button_;
  MenuButton* settings_button_;
  MenuButton* exit_button_;
  MenuButton* online_button_;

  // Game window
  MenuButton* pause_button_;
  MenuButton* zero_speed_button_;
  MenuButton* normal_speed_button_;
  MenuButton* double_speed_button_;

  // Settings window
  MenuButton* language_button_;
  MenuButton* sound_button_;
  MenuButton* fullscreen_button_;
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
  bool is_fullscreen_ = true;
  int font_id_;

  // left to check icons
  bool is_language_russian_ = true;

  const int kMaxLevel_ = 2;
};

#endif  // VIEW_BUTTON_HANDLER_H_
