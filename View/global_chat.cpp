#include "global_chat.h"

GlobalChat::GlobalChat(QMainWindow* window)
    : q_text_browser_(new QTextBrowser(window)),
      q_line_edit_(new QLineEdit(window)) {
  QString family = QFontDatabase::applicationFontFamilies(kFontId).at(0);
  QFont font(family);
  font.setFixedPitch(true);

  q_text_browser_->setFont(font);
  q_line_edit_->setFont(font);
  send_button = new MenuButton(
      Size(kTextEditSize.height, kTextEditSize.height), window,
      ":resources/buttons_resources/inc_level_button.png",
      ":resources/buttons_resources/inc_level_button_active.png");
  send_button->SetSecondIconPath(
      ":resources/buttons_resources/send_button.png",
      ":resources/buttons_resources/send_button_active.png");
  auto send_button_click = [this]() {
    SendMessage();
  };

  auto key_press = [this]() {
    SendMessage();
  };

  QObject::connect(send_button, &QPushButton::clicked, send_button_click);
  QObject::connect(q_line_edit_, &QLineEdit::returnPressed, key_press);

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
  q_line_edit_->show();
  brick_button->show();
  send_button->show();
  q_text_browser_->show();

  q_text_browser_->setFocusPolicy(Qt::NoFocus);

}

void GlobalChat::RescaleChat(const SizeHandler& size_handler) {
  Size remove_edit_size =
      Size(0,
           kTextEditSize.height);
  Coordinate text_edit_position = size_handler.GameToWindowCoordinate(
      kBottomLeftPosition - remove_edit_size);

  Size text_edit_size = size_handler.GameToWindowSize(kTextEditSize);
  q_line_edit_->setGeometry(text_edit_position.x, text_edit_position.y,
                            text_edit_size.width * how_right_brick_percent_
                                / 100.0,
                            text_edit_size.height);

  send_button->SetGeometry(
      kBottomLeftPosition +
          Size(kTextEditSize.width * how_right_brick_percent_ / 100,
               -kTextEditSize.height),
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

  auto font_ = q_line_edit_->font();
  font_.setPixelSize(size_handler.GameToWindowLength(kFondSize));
  q_line_edit_->setFont(font_);
  q_text_browser_->setFont(font_);

  brick_button->SetGeometry(
      kBottomLeftPosition +
          Size(kTextEditSize.width * how_right_brick_percent_ / 100,
               -kTextEditSize.height
                   - kTextEditSize.height * 9 / 100 * how_high_brick_percent_),
      size_handler);
}

void GlobalChat::Tick(const SizeHandler& size_handler, int delta_time) {
  if (is_brick_going_right_ && how_right_brick_percent_ < 100) {
    how_right_brick_percent_ +=
        kCloseSpeed * delta_time / constants::kTimeScale;
    how_right_brick_percent_ = std::min(100, how_right_brick_percent_);
    if (how_right_brick_percent_ == 100) {
      is_brick_going_up_ = true;
    }
    RescaleChat(size_handler);
    return;
  }

  if (!is_brick_going_right_ && how_right_brick_percent_ > 0) {
    how_right_brick_percent_ -=
        kCloseSpeed * delta_time / constants::kTimeScale;
    how_right_brick_percent_ = std::max(0, how_right_brick_percent_);
    RescaleChat(size_handler);
    return;
  }

  if (is_brick_going_up_ && how_high_brick_percent_ < 100) {
    how_high_brick_percent_ += kCloseSpeed * delta_time / constants::kTimeScale;
    how_high_brick_percent_ = std::min(100, how_high_brick_percent_);
    RescaleChat(size_handler);
    return;
  }

  if (!is_brick_going_up_ && how_high_brick_percent_ > 0) {
    how_high_brick_percent_ -= kCloseSpeed * delta_time / constants::kTimeScale;
    how_high_brick_percent_ = std::max(0, how_high_brick_percent_);
    if (how_high_brick_percent_ == 0) {
      is_brick_going_right_ = false;
    }
    RescaleChat(size_handler);
    return;
  }

}

void GlobalChat::HideShow() {
  if (is_brick_going_up_ && how_high_brick_percent_ == 100 &&
      is_brick_going_right_ && how_right_brick_percent_ == 100) {
    is_brick_going_up_ = false;
  }
  if (!is_brick_going_up_ && how_high_brick_percent_ == 0 &&
      !is_brick_going_right_ && how_right_brick_percent_ == 0) {
    is_brick_going_right_ = true;
  }
}

void GlobalChat::ChangeStyle() {
  is_game_style_using_ = !is_game_style_using_;
  QString style_sheet;
  if (is_game_style_using_) {
    style_sheet =
        "background-color : rgba(143,144,152,0.88);"
        "border : 1px solid black;"
        "border-radius: 8px;";
  }
  q_line_edit_->setStyleSheet(style_sheet);
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
  for (auto& message : text_browser_messages_) {
    QString line = message;
    if (line.startsWith(">")) {
      text.append(global_format.arg(line.replace(">",
                                                 "&#62;")));
    } else if (line.startsWith("<")) {
      text.append(local_format.arg(line.replace("<",
                                                "&#60;")));
    } else if (line.startsWith("!")) {
      text.append(error_format.arg(line));
    } else {
      text.append(command_format.arg(line));
    }
  }
  q_text_browser_->setHtml(html_style + text);
  QScrollBar* scroll = q_text_browser_->verticalScrollBar();
  scroll->setValue(scroll->maximum());
}

void GlobalChat::SendMessage() {
  QApplication::inputMethod()->commit();
  QString message = q_line_edit_->displayText();
  q_line_edit_->clear();
  if (message.isEmpty()) {
    return;
  }
  message = message.split(" ", QString::SkipEmptyParts).join(" ");
  send_messages_.push_back(message);
}
