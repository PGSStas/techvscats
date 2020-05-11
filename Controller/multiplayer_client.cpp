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
  CreateControllerMessage(Message(MessageType::kDisconnect));
}

void MultiplayerClient::SendMessageToServer(const Message& message) {
  server_web_socket_->sendBinaryMessage(Message::CodeToBinary(message));
}

void MultiplayerClient::Register(QString nick_name) {
  if (nick_name == "auto") {
    nick_name_ = AutoGenerateNickName();
  } else {
    nick_name_ = nick_name;
  }
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
  CreateControllerMessage(MessageType::kLeaveRoom);
  SendMessageToServer(MessageType::kLeaveRoom);
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
    CreateControllerMessage(Message(MessageType::kPlayerMessage, {messages}));
    ProcessCommand(messages);
    return;
  }
  if (!is_online_) {
    CreateControllerMessage(Message(MessageType::kChatOffline, {messages}));
    return;
  }

  if (!IsRegistered()) {
    CreateControllerMessage(Message(MessageType::kNameNullMessage, {messages}));
    return;
  }
  if (is_online_) {
    SendMessageToServer(Message(MessageType::kGlobalChat, {messages}));
    return;
  }
}

void MultiplayerClient::CreateControllerMessage(const Message& message) {
  Message message_to_send;
  switch (message.GetType()) {
    case MessageType::kConnect: {
      message_to_send.SetControllerMessage("< Connected", DialogType::kChat);
      break;
    }
    case MessageType::kDisconnect: {
      message_to_send.SetControllerMessage("< Disconnect", DialogType::kChat);
      break;
    }
    case MessageType::kLeaveRoom: {
      message_to_send.SetControllerMessage("! You left the room.",
                                           DialogType::kChat);
      break;
    }
    case MessageType::kPlayerMessage: {
      message_to_send.SetControllerMessage(message.GetArgument(0),
                                           DialogType::kChat);
      break;
    }
    case MessageType::kChatOffline: {
      message_to_send.SetControllerMessage("! Your chat is offline",
                                           DialogType::kChat);
      break;
    }
    case MessageType::kNameNullMessage: {
      message_to_send.SetControllerMessage("! Your Name is null",
                                           DialogType::kChat);
      break;
    }
    case MessageType::kErrorCommand: {
      message_to_send.SetControllerMessage("! command error",
                                           DialogType::kChat);
      break;
    }
    case MessageType::kOk: {
      message_to_send.SetControllerMessage("< Ok", DialogType::kChat);
      break;
    }
    case MessageType::kYourNickNameIs: {
      message_to_send.SetControllerMessage(
          "< Your nick name is : " + message.GetArgument(0),
          DialogType::kChat);

      break;
    }
    case MessageType::kMoreGold: {
      message_to_send.SetControllerMessage("< $$$ MOOOREE GOOLLDLDLDLD $$$",
                                           DialogType::kChat);
      break;
    }
    case MessageType::kHintRegistration1: {
      message_to_send.SetControllerMessage("< Enter /register <NickName>.",
                                           DialogType::kChat);
      break;
    }
    case MessageType::kHintRegistration2: {
      message_to_send.SetControllerMessage("< Or enter /register auto",
                                           DialogType::kChat);
      break;
    }
    case MessageType::kGoldError: {
      message_to_send.SetControllerMessage("! gold error", DialogType::kChat);
      break;
    }
    case MessageType::kInfinityHealth: {
      message_to_send.SetControllerMessage("< ❤_INFINITY HEALTH_❤",
                                           DialogType::kChat);
      break;
    }
    case MessageType::kServerClosed: {
      message_to_send.SetControllerMessage("< Server closed",
                                           DialogType::kChat);
      break;
    }
    case MessageType::kYouCreatedRoom: {
      message_to_send.SetControllerMessage("! You created the room.",
                                           DialogType::kChat);
      break;
    }
    case MessageType::kChatUpdate: {
      message_to_send.SetControllerMessage(message.GetArgument(0),
                                           DialogType::kChat);
      break;
    }
    case MessageType::kRoomStartsIn: {
      message_to_send.SetControllerMessage(
          "< Room starts in " + message.GetArgument(0) + " seconds.",
          DialogType::kChat);
      break;
    }
    case MessageType::kRoundStartsIn: {
      message_to_send.SetControllerMessage(
          "< Room starts in " + message.GetArgument(0) + " seconds.",
          DialogType::kChat);
      break;
    }
    case MessageType::kNickNameJoinedTheRoom: {
      message_to_send.SetControllerMessage(
          "! Player " + message.GetArgument(0) + " joined the room.",
          DialogType::kChat);
      break;
    }
    case MessageType::kNickNameDead: {
      message_to_send.SetControllerMessage(
          "! " + message.GetArgument(0) + " _DEAD_",
          DialogType::kChat);
      break;
    }
    case MessageType::kNickNameWinWithHp: {
      message_to_send.SetControllerMessage(
          "< " + message.GetArgument(0) + " WIN THE GAME Wow! With " +
              message.GetArgument(1) + "HP.",
          DialogType::kChat);
      break;
    }
    case MessageType::kGameEnd: {
      message_to_send.SetControllerMessage("< Game End.", DialogType::kChat);
      break;
    }
    case MessageType::kNickNameFinishRoundWithHp: {
      message_to_send.SetControllerMessage(
          "< " + message.GetArgument(0) + " ended round! With " +
              message.GetArgument(1) + "HP.",
          DialogType::kChat);
      break;
    }
    case MessageType::kNickNameLeft: {
      message_to_send.SetControllerMessage(
          "< " + message.GetArgument(0) + " left game... ",
          DialogType::kChat);
      break;
    }
    case MessageType::kStartRound: {
      SetPermissionToStartRound(true);
      message_to_send.SetControllerMessage(
          "< Round starts!! ",
          DialogType::kChat);
      break;
    }
  }
  received_message_.push_back(message_to_send);
}

void MultiplayerClient::ProcessCommand(QString command) {
  QString command_clear = command.remove(0, 1);
  QStringList words = command_clear.split(" ");
  if (words[0] == "register" && words.size() == 2) {
    if (!IsRegistered()) {
      Register(words[1]);
      CreateControllerMessage(Message(MessageType::kOk));
      return;
    } else {
      CreateControllerMessage(Message(MessageType::kYourNickNameIs,
                                      {nick_name_}));
      return;
    }
  }

  if (words[0] == "gold" && words.size() == 2) {
    if (words[1].toInt()) {
      received_message_.push_back(
          Message().SetCommandMessage(words[1],
                                      ControllerCommandType::kGoldChange));

      CreateControllerMessage(Message(MessageType::kMoreGold));
      return;
    } else {
      CreateControllerMessage(Message(MessageType::kGoldError));
      return;
    }
  }
  if (words[0] == "iddqd") {
    received_message_.push_back(
        Message().SetCommandMessage(words[0],
                                    ControllerCommandType::kHealthGrow));
    CreateControllerMessage(Message(MessageType::kInfinityHealth));
    return;
  }
  CreateControllerMessage(Message(MessageType::kErrorCommand));

}

void MultiplayerClient::OnConnect() {
  connect(server_web_socket_, &QWebSocket::binaryMessageReceived,
          this, &MultiplayerClient::OnMessageReceived);
  is_online_ = true;
  is_online_ = true;
  has_permission_to_start_round = true;
  CreateControllerMessage(Message(MessageType::kConnect));

  if (!IsRegistered()) {
    CreateControllerMessage(Message(MessageType::kHintRegistration1));
    CreateControllerMessage(Message(MessageType::kHintRegistration2));
  } else {
    Register(nick_name_);
    CreateControllerMessage(
        Message(MessageType::kYourNickNameIs, {nick_name_}));
  }
}

void MultiplayerClient::OnMessageReceived(const QByteArray& array) {
  Message new_message;
  new_message.DecodeFromBinary(array);
  CreateControllerMessage(new_message);
}

void MultiplayerClient::onClose() {
  is_online_ = false;
  has_permission_to_start_round = true;
}

QString MultiplayerClient::AutoGenerateNickName() const {
  return first_name[random_generator_() % first_name.size()] + "_"
      + sur_name[random_generator_() % sur_name.size()];
}
