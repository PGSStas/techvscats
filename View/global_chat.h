#ifndef VIEW_GLOBAL_CHAT_H_
#define VIEW_GLOBAL_CHAT_H_

#include <QStringList>
#include <QLineEdit>
#include <QTextBrowser>
#include <QMainWindow>
#include <QScrollBar>

#include <algorithm>

#include "View/menu_button.h"
#include "Model/coordinate.h"
#include "size_handler.h"

class GlobalChat : QLineEdit {
  Q_OBJECT

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

 private:
  bool is_game_style_using_ = true;
  int how_high_brick_percent_ = 100;
  bool is_brick_going_up_ = true;
  QStringList text_browser_messages_;
  QStringList send_messages_;

  QTextBrowser* q_text_browser_;
  MenuButton* send_button;
  MenuButton* brick_button;

  const int kMaxChatSize = 9;
  const Coordinate kBottomLeftPosition = {20, 1080};
  const Size kTextEditSize = {700, 60};
  const double kFondSize = 26;
  const int kFontId = 0;
  const int kCloseSpeed = 60;

 private:
  void keyPressEvent(QKeyEvent* event) override;
  void SendMessage();
};

#endif  // VIEW_GLOBAL_CHAT_H_
