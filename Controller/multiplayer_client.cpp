#include "multiplayer_client.h"

std::mt19937 MultiplayerClient::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

MultiplayerClient::MultiplayerClient() : QObject(nullptr) {
  QSettings settings;
  nick_name_ = settings.value("nick_name", "").toString();
}

MultiplayerClient::~MultiplayerClient() {
  if (is_online_) {
    Disconnect();
  }
}

void MultiplayerClient::Tick(int current_time) {
  if (current_time_ == 0) {
    current_time_ = current_time;
    return;
  }
  wait_time_ -= current_time - current_time_;
  if (wait_time_ < 0 && is_trying_to_connect_) {
    is_trying_to_connect_ = false;
    CreateVisibleMessage(Message(MessageType::kServerIsUnavailable));
  }
  current_time_ = current_time;
}

void MultiplayerClient::LoadDatabase() {
  QSettings settings(constants::kCompanyName, constants::kApplicationName);
  QString locale = settings.value("locale", "en_US").toString();

  QFile description_file(":resources/database/server_" + locale + ".json");

  if (!description_file.open(QFile::ReadOnly)) {
    qDebug() << "ERROR! Missing description file";
    return;
  }
  QJsonArray description_array = QJsonDocument::fromJson(
      description_file.readAll()).array();
  int enum_size = static_cast<int>(MessageType::kLastTranslatable);
  database_.resize(enum_size);
  for (int i = 0; i < description_array.count(); i++) {
    auto info = description_array[i].toObject();
    database_[i] = {
        info["message"].toString(),
        static_cast<VisibleType>(info["type"].toInt())
    };
  }
}

void MultiplayerClient::Connect() {
  is_trying_to_connect_ = true;
  wait_time_ = kWaitTime_;
  server_web_socket_ = new QWebSocket();
  connect(server_web_socket_, &QWebSocket::connected,
          this, &MultiplayerClient::OnConnect);
  connect(server_web_socket_, &QWebSocket::disconnected,
          this, &MultiplayerClient::onClose);
  server_web_socket_->open(QUrl(address_));
}

void MultiplayerClient::Disconnect() {
  server_web_socket_->close();
  server_web_socket_->deleteLater();
  is_trying_to_connect_ = false;
  CreateVisibleMessage(Message(MessageType::kDisconnect));
}

void MultiplayerClient::SendMessageToServer(const Message& message) const {
  server_web_socket_->sendBinaryMessage(Message::CodeToBinary(message));
}

void MultiplayerClient::Register(const QString& nick_name) {
  nick_name_ = nick_name;
  QSettings settings;
  settings.setValue("nick_name", nick_name);
  if (is_online_) {
    SendMessageToServer(Message(MessageType::kNewConnection, {nick_name_}));
  }
}

void MultiplayerClient::EnterRoom(int level_id) {
  SendMessageToServer(Message(
      MessageType::kEnterRoom, {QString::number(level_id)}));
  has_permission_to_start_round_ = false;
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
  CreateVisibleMessage(Message(MessageType::kLeaveRoom));
  SendMessageToServer(Message(MessageType::kLeaveRoom));
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

void MultiplayerClient::ChangePermissionToStartRound(bool permission) {
  if (!has_permission_to_start_round_ && permission) {
    is_end_round_message_sent_ = false;
  }
  has_permission_to_start_round_ = permission;
}

bool MultiplayerClient::IsOnline() const {
  return is_online_;
}

bool MultiplayerClient::HasPermissionToStartRound() const {
  return has_permission_to_start_round_;
}

void MultiplayerClient::NewClientMessage(const QString& message) {
  if (message.size() > kMaxMessageSize_) {
    CreateVisibleMessage(Message(MessageType::kToLongMessage));
    return;
  }
  if (message[0] == "/") {
    CreateVisibleMessage(Message(MessageType::kChatUpdate, {message}));
    ProcessCommand(message);
    return;
  }
  if (!is_online_) {
    CreateVisibleMessage(Message(MessageType::kChatOffline));
    return;
  }

  if (!IsRegistered()) {
    CreateVisibleMessage(Message(MessageType::kNameNullMessage));
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
      CreateVisibleMessage(Message(MessageType::kOk));
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
    } else {
      CreateVisibleMessage(Message(MessageType::kYourNickNameIs,
                                   {nick_name_}));
    }
    return;
  }
  if (words[0] == "clear" && words.size() == 1) {
    received_message_.push_back(
        Message().SetCommandMessage("",
                                    CommandType::kChatClear));
    return;
  }
  if (words[0] == "help" && words.size() == 1) {
    CreateVisibleMessage(Message(MessageType::kHelpClear));
    CreateVisibleMessage(Message(MessageType::kHelpImmortal));
    CreateVisibleMessage(Message(MessageType::kHelpGold));
    CreateVisibleMessage(Message(MessageType::kHelpUnlock));
    return;
  }
  if (words[0] == "gold" && words.size() == 2) {
    if (words[1].toInt()) {
      if (IsOnline()) {
        CreateVisibleMessage(Message(MessageType::kNoCheat));
      } else if (words[1].toInt() < 0) {
        CreateVisibleMessage(Message(MessageType::kGoldError));
      } else {
        received_message_.push_back(
            Message().SetCommandMessage(words[1],
                                        CommandType::kGoldChange));

        CreateVisibleMessage(Message(MessageType::kMoreGold));
      }
    } else {
      CreateVisibleMessage(Message(MessageType::kGoldError));
    }
    return;
  }
  if (words[0] == "iddqd") {
    if (IsOnline()) {
      CreateVisibleMessage(Message(MessageType::kNoCheat));
    } else {
      received_message_.push_back(
          Message().SetCommandMessage(words[0],
                                      CommandType::kHealthGrow));
      CreateVisibleMessage(Message(MessageType::kInfinityHealth));
    }
    return;
  }
  if (words[0] == "unlock") {
    received_message_.push_back(
        Message().SetCommandMessage(words[0],
                                    CommandType::kUnlock));
    CreateVisibleMessage(Message(MessageType::kYouTheBest));
    return;
  }
  CreateVisibleMessage(Message(MessageType::kErrorCommand));
}

void MultiplayerClient::CreateVisibleMessage(const Message& message) {
  Message message_to_send;
  int point = static_cast<int>(message.GetType());
  auto& arguments = message.GetArguments();
  QString text_message = database_[point].message;
  for (int i = 0; i < arguments.size(); i++) {
    text_message = text_message.arg(arguments[i]);
  }
  message_to_send.SetVisibleMessage(
      text_message, database_[point].type);

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
  is_trying_to_connect_ = false;
  has_permission_to_start_round_ = true;
  CreateVisibleMessage(Message(MessageType::kConnect));

  if (!IsRegistered()) {
    CreateVisibleMessage(Message(MessageType::kHintRegistration1));
    CreateVisibleMessage(Message(MessageType::kHintRegistration2));
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
  has_permission_to_start_round_ = true;
  is_online_ = false;
}

QString MultiplayerClient::AutoGenerateNickName() const {
  return first_name_[random_generator_() % first_name_.size()] + "_"
      + surname_[random_generator_() % surname_.size()];
}
