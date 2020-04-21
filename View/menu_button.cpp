#include <QtWidgets/QStyle>
#include "menu_button.h"

MenuButton::MenuButton(const QString& text, const Size& button_size,
                       QMainWindow* main_window, const QString& main_icon_path,
                       const QString& active_icon_path)
    : QPushButton(text, main_window), main_icon_path_(main_icon_path),
    active_icon_path_(active_icon_path) {
  setMouseTracking(true);
  int font_id = QFontDatabase::addApplicationFont(
      ":resources/buttons_resources/14722.ttf");
  QString family = QFontDatabase::applicationFontFamilies(font_id).at(0);
  QFont font(family);
  font.setBold(true);
  setFont(font);
  setStyleSheet("background-color: #ffffff;");
  setIcon(QIcon(main_icon_path_));
  button_size_ = button_size;
  setCursor(Qt::PointingHandCursor);
}

void MenuButton::SetGeometry(
    Coordinate game_coordinate, SizeHandler size_handler) {
  Coordinate
      window_coordinate = size_handler.GameToWindowCoordinate(game_coordinate);
  Size window_size = size_handler.GameToWindowSize(button_size_);
  this->setGeometry(window_coordinate.x, window_coordinate.y,
                    window_size.width, window_size.height);
  setIconSize(QSize(window_size.width, window_size.height));

  auto font = this->font();
  font.setPixelSize(size_handler.GameToWindowLength(
      button_constants::kMenuFontSize));
  setFont(font);

  border_size_ =
      size_handler.GameToWindowLength(button_constants::kMenuBorderSize);
  QString style_sheet =
      "border: " + QString::number(border_size_) + "px solid #000000;";
  setStyleSheet(style_sheet);
}

void MenuButton::enterEvent(QEvent*) {
  QString style_sheet =
      "border: " + QString::number(border_size_) + "px solid #000000;";
  style_sheet += "background-color: " +
      QColor::fromRgb(QRandomGenerator::global()->generate()).name() + ";";
  setStyleSheet(style_sheet);
  setIcon(QIcon(active_icon_path_));
}

void MenuButton::leaveEvent(QEvent*) {
  QString style_sheet =
      "border: " + QString::number(border_size_) + "px solid #000000;";
  style_sheet += "background-color: #ffffff;";
  setStyleSheet(style_sheet);
  setIcon(QIcon(main_icon_path_));
}

void MenuButton::SetActiveIconPath(const QString& active_icon) {
  active_icon_path_ = active_icon;
}

void MenuButton::SetIconPath(const QString& main_icon) {
  main_icon_path_ = main_icon;
  setIcon(QIcon(main_icon_path_));
}
