#include <QtWidgets/QStyle>
#include "menu_button.h"

std::mt19937 MenuButton::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

MenuButton::MenuButton(const QString& text, const Size& button_size,
                       QMainWindow* main_window, int font_id)
    : QPushButton(text, main_window),
      button_size_(button_size) {
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
      button_size_(button_size),
      main_icon_1_(main_icon_path),
      active_icon_1_(active_icon_path) {
  setIcon(main_icon_1_);
  setCursor(Qt::PointingHandCursor);
  setMouseTracking(true);
}

void MenuButton::SetGeometry(
    Coordinate game_coordinate, SizeHandler size_handler) {
  position_ = game_coordinate;
  auto window_coordinate = size_handler.GameToWindowCoordinate(game_coordinate);
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
  setIcon((is_second_icon_enabled_) ? active_icon_2_ : active_icon_1_);
}

void MenuButton::leaveEvent(QEvent*) {
  QString style_sheet =
      "border: " + QString::number(border_size_) + "px solid #000000;";
  style_sheet += "background-color: #ffffff;";
  setStyleSheet(style_sheet);
  setIcon((is_second_icon_enabled_) ? main_icon_2_ : main_icon_1_);
}

void MenuButton::SetSecondIconPath(const QString& main_icon_path,
                                   const QString& active_icon_path) {
  main_icon_2_ = QIcon(main_icon_path);
  active_icon_2_ = QIcon(active_icon_path);
}

void MenuButton::EnableSecondIcon(bool is_second_icon_enabled) {
  is_second_icon_enabled_ = is_second_icon_enabled;
}

Coordinate MenuButton::GetPosition() const {
  return position_;
}
