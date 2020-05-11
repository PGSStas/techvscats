#include "multiplayer_client.h"

std::mt19937 MultiplayerClient::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

MultiplayerClient::MultiplayerClient() : QObject(nullptr) {}

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
  CreateVisibleMessage(MessageType::kDisconnect);
}

void MultiplayerClient::SendMessageToServer(const Message& message) const {
  server_web_socket_->sendBinaryMessage(Message::CodeToBinary(message));
}

void MultiplayerClient::Register(const QString& nick_name) {
  nick_name_ = nick_name;
  if (is_online_) {
    SendMessageToServer(Message(MessageType::kNewConnection, {nick_name_}));
  }
}

void MultiplayerClient::EnterRoom(int level_id) {
  SendMessageToServer(Message(
      MessageType::kEnterRoom, {QString::number(level_id)}));
  has_permission_to_start_round = false;
}

void MultiplayerClient::RoundCompleted(int base_current_health,
                                       int casted_game_process) {
  if (!is_end_round_message_sent_) {
    SendMessageToServer(Message(
        MessageType::kRoundCompletedByPlayer, {
            QString::number(base_current_health),
            QString::number(casted_game_process)}));

    is_end_round_message_sent_ = true;
  }
}

void MultiplayerClient::LeaveRoom() {
  CreateVisibleMessage(MessageType::kLeaveRoom);
  SendMessageToServer(MessageType::kLeaveRoom);
}

bool MultiplayerClient::IsReceivedMessageEmpty() const {
  return received_message_.empty();
}

const std::list<Message>& MultiplayerClient::GetReceivedMessage() const {
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

void MultiplayerClient::NewClientMessage(const QString& message) {
  if (message[0] == "/") {
    CreateVisibleMessage(Message(MessageType::kChatUpdate, {message}));
    ProcessCommand(message);
    return;
  }
  if (!is_online_) {
    CreateVisibleMessage(MessageType::kChatOffline);
    return;
  }

  if (!IsRegistered()) {
    CreateVisibleMessage(MessageType::kNameNullMessage);
    return;
  }
  if (is_online_) {
    SendMessageToServer(Message(MessageType::kGlobalChat, {message}));
    return;
  }
}

void MultiplayerClient::ProcessCommand(QString command) {
  command.remove(0, 1);
  QStringList words = command.split(" ");
  if (words[0] == "register" && words.size() == 2) {
    if (!IsRegistered()) {
      Register(words[1]);
      CreateVisibleMessage(MessageType::kOk);
      return;
    } else {
      CreateVisibleMessage(Message(MessageType::kYourNickNameIs,
                                   {nick_name_}));
      return;
    }
  }
  if (words[0] == "autoregister" && words.size() == 1) {
    if (!IsRegistered()) {
      Register(AutoGenerateNickName());
      CreateVisibleMessage(Message(MessageType::kYourNickNameIs,
                                   {nick_name_}));
      return;
    } else {
      CreateVisibleMessage(Message(MessageType::kYourNickNameIs,
                                   {nick_name_}));
      return;
    }
  }
  if (words[0] == "gold" && words.size() == 2) {
    if (words[1].toInt()) {
      received_message_.push_back(
          Message().SetCommandMessage(words[1],
                                      CommandType::kGoldChange));

      CreateVisibleMessage(MessageType::kMoreGold);
      return;
    } else {
      CreateVisibleMessage(MessageType::kGoldError);
      return;
    }
  }
  if (words[0] == "iddqd") {
    received_message_.push_back(
        Message().SetCommandMessage(words[0],
                                    CommandType::kHealthGrow));
    CreateVisibleMessage(MessageType::kInfinityHealth);
    return;
  }
  CreateVisibleMessage(MessageType::kErrorCommand);
}

void MultiplayerClient::CreateVisibleMessage(const Message& message) {
  Message message_to_send;
  int point = static_cast<int>(message.GetType());
  auto& arguments = message.GetArguments();
  QString text_message = data_base_[point].message;
  for (int i = 0; i < arguments.size(); i++) {
    text_message = text_message.arg(arguments[i]);
  }
  message_to_send.SetVisibleMessage(
      text_message, data_base_[point].type);

  switch (message.GetType()) {
    case MessageType::kStartRound: {
      SetPermissionToStartRound(true);
      break;
    }
    default:break;
  }
  received_message_.push_back(message_to_send);
}

void MultiplayerClient::OnConnect() {
  connect(server_web_socket_, &QWebSocket::binaryMessageReceived,
          this, &MultiplayerClient::OnMessageReceived);
  is_online_ = true;
  is_online_ = true;
  has_permission_to_start_round = true;
  CreateVisibleMessage(MessageType::kConnect);

  if (!IsRegistered()) {
    CreateVisibleMessage(MessageType::kHintRegistration1);
    CreateVisibleMessage(MessageType::kHintRegistration2);
  } else {
    Register(nick_name_);
    CreateVisibleMessage(
        Message(MessageType::kYourNickNameIs, {nick_name_}));
  }
}

void MultiplayerClient::OnMessageReceived(const QByteArray& array) {
  Message new_message;
  new_message.DecodeFromBinary(array);
  CreateVisibleMessage(new_message);
}

void MultiplayerClient::onClose() {
  CreateVisibleMessage(MessageType::kServerClosed);
  has_permission_to_start_round = true;
  is_online_ = false;
}

QString MultiplayerClient::AutoGenerateNickName() const {
  return first_name[random_generator_() % first_name.size()] + "_"
      + sur_name[random_generator_() % sur_name.size()];
}

void MultiplayerClient::SetData(QString path) {
  int enum_size = 40;
  data_base_.resize(enum_size);
  data_base_[0] = {"%1", VisibleType::kChat};
  data_base_[1] = {"! %1 _DEAD_", VisibleType::kChat};
  data_base_[2] = {"! Player %1 joined the room.", VisibleType::kChat};
  data_base_[3] =
      {"! Player %1 finish the room with %2 HP.", VisibleType::kChat};
  data_base_[4] = {"< %1 left game... ", VisibleType::kChat};
  data_base_[5] = {"< %1 WIN THE GAME Wow! With %2 HP.", VisibleType::kChat};
  data_base_[6] = {"< Room starts in %1 seconds.", VisibleType::kChat};
  data_base_[7] = {"< Round starts in %1 seconds.", VisibleType::kChat};
  data_base_[8] = {"< Round starts!! ", VisibleType::kChat};
  data_base_[9] = {"< Connected", VisibleType::kChat};
  data_base_[10] = {"! Your chat is offline", VisibleType::kChat};
  data_base_[11] = {"! gold error", VisibleType::kChat};

  data_base_[12] = {"< Disconnect", VisibleType::kChat};
  data_base_[13] = {"! command error", VisibleType::kChat};
  data_base_[14] = {"< Game End", VisibleType::kChat};
  data_base_[15] = {"! Your Name is null", VisibleType::kChat};
  data_base_[15] = {"< Enter /register <NickName>.", VisibleType::kChat};
  data_base_[16] = {"< Or enter /autoregister", VisibleType::kChat};

  data_base_[18] = {"< ❤_INFINITY HEALTH_❤", VisibleType::kChat};
  data_base_[19] = {"< $$$ MOOOREE GOOLLDLDLDLD $$$", VisibleType::kChat};
  data_base_[20] = {"< Ok.", VisibleType::kChat};
  data_base_[21] = {"< Server closed", VisibleType::kChat};
  data_base_[22] = {"< Your nick name is : %1", VisibleType::kChat};
  data_base_[23] = {"! You created the room.", VisibleType::kChat};
  data_base_[24] = {"! You left the room.", VisibleType::kChat};

}

