#include "global_chat.h"

GlobalChat::GlobalChat(QMainWindow* window) {
  QString family = QFontDatabase::applicationFontFamilies(kFontId).at(0);
  QFont font(family);
  font.setFixedPitch(true);

  q_text_browser_ = new QTextBrowser(window);
  q_text_browser_->setFont(font);

  q_text_edit_ = new QTextEdit(window);
  q_text_edit_->setFont(font);

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

  close_open_button = new MenuButton(
      Size(kTextEditSize.height, kTextEditSize.height), window,
      ":resources/buttons_resources/dec_level_button.png",
      ":resources/buttons_resources/dec_level_button_active.png");
  close_open_button->SetSecondIconPath(
      ":resources/buttons_resources/pause_button.png",
      ":resources/buttons_resources/pause_button_active.png");

  auto close_open_button_click = [this]() {
    HideShow();
  };

  QObject::connect(close_open_button,
                   &QPushButton::clicked,
                   close_open_button_click);

  ChangeStyle();
}

void GlobalChat::RescaleChat(const SizeHandler& size_handler) {
  Coordinate text_edit_position =
      size_handler.GameToWindowCoordinate(
          kBottomLeftPosition
              - Size(-kTextEditSize.width * (1 - up_percent_ / 100.0),
                     kTextEditSize.height));
  Size text_edit_size = size_handler.GameToWindowSize(kTextEditSize);
  q_text_edit_->setGeometry(text_edit_position.x, text_edit_position.y,
                            text_edit_size.width * up_percent_ / 100.0,
                            text_edit_size.height);

  send_button->SetGeometry(
      kBottomLeftPosition + Size(kTextEditSize.width, -kTextEditSize.height),
      size_handler);

  Coordinate text_browser_position =
      size_handler.GameToWindowCoordinate(
          {kBottomLeftPosition.x, kBottomLeftPosition.y
              - kTextEditSize.height * 10
              + kTextEditSize.height * 9 * (1 - up_percent_ / 100.0)});
  Size text_browser_size = size_handler.GameToWindowSize(
      {kTextEditSize.width + kTextEditSize.height,
       kTextEditSize.height * 9 * up_percent_ / 100});

  q_text_browser_->setGeometry(text_browser_position.x,
                               text_browser_position.y,
                               text_browser_size.width,
                               text_browser_size.height);

  auto font = q_text_edit_->font();
  font.setPixelSize(size_handler.GameToWindowLength(kFondSize));
  q_text_edit_->setFont(font);
  q_text_browser_->setFont(font);

  close_open_button->SetGeometry(
      kBottomLeftPosition + Size(kTextEditSize.width, -kTextEditSize.height -
          kTextEditSize.height * 9 / 100 * up_percent_), size_handler);
}

void GlobalChat::Tick(const SizeHandler& size_handler, int delta_time) {
  if (is_go_up_ && up_percent_ < 100) {
    up_percent_ += kCloseSpeed * delta_time / constants::kTimeScale;
    up_percent_ = std::min(100, up_percent_);
    RescaleChat(size_handler);
  }

  if (!is_go_up_ && up_percent_ > 0) {
    up_percent_ -= kCloseSpeed * delta_time / constants::kTimeScale;
    up_percent_ = std::max(0, up_percent_);
    RescaleChat(size_handler);
  }
}

void GlobalChat::HideShow() {
  if (is_go_up_ && up_percent_ == 100) {
    is_go_up_ = false;
  }
  if (!is_go_up_ && up_percent_ == 0) {
    is_go_up_ = true;
  }
}

void GlobalChat::ChangeStyle() {
  game_style_ = !game_style_;
  QString style_sheet;
  if (game_style_) {
    style_sheet = " background-color : rgba(190,192,213,0.89);";
  }
  q_text_edit_->setStyleSheet(style_sheet);
  q_text_browser_->setStyleSheet(style_sheet);
  close_open_button->EnableSecondIcon(game_style_);
  send_button->EnableSecondIcon(game_style_);
}

bool GlobalChat::IsSendMessagesEmpty() const {
  return send_messages_.isEmpty();
}

const QString& GlobalChat::GetMessageToSend() const {
  return *send_messages_.begin();
}

void GlobalChat::PopMessageToSend() {
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
  QString message = q_text_edit_->toPlainText();
  q_text_edit_->clear();
  if (message == "") {
    return;
  }
  message = message.split(" ", QString::SkipEmptyParts).join(" ");
  send_messages_.push_back(message);
}
