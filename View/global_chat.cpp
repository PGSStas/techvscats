#include "global_chat.h"

GlobalChat::GlobalChat(QMainWindow* window) : QLineEdit(window) {
  QString family = QFontDatabase::applicationFontFamilies(kFontId).at(0);
  QFont font(family);
  font.setFixedPitch(true);

  q_text_browser_ = new QTextBrowser(window);
  q_text_browser_->setFont(font);
  setFont(font);
  send_button = new MenuButton(
      Size(kTextEditSize.height, kTextEditSize.height), window,
      ":resources/buttons_resources/inc_level_button.png",
      ":resources/buttons_resources/inc_level_button_active.png");
  send_button->SetSecondIconPath(
      ":resources/buttons_resources/normal_speed_button.png",
      ":resources/buttons_resources/normal_speed_button_active.png");
  auto send_button_click = [this]() {
    SendMessage();
  };

  QObject::connect(send_button, &QPushButton::clicked, send_button_click);

  brick_button = new MenuButton(
      Size(kTextEditSize.height, kTextEditSize.height), window,
      ":resources/buttons_resources/dec_level_button.png",
      ":resources/buttons_resources/dec_level_button_active.png");
  brick_button->SetSecondIconPath(
      ":resources/buttons_resources/pause_button.png",
      ":resources/buttons_resources/pause_button_active.png");

  auto close_open_button_click = [this]() {
    HideShow();
  };
  QObject::connect(brick_button,
                   &QPushButton::clicked,
                   close_open_button_click);
  ChangeStyle();
  show();
  brick_button->show();
  send_button->show();
  q_text_browser_->show();
}

void GlobalChat::RescaleChat(const SizeHandler& size_handler) {
  Size remove_edit_size =
      Size(-kTextEditSize.width * (1 - how_high_brick_percent_ / 100.0),
           kTextEditSize.height);
  Coordinate text_edit_position = size_handler.GameToWindowCoordinate(
      kBottomLeftPosition - remove_edit_size);

  Size text_edit_size = size_handler.GameToWindowSize(kTextEditSize);
  setGeometry(text_edit_position.x, text_edit_position.y,
              text_edit_size.width * how_high_brick_percent_ / 100.0,
              text_edit_size.height);

  send_button->SetGeometry(
      kBottomLeftPosition +
          Size(kTextEditSize.width, -kTextEditSize.height),
      size_handler);

  Coordinate text_browser_position =
      size_handler.GameToWindowCoordinate(
          {kBottomLeftPosition.x, kBottomLeftPosition.y
              - kTextEditSize.height * 10
              + kTextEditSize.height * 9
                  * (1 - how_high_brick_percent_ / 100.0)});
  Size text_browser_size = size_handler.GameToWindowSize(
      {kTextEditSize.width + kTextEditSize.height,
       kTextEditSize.height * 9 * how_high_brick_percent_ / 100});

  q_text_browser_->setGeometry(text_browser_position.x,
                               text_browser_position.y,
                               text_browser_size.width,
                               text_browser_size.height);

  auto font_ = font();
  font_.setPixelSize(size_handler.GameToWindowLength(kFondSize));
  setFont(font_);
  q_text_browser_->setFont(font_);

  brick_button->SetGeometry(
      kBottomLeftPosition +
          Size(kTextEditSize.width, -kTextEditSize.height
              - kTextEditSize.height * 9 / 100 * how_high_brick_percent_),
      size_handler);
}

void GlobalChat::Tick(const SizeHandler& size_handler, int delta_time) {
  if (is_brick_going_up_ && how_high_brick_percent_ < 100) {
    how_high_brick_percent_ += kCloseSpeed * delta_time / constants::kTimeScale;
    how_high_brick_percent_ = std::min(100, how_high_brick_percent_);
    RescaleChat(size_handler);
  }

  if (!is_brick_going_up_ && how_high_brick_percent_ > 0) {
    how_high_brick_percent_ -= kCloseSpeed * delta_time / constants::kTimeScale;
    how_high_brick_percent_ = std::max(0, how_high_brick_percent_);
    RescaleChat(size_handler);
  }
}

void GlobalChat::HideShow() {
  if (is_brick_going_up_ && how_high_brick_percent_ == 100) {
    is_brick_going_up_ = false;
  }
  if (!is_brick_going_up_ && how_high_brick_percent_ == 0) {
    is_brick_going_up_ = true;
  }
}

void GlobalChat::ChangeStyle() {
  is_game_style_using_ = !is_game_style_using_;
  QString style_sheet;
  if (is_game_style_using_) {
    style_sheet = " background-color : rgba(190,192,213,0.89);";
  }
  setStyleSheet(style_sheet);
  q_text_browser_->setStyleSheet(style_sheet);
  brick_button->EnableSecondIcon(is_game_style_using_);
  send_button->EnableSecondIcon(is_game_style_using_);
}

bool GlobalChat::IsMessagesQueueEmpty() const {
  return send_messages_.isEmpty();
}

const QString& GlobalChat::GetMessageToSend() const {
  return *send_messages_.begin();
}

void GlobalChat::PopMessageQueue() {
  send_messages_.pop_front();
}

void GlobalChat::Clear() {
  q_text_browser_->clear();
  text_browser_messages_.clear();
}

void GlobalChat::ReceiveNewMessages(const QStringList& messages) {
  text_browser_messages_ += messages;
  while (text_browser_messages_.size() > kMaxChatSize) {
    text_browser_messages_.removeAt(0);
  }

  QString html_style("<style>"
                     "p.global{color: black; margin: 0; padding: 0;}"
                     "p.local{color: green; margin: 0; padding: 0;}"
                     "p.error{color: red; margin: 0; padding: 0;}"
                     "p.command{color: orange; margin: 0; padding: 0;}"
                     "</style>");
  QString global_format = "<p class=\"global\">%1</p>";
  QString local_format = "<p class=\"local\">%1</p>";
  QString error_format = "<p class=\"error\">%1</p>";
  QString command_format = "<p class=\"command\">%1</p>";

  QString text;
  for (int i = 0; i < text_browser_messages_.length(); i++) {
    QString line = text_browser_messages_[i];
    if (line.startsWith(">")) {
      text.append(global_format.arg(line.replace(">",
                                                 "&#62;")));
    } else if (line.startsWith("<")) {
      text.append(local_format.arg(line.replace("<",
                                                "&#60;")));
    } else if (line.startsWith("!")) {
      text.append(error_format.arg(line));
    } else if (line.startsWith("/")) {
      text.append(command_format.arg(line));
    }
  }
  q_text_browser_->setHtml(html_style + text);

  QScrollBar* scroll = q_text_browser_->verticalScrollBar();
  scroll->setValue(scroll->maximum());
}

void GlobalChat::SendMessage() {
  QString message = "> " + text();
  clear();
  if (message == "") {
    return;
  }
  message = message.split(" ", QString::SkipEmptyParts).join(" ");
  ReceiveNewMessages(message.split(" "));
  send_messages_.push_back(message);
}

void GlobalChat::keyPressEvent(QKeyEvent* event) {
  auto* key = static_cast<QKeyEvent*>(event);
  if (key->text() == "\r") {
    SendMessage();
  } else {
    QLineEdit::keyPressEvent(event);
  }
}
