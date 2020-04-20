#ifndef VIEW_MENU_BUTTON_H_
#define VIEW_MENU_BUTTON_H_

#include <QPushButton>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPalette>
#include <QFontDatabase>
#include <memory>
#include <string>
#include "size_handler.h"
#include "Model/constants.h"

namespace buttonconstants {
const int kMenuBorderSize = 12;
const Size kLongButtonSize(640, 72);
const Size kShortButtonSize(72, 72);
const int kMenuFontSize = 36;
const Coordinate kFirstButtonCoordinate(640, 360);
const int kShift = 8;
}

class MenuButton : public QPushButton {
 public:
  MenuButton() : button_size_(0, 0), border_size_(0) {}
  MenuButton(const QString& text, const Size& button_size,
             QMainWindow* main_window, const QString& icon = "");
  void Move(Coordinate game_coordinate, SizeHandler size_handler);

 private:
  void enterEvent(QEvent*) override;
  void leaveEvent(QEvent*) override;
  Size button_size_;
  int border_size_;
};

#endif  // VIEW_MENU_BUTTON_H_
