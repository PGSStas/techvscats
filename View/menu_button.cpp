#include <QtWidgets/QStyle>
#include "menu_button.h"

MenuButton::MenuButton(const QString& text, const Size& button_size,
                       QMainWindow* main_window, const QString& icon) :
    QPushButton(text, main_window) {
  setMouseTracking(true);
  int id =
      QFontDatabase::addApplicationFont(":resources/buttons_resources/14722.ttf");
  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  setFont(QFont(family));
  setStyleSheet("background-color: #ffffff;");
  if (icon != "") {
    setIcon(QIcon(icon));
  }
  button_size_ = button_size;
  setCursor(Qt::PointingHandCursor);
}

void MenuButton::Move(Coordinate game_coordinate, SizeHandler size_handler) {
  Coordinate
      window_coordinate = size_handler.GameToWindowCoordinate(game_coordinate);
  move(window_coordinate.x, window_coordinate.y);
  Size window_size = size_handler.GameToWindowSize(button_size_);
  resize(window_size.width, window_size.height);
  setIconSize(QSize(window_size.width, window_size.height));

  auto font = this->font();
  font.setPointSize(size_handler.GameToWindowLength(kMenuFontSize));
  font.setBold(true);
  setFont(font);

  border_size_ = size_handler.GameToWindowLength(kMenuBorderSize);
  QString style_sheet =
      "border: " + QString::number(border_size_) + "px solid #000000;";
  setStyleSheet(style_sheet);
}

void MenuButton::enterEvent(QEvent*) {
  QString style_sheet =
      "border: " + QString::number(border_size_) + "px solid #000000;";
  style_sheet += "background-color: #dddddd;";
  setStyleSheet(style_sheet);
}

void MenuButton::leaveEvent(QEvent*) {
  QString style_sheet =
      "border: " + QString::number(border_size_) + "px solid #000000;";
  style_sheet += "background-color: #ffffff;";
  setStyleSheet(style_sheet);
}
