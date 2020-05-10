#include "message.h"

Message::Message(MessageType type, QStringList list)
    : message_type_(type), arguments_(std::move(list)) {
  arguments_number_ = arguments_.size();
}

QByteArray Message::NewConnectionMessage(const QString& nick_name) {
  return CodeToBinary(Message(
      MessageType::kNewConnection, {nick_name}));
}

QByteArray Message::EnterRoomMessage(int level_id) {
  return CodeToBinary(Message(
      MessageType::kEnterRoom, {QString::number(level_id)}));
}

QByteArray Message::RoundCompletedMessage(int base_current_health,
                                          int casted_game_process_) {
  return CodeToBinary(Message(
      MessageType::kRoundCompletedByPlayer,
      {
          QString::number(base_current_health),
          QString::number(casted_game_process_)
      }));
}

QByteArray Message::LeaveRoomMessage() {
  return CodeToBinary(Message(MessageType::kLeaveRoom));
}

QByteArray Message::DialogMessage(const QString& message, DialogType type,
                                  const QString& nick_name) {
  return CodeToBinary(
      Message().SetControllerMessage(message, type, nick_name));
}

QByteArray Message::CodeToBinary(const Message& message) {
  QJsonDocument json_document;
  QJsonObject json_object;
  json_object["type"] = static_cast<int>(message.message_type_);
  json_object["arguments_number_"] = message.arguments_number_;
  for (int i = 0; i < message.arguments_number_; i++) {
    json_object["argument_" + QString::number(i)] = message.arguments_[i];
  }
  json_document.setObject(json_object);
  return json_document.toBinaryData();
}

QByteArray Message::GlobalChatMessage(const QString& messages) {
  return CodeToBinary(
      Message(MessageType::kGlobalChat, {messages}));
}

Message& Message::SetControllerMessage(const QString& message, DialogType type,
                                       const QString& nick_name) {
  message_type_ = MessageType::kDialog;
  dialog_type_ = type;
  arguments_ = QStringList({""});
  if (!nick_name.isEmpty()) {
    arguments_[0] = "> " + nick_name + " : ";
  }
  arguments_[0] += message;

  return *this;
}
Message& Message::SetCommandMessage(const QString& message,
                                    ControllerCommandType type) {
  message_type_ = MessageType::kControllerCommand;
  controller_command_type_ = type;
  arguments_[0] = message;
  return *this;
}

Message& Message::DecodeFromBinary(const QByteArray& array) {
  QJsonDocument json_document = QJsonDocument::fromBinaryData(array);
  auto object = json_document.object();
  message_type_ = static_cast<MessageType>(object["type"].toInt());
  arguments_number_ = object["arguments_number_"].toInt();
  for (int i = 0; i < arguments_number_; i++) {
    arguments_.push_back(object["argument_" + QString::number(i)].toString());
  }
  return *this;
}

MessageType Message::GetType() const {
  return message_type_;
}

QString Message::GetArgument(int arg_num) const {
  if(arg_num>arguments_number_){
    return "";
  }
  return arguments_[arg_num];
}

ControllerCommandType Message::GetControllerCommandType() const {
  return controller_command_type_;
}

DialogType Message::GetDialogType() const {
  return dialog_type_;
}
