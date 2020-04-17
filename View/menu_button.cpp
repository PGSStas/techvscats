#include <QtWidgets/QStyle>
#include "menu_button.h"

MenuButton::MenuButton(const QString& text,
                       const Size button_size,
                       QMainWindow* main_window,
                       const QString& icon) {
  button_ = new QPushButton(main_window);
  int id = QFontDatabase::addApplicationFont(":resources/buttons_images/14722.ttf");
  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  button_->setFont(QFont(family));
  button_->setText(text);
  button_->setStyleSheet("border: 1px solid #000000; background-color: #ffffff;");
  if (icon != "") {
    button_->setIcon(QIcon(icon));
  }
  button_size_ = button_size;
  button_->setCursor(Qt::PointingHandCursor);
}

void MenuButton::Move(Coordinate game_coordinate,
                      std::shared_ptr<SizeHandler> size_handler) {
  Coordinate
      window_coordinate = size_handler->GameToWindowCoordinate(game_coordinate);
  button_->move(window_coordinate.x, window_coordinate.y);
  Size window_size = size_handler->GameToWindowSize(button_size_);
  button_->resize(window_size.width, window_size.height);
  button_->setIconSize(QSize(window_size.width, window_size.height));

  auto font = button_->font();
  font.setPointSize(size_handler->GameToWindowLength(18));
  font.setBold(true);
  button_->setFont(font);

  int border = size_handler->GameToWindowLength(12);
  QString
      style_sheet = "border: " + QString::number(border) + "px solid #000000;";
  button_->setStyleSheet(style_sheet);
}

void MenuButton::Show() {
  button_->show();
}

void MenuButton::Hide() {
  button_->hide();
}

QPushButton* MenuButton::GetQPushButton() {
  return button_;
}
void MenuButton::SetText(const QString& text) {
  button_->setText(text);
}

void MenuButton::SetIcon(const QString& icon) {
  button_->setIcon(QIcon(icon));
}
