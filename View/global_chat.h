#ifndef VIEW_GLOBAL_CHAT_H
#define VIEW_GLOBAL_CHAT_H

#include <QTextEdit>
#include <QTextBrowser>
#include <QMainWindow>

#include "View/menu_button.h"
#include "Model/coordinate.h"
#include "size_handler.h"

class GlobalChat {
 public:
  GlobalChat(QMainWindow*);
  void RescaleChat(const SizeHandler& size_handler);
//  void Draw(const SizeHandler& size_handler) const;
 // void Tick();

 private:
  QTextBrowser* q_text_browser_;
  QTextEdit* q_text_edit_;
  MenuButton* send_button;
  const Coordinate kBottomLeftPosition = {0, 1080};
  const Size kSize = {200, 300};



};

#endif //  VIEW_GLOBAL_CHAT_H
