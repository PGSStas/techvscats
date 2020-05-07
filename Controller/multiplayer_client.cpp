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
  auto data = Message().DialogMessage("Disconnect", DialogType::kWarning);
  messages_.push_back(Message().DecodeFromBinary(data));
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

bool MultiplayerClient::IsMessagesEmpty() const {
  return messages_.empty();
}

const std::list<Message>& MultiplayerClient::GetMessages() const {
  return messages_;
}

void MultiplayerClient::MessagesClear() {
  messages_.clear();
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

void MultiplayerClient::OnConnect() {
  connect(web_socket_, &QWebSocket::binaryMessageReceived,
          this, &MultiplayerClient::OnMessageReceived);
  is_online_ = true;
  nick_name_ = AutoGenerateNickName();
  web_socket_->sendBinaryMessage(Message().NewConnectionMessage(
      nick_name_));
  is_online_ = true;
  is_ready_ = true;
  auto data = Message().DialogMessage("Connected", DialogType::kWarning);
  messages_.push_back(Message().DecodeFromBinary(data));
}

void MultiplayerClient::OnMessageReceived(const QByteArray& array) {
  Message new_message;
  new_message.DecodeFromBinary(array);
  messages_.push_back(new_message);
}

void MultiplayerClient::onClose() {
  qDebug() << "server killed you";
  is_online_ = false;
  is_ready_ = true;
}

QString MultiplayerClient::AutoGenerateNickName() const {
  return first_name[random_generator_() % first_name.size()] + "_"
      + sur_name[random_generator_() % sur_name.size()];
}
