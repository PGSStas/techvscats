#include "message.h"

Message::Message(MessageType type, const QString& message, int number)
    : type_(type), message_(message), number_(number) {}

QByteArray Message::NewConnectionMessage(const QString& nick_name) {
  return CodeToBinary(Message(
      MessageType::kNewConnection, nick_name, 0));
}

QByteArray Message::EnterRoomMessage(int level_id) {
  return CodeToBinary(Message(
      MessageType::kEnterRoom, "", level_id));

}

QByteArray Message::RoundCompletedMessage(int base_current_health) {
  return CodeToBinary(Message(
      MessageType::kRoundCompletedByPlayer, "", base_current_health));

}

QByteArray Message::LeaveRoomMessage() {
  return CodeToBinary(Message(
      MessageType::kLeaveRoom, "", 0));
}

QByteArray Message::StartRoundMessage() {
  return CodeToBinary(Message(
      MessageType::kStartRound, "", 0));
}

QByteArray Message::DialogMessage(const QString& message, DialogType type,
                                  const QString& nick_name) {
  return CodeToBinary(
      Message().SetDialogMessage(message, type, nick_name));
}

QByteArray Message::CodeToBinary(const Message& message) {
  QJsonDocument json_document;
  QJsonObject json_object;
  json_object["type"] = static_cast<int>(message.type_);
  json_object["message"] = message.message_;
  json_object["number"] = message.number_;
  json_document.setObject(json_object);
  return json_document.toBinaryData();
}

QByteArray Message::GlobalChatMessage(const QString& messages) {
  return CodeToBinary(
      Message(MessageType::kGlobalChat, messages, 0));
}

Message& Message::SetDialogMessage(const QString& message, DialogType type,
                                   const QString& nick_name) {
  type_ = MessageType::kDialog;
  number_ = static_cast<int>(type);
  message_ = "";
  if (!nick_name.isEmpty()) {
    message_ = "> " + nick_name + " : ";
  }
  message_ += message;

  return *this;
}
Message& Message::SetCommandMessage(const QString& message,
                                    ControllerCommandType type) {
  type_ = MessageType::kControllerCommand;
  number_ = static_cast<int>(type);
  message_ = message;
  return *this;
}

Message& Message::DecodeFromBinary(const QByteArray& array) {
  QJsonDocument json_document = QJsonDocument::fromBinaryData(array);
  auto object = json_document.object();
  type_ = static_cast<MessageType>(object["type"].toInt());
  message_ = object["message"].toString();
  number_ = object["number"].toInt();
  return *this;
}

MessageType Message::GetType() const {
  return type_;
}

QString Message::GetMessage() const {
  return message_;
}

int Message::GetNumber() const {
  return number_;
}