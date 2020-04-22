#include <QtWidgets/QStyle>
#include "menu_button.h"

std::mt19937 MenuButton::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

MenuButton::MenuButton(const QString& text, const Size& button_size,
                       QMainWindow* main_window, int font_id)
    : QPushButton(text, main_window) {
  QString family = QFontDatabase::applicationFontFamilies(font_id).at(0);
  QFont font(family);
  font.setBold(true);
  setFont(font);
  setMouseTracking(true);
  setStyleSheet("background-color: #ffffff;");
  button_size_ = button_size;
  setCursor(Qt::PointingHandCursor);
}

MenuButton::MenuButton(const Size& button_size,
                       QMainWindow* main_window,
                       const QString& main_icon_path,
                       const QString& active_icon_path)
    : QPushButton(main_window),
      main_icon_(main_icon_path),
      active_icon_(active_icon_path) {
  setIcon(main_icon_);
  button_size_ = button_size;
  setCursor(Qt::PointingHandCursor);
  setMouseTracking(true);
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
      QColor::fromRgb(static_cast<int32_t>(random_generator_())).name() + ";";
  setStyleSheet(style_sheet);
  if (!is_second_icons_active_) {
    setIcon(active_icon_);
  } else {
    setIcon(active_icon_2_);
  }
}

void MenuButton::leaveEvent(QEvent*) {
  QString style_sheet =
      "border: " + QString::number(border_size_) + "px solid #000000;";
  style_sheet += "background-color: #ffffff;";
  setStyleSheet(style_sheet);
  if (!is_second_icons_active_) {
    setIcon(main_icon_);
  } else {
    setIcon(main_icon_2_);
  }
}

void MenuButton::SetSecondIconPath(const QString& main_icon,
                                   const QString& active_icon) {
  main_icon_2_ = QIcon(main_icon);
  active_icon_2_ = QIcon(active_icon);
}

void MenuButton::SetSecondIconActive(bool is_second_icon_active) {
  is_second_icons_active_ = is_second_icon_active;
}
