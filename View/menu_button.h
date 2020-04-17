#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <QPushButton>
#include <QMainWindow>
#include <QPalette>
#include <QFontDatabase>
#include <memory>
#include <string>
#include "size_handler.h"

class MenuButton {
 public:
  MenuButton() : button_(nullptr), button_size_(0, 0) {}
  MenuButton(const QString& text, const Size button_size,
             QMainWindow* main_window, const QString& icon = "");

  void Move(Coordinate game_coordinate,
            std::shared_ptr<SizeHandler> size_handler);
  void Show();
  void Hide();
  void SetIcon(const QString& icon);
  void SetText(const QString& text);

  QPushButton* GetQPushButton();
 private:
  QPushButton* button_;
  Size button_size_;
};

#endif //MENU_BUTTON_H
