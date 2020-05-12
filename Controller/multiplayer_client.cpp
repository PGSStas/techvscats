#include "multiplayer_client.h"

std::mt19937 MultiplayerClient::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

MultiplayerClient::MultiplayerClient() : QObject(nullptr) {}

MultiplayerClient::~MultiplayerClient() {
  Disconnect();
}

void MultiplayerClient::Tick(int current_time) {
  if (current_time_ == 0) {
    current_time_ = current_time;
    return;
  }
  wait_time_ -= current_time - current_time_;
  if (wait_time_ < 0 && is_trying_to_connect_) {
    is_trying_to_connect_ = false;
    CreateVisibleMessage(MessageType::kServerIsUnavailable);
  }
  current_time_ = current_time;

}

void MultiplayerClient::Connect() {
  is_trying_to_connect_ = true;
  wait_time_ = kWaitTime;
  server_web_socket_ = new QWebSocket();
  connect(server_web_socket_, &QWebSocket::connected,
          this, &MultiplayerClient::OnConnect);
  connect(server_web_socket_, &QWebSocket::disconnected,
          this, &MultiplayerClient::onClose);
  server_web_socket_->open(QUrl(address));
}

void MultiplayerClient::Disconnect() {
  is_normal_close_ = true;
  server_web_socket_->close();
  server_web_socket_->deleteLater();
  is_trying_to_connect_ = false;
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

const std::list <Message>& MultiplayerClient::GetReceivedMessage() const {
  return received_message_;
}

void MultiplayerClient::ClearReceivedMessage() {
  received_message_.clear();
}

bool MultiplayerClient::IsRegistered() const {
  return !nick_name_.isEmpty();
}

void MultiplayerClient::ChangePermissionToStartRound(bool permission) {
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
  if (message.size() > kMaxMessageSize) {
    CreateVisibleMessage(MessageType::kToLongMessage);
    return;
  }
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
      ChangePermissionToStartRound(true);
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
  is_normal_close_ = false;
  is_trying_to_connect_ = false;
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
  if (!is_normal_close_) {
    CreateVisibleMessage(MessageType::kServerClosed);
  }
  is_normal_close_ = false;
  has_permission_to_start_round = true;
  is_online_ = false;
}

QString MultiplayerClient::AutoGenerateNickName() const {
  return first_name[random_generator_() % first_name.size()] + "_"
      + sur_name[random_generator_() % sur_name.size()];
}

void MultiplayerClient::LoadDatabase(const QString& path) {
  QFile description_file(path);
  if (!description_file.open(QFile::ReadOnly)) {
    qDebug() << "ERROR! Missing description file";
    return;
  }
  QJsonArray description_array = QJsonDocument::fromJson(
      description_file.readAll()).array();
  int enum_size = 40;
  data_base_.resize(enum_size);
  for (int i = 0; i < description_array.count(); i++) {
    auto info = description_array[i].toObject();
    data_base_[i] = {
        info["message"].toString(),
        static_cast<VisibleType>(info["type"].toInt())
    };
  }
}
