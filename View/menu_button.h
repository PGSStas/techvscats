#ifndef VIEW_MENU_BUTTON_H_
#define VIEW_MENU_BUTTON_H_

#include <QFontDatabase>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>
#include <QRandomGenerator>

#include <chrono>
#include <memory>
#include <random>
#include <string>

#include "size_handler.h"
#include "Model/constants.h"

namespace button_constants {
const int kMenuBorderSize = 12;
const Size kLongButtonSize = Size(640, 72);
const Size kShortButtonSize = Size(72, 72);
const int kMenuFontSize = 36;
const Coordinate kFirstButtonCoordinate = Coordinate(640, 360);
const int kShift = 8;
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

 private:
  // changing hover color and back
  void enterEvent(QEvent*) override;
  void leaveEvent(QEvent*) override;

 private:
  Size button_size_ = Size(0, 0);
  Coordinate position_;
  int border_size_ = 0;
  QIcon main_icon_1_;
  QIcon active_icon_1_;

  bool is_second_icon_enabled_ = false;
  bool is_enter_ = false;
  QIcon main_icon_2_;
  QIcon active_icon_2_;

  static std::mt19937 random_generator_;
};

#endif  // VIEW_MENU_BUTTON_H_
