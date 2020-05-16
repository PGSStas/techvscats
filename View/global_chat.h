#ifndef VIEW_GLOBAL_CHAT_H_
#define VIEW_GLOBAL_CHAT_H_

#include <QApplication>
#include <QScroller>
#include <QStringList>
#include <QLineEdit>
#include <QTextBrowser>
#include <QMainWindow>
#include <QScrollBar>
#include <QInputMethod>

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

  bool IsMessagesQueueEmpty() const;
  const QString& GetMessageToSend() const;
  void PopMessageQueue();

  void Clear();
  void ReceiveNewMessages(const QStringList& messages);

  void SetVisible(bool visible);

 private:
  bool using_game_style_ = true;

  bool is_brick_going_up_ = false;
  int how_high_brick_percent_ = 0;
  bool is_brick_going_right_ = false;
  int how_right_brick_percent_ = 0;

  QStringList text_browser_messages_;
  QStringList send_messages_;

  QTextBrowser* q_text_browser_;
  QLineEdit* q_line_edit_;
  MenuButton* send_button;
  MenuButton* brick_button;

  const int kMaxChatSize = 30;
  const int kFontId = 0;
  const int kCloseSpeed = 60;
  const Size kTextEditSize = {700, 60};
  const double kFondSize = 26;
  const Coordinate kBottomLeftPosition = {20, 1060};

  void SendMessage();
};

#endif  // VIEW_GLOBAL_CHAT_H_
