#include "multiplayer_client.h"

std::mt19937 MultiplayerClient::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

MultiplayerClient::~MultiplayerClient() {
  Disconnect();
}

void MultiplayerClient::Connect() {
  server_web_socket_ = new QWebSocket();
  connect(server_web_socket_, &QWebSocket::connected,
          this, &MultiplayerClient::OnConnect);
  connect(server_web_socket_, &QWebSocket::disconnected,
          this, &MultiplayerClient::onClose);
  server_web_socket_->open(QUrl(address));
}

void MultiplayerClient::Disconnect() {
  server_web_socket_->close();
  server_web_socket_->deleteLater();
  auto message = Message().SetDialogMessage("< Disconnect", DialogType::kChat);
  received_message_.push_back(message);
}

void MultiplayerClient::Register(QString nick_name) {
  if (nick_name == "auto") {
    nick_name_ = AutoGenerateNickName();
  } else {
    nick_name_ = nick_name;
  }
  if (is_online_) {
    server_web_socket_->sendBinaryMessage(Message::NewConnectionMessage(
        nick_name_));
  }
}

void MultiplayerClient::EnterRoom(int level_id) {
  server_web_socket_->sendBinaryMessage(Message::EnterRoomMessage(level_id));
  has_permission_to_start_round = false;
}

void MultiplayerClient::RoundCompleted(int base_current_health, int casted_game_process) {
  if (!is_end_round_message_sent_) {
    server_web_socket_->sendBinaryMessage(Message::RoundCompletedMessage(
        base_current_health,casted_game_process));
    is_end_round_message_sent_ = true;
  }
}

void MultiplayerClient::LeaveRoom() {
  server_web_socket_->sendBinaryMessage(Message().LeaveRoomMessage());
}

bool MultiplayerClient::IsReceivedMessageEmpty() const {
  return received_message_.empty();
}

const std::list<Message>& MultiplayerClient::GetReceivedMessages() const {
  return received_message_;
}

void MultiplayerClient::ClearReceivedMessage() {
  received_message_.clear();
}

bool MultiplayerClient::IsRegistered() const {
  return !nick_name_.isEmpty();
}

void MultiplayerClient::SetPermissionToStartRound(bool permission) {
  if (!has_permission_to_start_round && permission) {
    is_end_round_message_sent_ = false;
  }
  has_permission_to_start_round = permission;
}

bool MultiplayerClient::IsOnline() const {
  return is_online_;
}
bool MultiplayerClient::HasPermissionToStartRound() const {
  return has_permission_to_start_round;
}

void MultiplayerClient::NewClientMessage(const QString& messages) {
  if (messages[0] == "/") {
    auto message = Message().SetDialogMessage(messages,
                                              DialogType::kChat);
    received_message_.push_back(message);
    ProcessCommand(messages);
    return;
  }
  if (!is_online_) {
    auto message = Message().SetDialogMessage("! Your chat is offline",
                                              DialogType::kChat);
    received_message_.push_back(message);
    return;
  }

  if (!IsRegistered()) {
    auto message = Message().SetDialogMessage("! Your Name is null",
                                              DialogType::kChat);
    received_message_.push_back(message);
    return;
  }
  if (is_online_) {
    server_web_socket_->sendBinaryMessage(Message::GlobalChatMessage(messages));
    return;
  }
}

void MultiplayerClient::ProcessCommand(QString command) {
  QString command_clear = command.remove(0, 1);
  QStringList words = command_clear.split(" ");
  auto message = Message().SetDialogMessage("! command error",
                                            DialogType::kChat);
  if (words[0] == "register" && words.size() == 2) {
    if (!IsRegistered()) {
      Register(words[1]);
      message = Message().SetDialogMessage("< Ok",
                                           DialogType::kChat);
    } else {
      message = Message().SetDialogMessage("! your nick name is" + nick_name_,
                                           DialogType::kChat);
    }
  }

  if (words[0] == "gold" && words.size() == 2) {
    if (words[1].toInt()) {
      received_message_.push_back(
          Message().SetCommandMessage(words[1],
                                      ControllerCommandType::kGoldChange));
      message = Message().SetDialogMessage("< $$$ MOOOREE GOOLLDLDLDLD $$$",
                                           DialogType::kChat);
    } else {
      message = Message().SetDialogMessage("! gold error",
                                           DialogType::kChat);
    }
  }
  if (words[0] == "iddqd") {
    received_message_.push_back(
        Message().SetCommandMessage(words[0],
                                    ControllerCommandType::kHealthGrow));
    message = Message().SetDialogMessage("<❤_INFINITY HEALTH_❤",
                                         DialogType::kChat);
  }
  received_message_.push_back(message);
}

void MultiplayerClient::OnConnect() {
  connect(server_web_socket_, &QWebSocket::binaryMessageReceived,
          this, &MultiplayerClient::OnMessageReceived);
  is_online_ = true;
  is_online_ = true;
  has_permission_to_start_round = true;
  auto message = Message().SetDialogMessage(
      "< Connected.",
      DialogType::kChat);

  received_message_.push_back(message);
  if (!IsRegistered()) {
    message = Message().SetDialogMessage(
        "< Enter /register <NickName>.",
        DialogType::kChat);
    received_message_.push_back(message);
    message = Message().SetDialogMessage(
        "< Or enter /register auto",
        DialogType::kChat);
    received_message_.push_back(message);
  } else {
    message = Message().SetDialogMessage(
        "< Your name is " + nick_name_,
        DialogType::kChat);
    received_message_.push_back(message);
    Register(nick_name_);
  }
}

void MultiplayerClient::OnMessageReceived(const QByteArray& array) {
  Message new_message;
  new_message.DecodeFromBinary(array);
  received_message_.push_back(new_message);
}

void MultiplayerClient::onClose() {
  is_online_ = false;
  has_permission_to_start_round = true;
  auto message =
      Message().SetDialogMessage("< Server closed", DialogType::kChat);
  received_message_.push_back(message);
}

QString MultiplayerClient::AutoGenerateNickName() const {
  return first_name[random_generator_() % first_name.size()] + "_"
      + sur_name[random_generator_() % sur_name.size()];
}
