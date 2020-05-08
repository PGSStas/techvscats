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

  auto send_button_click = [this]() {
    SendMessage();
  };

  QObject::connect(send_button, &QPushButton::clicked, send_button_click);

  close_open_button = new MenuButton(
      Size(kTextEditSize.height, kTextEditSize.height), window,
      ":resources/buttons_resources/dec_level_button.png",
      ":resources/buttons_resources/dec_level_button_active.png");

  auto close_open_button_click = [this]() {
    HideShow();
  };

  QObject::connect(close_open_button,
                   &QPushButton::clicked,
                   close_open_button_click);
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

void GlobalChat::ReceiveNewMessages(const QStringList& messages, QColor color) {
  text_browser_messages_ += messages;
  while (text_browser_messages_.size() > 3) {
    text_browser_messages_.removeAt(0);
  }
  q_text_browser_->setText(text_browser_messages_.join("\n"));
  QScrollBar* scroll = q_text_browser_->verticalScrollBar();
  scroll->setValue(scroll->maximum());
}

void GlobalChat::SendMessage() {
  QString message = q_text_edit_->toPlainText();
  q_text_edit_->clear();
  send_messages_.push_back(message);
}

void GlobalChat::HideShow() {
  if (is_go_up_ && up_percent_ == 100) {
    is_go_up_ = false;
  }
  if (!is_go_up_ && up_percent_ == 0) {
    is_go_up_ = true;
  }
}
