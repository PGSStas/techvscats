#include "multiplayer_client.h"

std::mt19937 MultiplayerClient::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

MultiplayerClient::~MultiplayerClient() {
  Disconnect();
}

void MultiplayerClient::Connect() {
  web_socket_ = new QWebSocket();
  connect(web_socket_, &QWebSocket::connected,
          this, &MultiplayerClient::OnConnect);
  connect(web_socket_, &QWebSocket::disconnected,
          this, &MultiplayerClient::onClose);
  web_socket_->open(QUrl(address));
}

void MultiplayerClient::Disconnect() {
  web_socket_->close();
  web_socket_->deleteLater();
  auto message = Message().SetDialogMessage("< Disconnect", DialogType::kChat);
  received_messages_.push_back(message);
}

void MultiplayerClient::Register(QString nick_name) {
  if (nick_name == "auto") {
    nick_name = AutoGenerateNickName();
  }else{
    nick_name_ = nick_name;
  }

  web_socket_->sendBinaryMessage(Message().NewConnectionMessage(
      nick_name_));
}

void MultiplayerClient::EnterRoom(int level_id) {
  web_socket_->sendBinaryMessage(Message().EnterRoomMessage(level_id));
  is_ready_ = false;
}

void MultiplayerClient::RoundCompleted(int base_current_health) {
  if (!is_send_) {
    web_socket_->sendBinaryMessage(Message().RoundCompletedMessage(
        base_current_health));
    is_send_ = true;
  }
}

void MultiplayerClient::LeaveRoom() {
  web_socket_->sendBinaryMessage(Message().LeaveRoomMessage());
}

bool MultiplayerClient::IsReceivedMessagesEmpty() const {
  return received_messages_.empty();
}

const std::list<Message>& MultiplayerClient::GetReceivedMessages() const {
  return received_messages_;
}

void MultiplayerClient::ReceivedMessagesClear() {
  received_messages_.clear();
}

void MultiplayerClient::SetIsReady(bool new_is_ready) {
  if (!is_ready_ && new_is_ready) {
    is_send_ = false;
  }
  is_ready_ = new_is_ready;
}

bool MultiplayerClient::IsOnline() const {
  return is_online_;
}
bool MultiplayerClient::IsReady() const {
  return is_ready_;
}

void MultiplayerClient::NewClientMessage(const QString& messages) {
  if (!is_online_) {
    auto message = Message().SetDialogMessage("! Your chat is offline",
                                              DialogType::kChat);
    received_messages_.push_back(message);
    return;
  }
  if (messages[0] == "/") {
    auto message = Message().SetDialogMessage(messages,
                                              DialogType::kChat);
    received_messages_.push_back(message);
    ProcessCommand(messages);
    return;
  }
  if (nick_name_ == "") {
    auto message = Message().SetDialogMessage("! Your Name is null",
                                              DialogType::kChat);
    received_messages_.push_back(message);
    return;
  }
  if (is_online_) {
    web_socket_->sendBinaryMessage(Message().GlobalChatMessage(messages));
    return;
  }
}

void MultiplayerClient::ProcessCommand(QString command) {
  QString command_clear = command.remove(0, 1);
  QStringList words = command_clear.split(" ");
  auto message = Message().SetDialogMessage("! command error",
                                            DialogType::kChat);
  if (words[0] == "register") {
    if (words.size() == 2) {
      Register(words[1]);
      message = Message().SetDialogMessage("< Ok",
                                           DialogType::kChat);
    }
  }

  received_messages_.push_back(message);
}

void MultiplayerClient::OnConnect() {
  connect(web_socket_, &QWebSocket::binaryMessageReceived,
          this, &MultiplayerClient::OnMessageReceived);
  is_online_ = true;
  nick_name_ = "";
  is_online_ = true;
  is_ready_ = true;
  auto message = Message().SetDialogMessage(
      "< Connected. Enter /register <NickName>. ",
      DialogType::kChat);

  received_messages_.push_back(message);
  message = Message().SetDialogMessage(
      "< Or enter /register auto",
      DialogType::kChat);
  received_messages_.push_back(message);
}

void MultiplayerClient::OnMessageReceived(const QByteArray& array) {
  Message new_message;
  new_message.DecodeFromBinary(array);
  received_messages_.push_back(new_message);
}

void MultiplayerClient::onClose() {
  is_online_ = false;
  is_ready_ = true;
  auto message =
      Message().SetDialogMessage("< Server closed", DialogType::kChat);
  received_messages_.push_back(message);
}

QString MultiplayerClient::AutoGenerateNickName() const {
  return first_name[random_generator_() % first_name.size()] + "_"
      + sur_name[random_generator_() % sur_name.size()];
}
