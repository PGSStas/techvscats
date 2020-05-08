#include "message.h"

QByteArray Message::NewConnectionMessage(const QString& nick_name) {
  message_ = nick_name;
  type_ = MessageType::kNewConnection;
  return CodeToBinary();
}

QByteArray Message::EnterRoomMessage(int level_id) {
  number_ = level_id;
  type_ = MessageType::kEnterRoom;
  return CodeToBinary();
}

QByteArray Message::RoundCompletedMessage(int base_current_health) {
  number_ = base_current_health;
  type_ = MessageType::kRoundCompletedByPlayer;
  return CodeToBinary();
}

QByteArray Message::LeaveRoomMessage() {
  type_ = MessageType::kLeaveRoom;
  return CodeToBinary();
}

QByteArray Message::StartRoundMessage() {
  type_ = MessageType::kStartRound;
  return CodeToBinary();
}

QByteArray Message::DialogMessage(const QString& message, DialogType type,
                                  const QString& nick_name) {
  SetDialogMessage(message, type, nick_name);
  return CodeToBinary();
}

QByteArray Message::GlobalChatMessage(const QString& messages) {
  type_ = MessageType::kGlobalChat;
  message_ = messages;
  return CodeToBinary();
}

Message& Message::SetDialogMessage(const QString& message, DialogType type,
                                   const QString& nick_name) {
  type_ = MessageType::kDialog;
  number_ = static_cast<int>(type);
  message_ = "";
  if (nick_name != "") {
    message_ += nick_name + " : ";
  }
  message_ += message;
  return *this;
}

Message& Message::DecodeFromBinary(const QByteArray& array) {
  QJsonDocument json_document = QJsonDocument::fromBinaryData(array);
  type_ = static_cast<MessageType>(json_document["type"].toInt());
  message_ = json_document["message"].toString();
  number_ = json_document["number"].toInt();
  return *this;
}

QByteArray Message::CodeToBinary() const {
  QJsonDocument json_document;
  QJsonObject json_object;
  json_object["type"] = static_cast<int>(type_);
  json_object["message"] = message_;
  json_object["number"] = number_;
  json_document.setObject(json_object);
  return json_document.toBinaryData();
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
