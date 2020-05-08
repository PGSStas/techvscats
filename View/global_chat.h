#ifndef VIEW_GLOBAL_CHAT_H_
#define VIEW_GLOBAL_CHAT_H_

#include <QStringList>
#include <QTextEdit>
#include <QTextBrowser>
#include <QMainWindow>
#include <QScrollBar>

#include <algorithm>

#include "View/menu_button.h"
#include "Model/coordinate.h"
#include "size_handler.h"

class GlobalChat {
 public:
  explicit GlobalChat(QMainWindow*);
  void RescaleChat(const SizeHandler& size_handler);
  void Tick(const SizeHandler&, int delta_time);
  void HideShow();
  void ChangeStyle();

  bool IsSendMessagesEmpty() const;
  const QString& GetMessageToSend() const;
  void PopMessageToSend();

  void Clear();
  void ReceiveNewMessages(const QStringList& messages);

 private:
  bool game_style_ = true;
  int up_percent_ = 100;
  bool is_go_up_ = true;
  QStringList text_browser_messages_;
  QStringList send_messages_;

  QTextBrowser* q_text_browser_;
  QTextEdit* q_text_edit_;
  MenuButton* send_button;
  MenuButton* close_open_button;

  const Coordinate kBottomLeftPosition = {20, 1080};
  const Size kTextEditSize = {700, 60};
  const double kFondSize = 26;
  const int kFontId = 0;
  const int kCloseSpeed = 60;

 private:
  void SendMessage();
};

#endif  // VIEW_GLOBAL_CHAT_H_
