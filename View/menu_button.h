#ifndef VIEW_MENU_BUTTON_H_
#define VIEW_MENU_BUTTON_H_

#include <QFontDatabase>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>

#include <chrono>
#include <memory>
#include <random>
#include <string>

#include "size_handler.h"
#include "Model/constants.h"

namespace button_constants {
const int kMenuBorderSize = 12;

#ifndef Q_OS_ANDROID
const Size kLongButtonSize = Size(640, 72);
const Size kShortButtonSize = Size(72, 72);
#else
const Size kLongButtonSize = Size(640, 110);
const Size kShortButtonSize = Size(110, 110);
#endif

const int kMenuFontSize = 36;

#ifndef Q_OS_ANDROID
const Coordinate kFirstButtonCoordinate = Coordinate(640, 360);
#else
const Coordinate kFirstButtonCoordinate = Coordinate(640, 240);
#endif

const int kShift = 20;
}  // namespace button_constants

class MenuButton : public QPushButton {
 public:
  MenuButton(const QString& text, const Size& button_size,
             QMainWindow* main_window, int font_id);
  MenuButton(const Size& button_size, QMainWindow* main_window,
             const QString& main_icon_path, const QString& active_icon_path);

  ~MenuButton() override = default;

  void UpdateIcon();
  void SetIsEnter(bool enter);
  void SetGeometry(Coordinate game_coordinate, SizeHandler size_handler);
  void SetSecondIconPath(const QString& main_icon_path,
                         const QString& active_icon_path);
  Coordinate GetPosition() const;
  void EnableSecondIcon(bool is_second_icon_enabled);
  void ResetStyleSheet();

 private:
  // changing hover color and back
  void enterEvent(QEvent*) override;
  void leaveEvent(QEvent*) override;

 private:
  Size button_size_{0, 0};
  Coordinate position_{0, 0};
  int border_size_ = 0;
  QIcon main_icon_1_;
  QIcon active_icon_1_;

  bool is_second_icon_enabled_ = false;
  bool have_entered_event_ = false;
  QIcon main_icon_2_;
  QIcon active_icon_2_;

  static std::mt19937 random_generator_;
};

#endif  // VIEW_MENU_BUTTON_H_
