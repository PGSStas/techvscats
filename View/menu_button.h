#ifndef VIEW_MENU_BUTTON_H_
#define VIEW_MENU_BUTTON_H_

#include <QPushButton>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPalette>
#include <QFontDatabase>
#include <QRandomGenerator>
#include <memory>
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
  MenuButton() = default;
  MenuButton(const QString& text, const Size& button_size,
             QMainWindow* main_window, const QString& main_icon_path = "",
             const QString& active_icon_path = "");
  ~MenuButton() override = default;

  void SetGeometry(Coordinate game_coordinate, SizeHandler size_handler);
  void SetIconPath(const QString& main_icon);
  void SetActiveIconPath(const QString& active_icon);

 private:
  void enterEvent(QEvent*) override;
  void leaveEvent(QEvent*) override;

 private:
  Size button_size_ = Size(0, 0);
  int border_size_ = 0;
  QString main_icon_path_;
  QString active_icon_path_;
};

#endif  // VIEW_MENU_BUTTON_H_
